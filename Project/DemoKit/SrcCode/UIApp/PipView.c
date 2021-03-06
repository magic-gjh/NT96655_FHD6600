#include "PipView.h"
#include "CoordTs.h"
#include "GxImage.h"
#include "Color.h"
#include <stdio.h>
#include "SxCmd.h"

#define THIS_DBGLVL         1       //0=OFF, 1=ERROR, 2=TRACE
#define __MODULE__          Pip
#define __DBGLVL__          THIS_DBGLVL
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
//#define __DBGFLT__          "[buf]"
#include "DebugModule.h"

static INT32 m_iCleanCnt = 0; //indicate the times of cleaning screen
static PIP_STYLE m_PipStyle = PIP_STYLE_2T1B2S;
static PIP_SRC_RATIO m_PrimaryImageRatio_Set = PIP_SRC_RATIO_4_3;
static PIP_SRC_RATIO m_PrimaryImageRatio_Active = PIP_SRC_RATIO_4_3;
static _ALIGNED(4) UINT8 m_PipTsBuf[COORDTS_REQ_MEM_SIZE]={0};


static URECT m_PipBaseOn_4_3 = {0,0,640,480};
static URECT m_PipBaseOn_16_9 = {0,0,640,360};

static URECT m_PipWnd_Full[PIP_DST_RATIO_MAX_CNT][PIP_SRC_RATIO_MAX_CNT] = {
    {{  0,  0,640,480},{  0, 60,640,360},{  0, 27,640,426}},
    {{ 80,  0,480,360},{  0,  0,640,360},{ 50,  0,540,360}},
};

static URECT m_PipWnd_Big[PIP_DST_RATIO_MAX_CNT][PIP_SRC_RATIO_MAX_CNT] = {
    {{  0,  0,640,480},{  0, 60,640,360},{  0, 27,640,426}},
    {{ 80,  0,480,360},{  0,  0,640,360},{ 50,  0,540,360}},
};

static URECT m_PipWnd_Small[PIP_DST_RATIO_MAX_CNT][PIP_SRC_RATIO_MAX_CNT] = {
    {{0,0,320,240},{0,0,320,240},{0,0,320,240}},
    {{0,0,320,240},{0,0,320,240},{0,0,320,240}},
};
#if 0
static URECT m_PipWnd_Small[PIP_DST_RATIO_MAX_CNT][PIP_SRC_RATIO_MAX_CNT] = {
    {{480,360,160,120},{480,390,160, 90},{480,374,160,106}},
    {{520,270,120, 90},{480,270,160, 90},{504,270,136, 90}},
};
#endif

void PipView_SetStyle(PIP_STYLE PipStyle)
{
    m_PipStyle = PipStyle;
}

void PipView_SetPrimaryImgRatio(USIZE* pSize)
{
    if(pSize->w==4 && pSize->h==3)
        m_PrimaryImageRatio_Set = PIP_SRC_RATIO_4_3;
    else if(pSize->w==16 && pSize->h==9)
        m_PrimaryImageRatio_Set = PIP_SRC_RATIO_16_9;
    else if(pSize->w==3 && pSize->h==2)
        m_PrimaryImageRatio_Set = PIP_SRC_RATIO_3_2;
    else
    {
        DBG_ERR("Unsupport.\r\n");
    }
}

void PipView_ActivePrimaryImgRatio(void)
{
    m_iCleanCnt = 2;
    m_PrimaryImageRatio_Active = m_PrimaryImageRatio_Set;
}

INT32 PipView_OnDraw(DISPSRV_DRAW* pDraw) //PIP = Picture In Picture
{
    ER er;
    UINT32 i,n=(pDraw->bDualSrc==TRUE)?2:1;
    UINT32 uiLockIdx[2];
    PIP_DST_RATIO RatioDst; //display buffer ratio
    PIP_SRC_RATIO RatioSrc[2]={0}; //1st source and 2nd source
    COORDTS_HANDLE hTs = NULL;
    COORDTS_CREATE Create={0};
    COORDTS_ORIGIN Origin={0};
    COORDTS_TARGET Target={0};
    COORDTS_TRANS  Trans={0};
    IMG_BUF* pSrc=NULL;
    IMG_BUF* pSrcImg[2]={0};
    IMG_BUF* pDst=pDraw->pImg[0];

    IRECT rcSrc={0},rcDst={0};

    for(i=0;i<n;i++)
    {
        if((er=pDraw->fpLock[i](&uiLockIdx[i],DISPSRV_LOCK_NEWEST))!=E_OK)
        {
            DBG_ERR("failed to lock %d\r\n",i);
            return er;
        }
        else
        {
             pSrcImg[i] = &pDraw->pDS[i]->pSrc[uiLockIdx[i]];
        }
    }

    //Collect Ratio
    RatioDst = PIP_DST_RATIO_4_3;//(pDraw->pDD[DISPSRV_DISP_IDX_PRIMARY]->AspectRatio.h*16.0f/pDraw->pDD[DISPSRV_DISP_IDX_PRIMARY]->AspectRatio.w==9.0f)
//        ?PIP_DST_RATIO_16_9
//        :PIP_DST_RATIO_4_3;
    RatioSrc[0] = m_PrimaryImageRatio_Active;

    if(pSrcImg[1]!=NULL)
    {
        RatioSrc[1] = (pSrcImg[1]->Height*16.0f/pSrcImg[1]->Width==9.0f)
            ?PIP_SRC_RATIO_16_9
            :((pSrcImg[1]->Height*3.0f/pSrcImg[1]->Width==2.0f)?PIP_SRC_RATIO_3_2:PIP_SRC_RATIO_4_3);
    }

    //Prepare Coordinate Transform
    Create.uiApiVer = COORDTS_API_VERSION;
    Create.pRegBuf = m_PipTsBuf;
    Create.uiRegBufSize = sizeof(m_PipTsBuf);
    hTs = CoordTs_Create(&Create);

    Origin.hHandle=hTs;
    if(RatioDst==PIP_DST_RATIO_16_9)
    {
        Origin.SizeOrigin.w = m_PipBaseOn_16_9.w;
        Origin.SizeOrigin.h = m_PipBaseOn_16_9.h;
    }
    else
    {
        Origin.SizeOrigin.w = m_PipBaseOn_4_3.w;
        Origin.SizeOrigin.h =m_PipBaseOn_4_3.h;
    }
    CoordTs_SetOrigin(&Origin);

    Target.hHandle=hTs;
    Target.SizeTarget.w = pDst->Width;
    Target.SizeTarget.h = pDst->Height;
    Target.pRcRegion = NULL;
    CoordTs_SetTarget(&Target);


    //--------------------Customer Draw Begin-----------------------------------
    //Clean Screen
    if(m_iCleanCnt>0)
    {
        GxImg_FillData(pDst, NULL, COLOR_YUV_BLACK);
        m_iCleanCnt--;
    }

    //Trans Common Setting
    Trans.hHandle=hTs;
    Trans.bInverse=FALSE;
    Trans.Method = COORDTS_METHOD_FULL_FIT;
    Trans.pRcDst = (URECT*)&rcDst;
    Trans.uiRectNum = 1;

    //Paste 2nd layer first
    switch(m_PipStyle)
    {
        case PIP_STYLE_1T1F:
            pSrc = NULL;       //no paste
            Trans.pRcSrc=NULL;
            break;
        case PIP_STYLE_1T1B2S:
            pSrc = pSrcImg[1]; //paste 2nd first
            Trans.pRcSrc = &m_PipWnd_Small[RatioDst][RatioSrc[1]];
            break;
        case PIP_STYLE_1T1S2B:
            pSrc = pSrcImg[1]; //paste 2nd first
            Trans.pRcSrc = &m_PipWnd_Big[RatioDst][RatioSrc[1]];
            break;
        case PIP_STYLE_2T2F:   //no paste
            pSrc = NULL;
            Trans.pRcSrc=NULL;
            break;
        case PIP_STYLE_2T1B2S:
            pSrc = pSrcImg[0]; //paste 1st first
            Trans.pRcSrc = &m_PipWnd_Big[RatioDst][RatioSrc[0]];
            break;
        case PIP_STYLE_2T1S2B:
            pSrc = pSrcImg[0]; //paste 1st first
            Trans.pRcSrc = &m_PipWnd_Small[RatioDst][RatioSrc[0]];
            break;
        default:
            DBG_ERR("unexpected case %d\r\n",m_PipStyle);
            break;
    }

    if(pSrc!=NULL)
    {
        CoordTs_TransRect(&Trans);

        rcSrc.x = 0;
        rcSrc.y = 0;
        rcSrc.w = pSrc->Width;
        rcSrc.h = pSrc->Height;

        //First Draw
        GxImg_ScaleData(pSrc,&rcSrc,pDst,&rcDst);
    }

    //Paste 1st layer second
    switch(m_PipStyle)
    {
        case PIP_STYLE_1T1F:
            pSrc = pSrcImg[0]; //then paste 1st
            Trans.pRcSrc = &m_PipWnd_Full[RatioDst][RatioSrc[0]];
            break;
        case PIP_STYLE_1T1B2S:
            pSrc = pSrcImg[0]; //then paste 1st
            Trans.pRcSrc = &m_PipWnd_Big[RatioDst][RatioSrc[0]];
            break;
        case PIP_STYLE_1T1S2B:
            pSrc = pSrcImg[0]; //then paste 1st
            Trans.pRcSrc = &m_PipWnd_Small[RatioDst][RatioSrc[0]];
            break;
        case PIP_STYLE_2T2F:
            pSrc = pSrcImg[1]; //then paste 2nd
            Trans.pRcSrc = &m_PipWnd_Full[RatioDst][RatioSrc[1]];
            break;
        case PIP_STYLE_2T1B2S:
            pSrc = pSrcImg[1]; //then paste 2nd
            Trans.pRcSrc = &m_PipWnd_Small[RatioDst][RatioSrc[1]];
            break;
        case PIP_STYLE_2T1S2B:
            pSrc = pSrcImg[1]; //then paste 2nd
            Trans.pRcSrc = &m_PipWnd_Big[RatioDst][RatioSrc[1]];
            break;
        default:
            DBG_ERR("unexpected case %d\r\n",m_PipStyle);
            break;
    }

    if(pSrc!=NULL)
    {
        CoordTs_TransRect(&Trans);

        rcSrc.x = 0;
        rcSrc.y = 0;
        rcSrc.w = pSrc->Width;
        rcSrc.h = pSrc->Height;

        //Second Draw
        GxImg_ScaleData(pSrc,&rcSrc,pDst,&rcDst);
    }

    for(i=0;i<n;i++)
    {
        if((er=pDraw->fpUnlock[i](uiLockIdx[i]))!=E_OK)
        {
            DBG_ERR("failed to unlock %d\r\n",i);
            return er;
        }
    }
    //--------------------Customer Draw End-------------------------------------
    pDraw->fpFlip(TRUE);

    return E_OK;
}


static BOOL xPipView_Style(CHAR* strCmd)
{
    sscanf(strCmd,"%d",&m_PipStyle);
    return TRUE;
}

SXCMD_BEGIN(pipview,"Picture in picture")
SXCMD_ITEM("sty %", xPipView_Style, "Set style")
SXCMD_END()

void PipView_InstallCmd(void)
{
    SxCmd_AddTable(pipview);
}