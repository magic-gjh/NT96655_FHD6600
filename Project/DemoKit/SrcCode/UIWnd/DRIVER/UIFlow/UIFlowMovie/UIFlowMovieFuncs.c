#include "UIFlow.h"
#include "type.h"
#include "UIFramework.h"
#include "UIFrameworkExt.h"
#include "Sdio.h"
#include "MediaRecAPI.h"
#include "IPL_Ctrl.h" // Isiah, implement YUV merge mode of recording func.
#include "FileDB.h"
#include "FileSysTsk.h"

#define MOVIE_REC_TIME_MIN  1 // 1 sec

#define MOVIE_REC_MIN_CLUSTER_SIZE      (0x8000)    //32KB
#define MOVIE_REC_SD_CLASS              (4)         // class 4

MOV_TASK_DATA   gMovData = { 0 };

static UINT32  g_MovRecMaxTime = 0;
static UINT32  g_MovRecCurrTime = 0;
static UINT32  g_MovRecSelfTimerSec = 0;
static UINT32  g_MovRecSelfTimerID = NULL_TIMER;
static LDWS_OSD_COORDINATE g_LdwsOsdCoord = {0};
extern void Movie_IPLChangeCB(UINT32 mode, UINT32 param);
extern BOOL System_OnStrgIsFileSystemOK(void);

UINT8 FlowMovie_GetMovDataState(void)
{
    return gMovData.State;
}

UINT32 Get_MovieCyclicRecTime(void)
{
    UINT32 uiCycleRecTime=0;
    switch (SysGetFlag(FL_MOVIE_CYCLIC_REC))
    {
    // cyclic recording handling
    
      case MOVIE_CYCLICREC_1MIN:
           uiCycleRecTime=60;
        break;
        
      case MOVIE_CYCLICREC_2MIN:
           uiCycleRecTime=120;
        break;		
        
      case MOVIE_CYCLICREC_3MIN:
           uiCycleRecTime=180;
        break;
      case MOVIE_CYCLICREC_5MIN:
           uiCycleRecTime=300;
        break;
      case MOVIE_CYCLICREC_10MIN:
           uiCycleRecTime=600;
        break;
    }
    return uiCycleRecTime;
}

BOOL FlowMovie_CheckMemoryForCyclicRec(UINT32 uiCyclicRecTime)
{

    UINT32  err;
	PFILEDB_FILE_ATTR FileAttr = NULL;
	INT32             ret;
	int i = 0;
	i = 1;
       if(System_OnStrgIsFileSystemOK()==FALSE)
       {
	     debug_msg("File system not ok ,return ..\r\n");                            
            return FALSE;
       }
       FileSys_WaitFinish();
	debug_msg("^G ==  uiCyclicRecTime : %d      :  %d\r\n",uiCyclicRecTime*2,UIMovRecObj_GetData(RECMOVIE_MAXSECOND));
	while (uiCyclicRecTime*2 >= (UIMovRecObj_GetData(RECMOVIE_MAXSECOND)))
    	{
    	FileDB_Refresh(0);
    	FileAttr = FileDB_SearhFile2(0,i);
		if(FileAttr->attrib == 33)
		{
		/*
		 ret = FileSys_SetAttrib(FileAttr->filePath,FST_ATTRIB_READONLY,FALSE);
		 if (ret == FST_STA_OK)
		 	{
		 	FileAttr->attrib &=(~FS_ATTRIB_READ);
		 	}
		 	*/
		 
		}
		else
			{
			debug_msg("^G ==  no room for  loop rec   then   del   file : %s\r\n",FileAttr->filePath);
			if(FST_STA_OK==FileSys_DeleteFile(FileAttr->filePath))
                      {
	        	    FileSys_WaitFinish();
			    FileDB_Refresh(0);
			}			
                     else
                     {
			        debug_msg("File system error ,return ..\r\n");                     
                            return FALSE;
                     }
			}
		i++;
    	}
    if (uiCyclicRecTime*2 >= UIMovRecObj_GetData(RECMOVIE_MAXSECOND))
    {
    	Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CARD_FULL,FLOWWRNMSG_TIMER_2SEC);
		return TRUE;
    }
	else
	{
	return FALSE;
	}
    
}

void FlowMovie_StartRec(void)
{
    if (g_MovRecSelfTimerSec == 0)
    {
        g_MovRecCurrTime = 0;

        // update DCF Folder/File name
        FlowDCF_UpdateName();

        // wait playing sound stop
        GxSound_WaitStop();
		
        Ux_SendEvent(&CustomMovieObjCtrl,NVTEVT_EXE_MOVIE_REC_START,NULL);

        //#NT#2012/10/23#Philex Lin - begin
        // disable auto power off/USB detect timer
        KeyScan_EnableMisc(FALSE);
        //#NT#2012/10/23#Philex Lin - end
    }
    else
    {
        debug_err(("FlowMovie_StartRec: Not yet,g_MovSelfTimerSec=%d\r\n", g_MovRecSelfTimerSec));
    }
}

void FlowMovie_StopRec(void)
{
    // Isiah, implement YUV merge mode of recording func.
    IPL_SLEEP_INFO Info;

    UxCtrl_SetShow(&UIFlowWndMovie_PanelCtrl,FALSE);
    Ux_SendEvent(&CustomMovieObjCtrl,NVTEVT_EXE_MOVIE_REC_STOP,NULL);
  
    //#NT#2012/10/23#Philex Lin - begin
    // enable auto power off/USB detect timer
    KeyScan_EnableMisc(TRUE);
    // make sure mediarec task stopping record
    while (MediaRec_GetStatus()!=MEDIAREC_STATUS_OPENED_NOT_RECORD)
        ;
    gMovData.State= MOV_ST_VIEW;
    //#NT#2012/10/23#Philex Lin - end

    // Isiah, implement YUV merge mode of recording func.
    if(FlowMovie_RecGetYUVMergeMode())
    {
        Info.Id = 0;
        IPL_SetCmd(IPL_SET_WAKEUP, (void *)&Info);
        IPL_WaitCmdFinish();

        IPC_WaitVD(FALSE, IPL_ID_1);
        IPC_WaitVD(FALSE, IPL_ID_1);
        IPC_WaitVD(FALSE, IPL_ID_1);

        Movie_IPLChangeCB(MEDIAREC_IPLCHG_PREVIEW, 0);
        debug_msg("Change IPL to movie preview mode\r\n");
    }
}

void FlowMovie_StopRecSelfTimer(void)
{
    if (g_MovRecSelfTimerID != NULL_TIMER)
    {
        GxTimer_StopTimer(&g_MovRecSelfTimerID);
        g_MovRecSelfTimerID = NULL_TIMER;
    }
    g_MovRecSelfTimerSec = 0;
}

UINT8 FlowMovie_GetDataState(void)
{
    return gMovData.State;
}

void FlowMovie_SetRecMaxTime(UINT32 RecMaxTime)
{
    g_MovRecMaxTime = RecMaxTime;
}

UINT32 FlowMovie_GetRecMaxTime(void)
{
    return g_MovRecMaxTime;
}

void FlowMovie_SetRecCurrTime(UINT32 RecCurrTime)
{
    g_MovRecCurrTime = RecCurrTime;
}

UINT32 FlowMovie_GetRecCurrTime(void)
{
    return g_MovRecCurrTime;
}

BOOL FlowMovie_IsStorageErr(BOOL IsCheckFull)
{
    UINT32  uiClusterSize;
    BOOL MTG_cardisFull = FALSE;
#if (MOVIE_REC_CLASS4 == ENABLE)
    PSDIO_MISC_INFORMATION pMiscInfo;
#endif

    // check card inserted
    if (UI_GetData(FL_CardStatus) == CARD_REMOVED)
    {
        Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_PLEASE_INSERT_SD,FLOWWRNMSG_TIMER_2SEC);
        return TRUE;
    }

    // check storage error
    if(UIStorageCheck(STORAGE_CHECK_ERROR, NULL) == TRUE)
    {
        Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,FLOWWRNMSG_ISSUE_MEM_ERR,FLOWWRNMSG_TIMER_KEEP);
        return TRUE;
    }


    // check storage lock or directory read only
    if (UIStorageCheck(STORAGE_CHECK_LOCKED, NULL) == TRUE ||
        UIStorageCheck(STORAGE_CHECK_DCIM_READONLY, NULL) == TRUE)
    {
        Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CARD_LOCKED,FLOWWRNMSG_TIMER_2SEC);
        return TRUE;
    }

    // check storage full
    if (TRUE == IsCheckFull)
    {
        g_MovRecMaxTime = UIMovRecObj_GetData(RECMOVIE_MAXSECOND);
        if (g_MovRecMaxTime <= MOVIE_REC_TIME_MIN)
        {
            g_MovRecMaxTime = 0;
            Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CARD_FULL,FLOWWRNMSG_TIMER_2SEC);
            return TRUE;
        }
    }

    // check folder full
    if (UIStorageCheck(STORAGE_CHECK_FOLDER_FULL, NULL) == TRUE)
    {
        Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CARD_FULL,FLOWWRNMSG_TIMER_2SEC);
        return TRUE;
    }

    if (Get_MovieCyclicRecTime() != 0)
        {
              debug_err(("#Card Full Get_MovieCyclicRecTime : %d\r\n",Get_MovieCyclicRecTime()));			        
            MTG_cardisFull = FlowMovie_CheckMemoryForCyclicRec(Get_MovieCyclicRecTime());
			if(MTG_cardisFull)
		return MTG_cardisFull;
	 }     

    // check sd card whether faster than class 4
#if (MOVIE_REC_CLASS4 == ENABLE)
    pMiscInfo = sdio_getMiscInfo();
    if (pMiscInfo->uiWriteRate<MOVIE_REC_SD_CLASS)
    {
        Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_SD_CLASS4,FLOWWRNMSG_TIMER_2SEC);
        return TRUE;
    }
#endif

    // Check cluster size, need to be larger than 32KB
    uiClusterSize = FileSys_GetDiskInfo(FST_INFO_CLUSTER_SIZE);
    if (uiClusterSize< MOVIE_REC_MIN_CLUSTER_SIZE)
    {
        Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CLUSTER_WRONG,FLOWWRNMSG_TIMER_2SEC);
        return TRUE;
    }

    return FALSE;
}

UINT32 FlowMovie_GetSelfTimerID(void)
{
    return g_MovRecSelfTimerID;
}

#if 0
BOOL FlowMovie_ChkDrawStoreFullFolderFull(void)
{

    if(UIStorageCheck(STORAGE_CHECK_FULL, &(g_MovRecMaxTime)) == TRUE)
    {
        g_MovRecMaxTime = UIMovRecObj_GetData(RECMOVIE_MAXSECOND);
        if (UI_GetData(FL_CardStatus) == CARD_REMOVED)
        {
            Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,FLOWWRNMSG_ISSUE_MEM_FULL,FLOWWRNMSG_TIMER_2SEC);
            return TRUE;
        }
        else
        {
            Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,FLOWWRNMSG_ISSUE_CARD_FULL,FLOWWRNMSG_TIMER_2SEC);
            return TRUE;
        }
    }

    return FALSE;
}
#endif

void FlowMovie_GetPictureInMovie(void)
{
#if (0)//(_MOVIE_PIM_MODE_ == ENABLE)
    UINT32  sec, unsafe;

    switch (gMovData.State)
    {
    case MOV_ST_REC:
        sec = MovRec_Disk2Second();
        unsafe = MovRec_CheckUnsavedFileBlocks();

        if ((sec > 3)&&(unsafe == 0))
        {
            RawEnc_SetCaptureOne();
            //UxCtrl_SetShow(&UIFlowWndMovie_Static_pimCtrl, TRUE);
        }
        else
        {
            if (unsafe)
            {
                debug_err(("unsafe to take picture !\r\n"));
            }
            else
            {
                debug_err(("no space to encode RAW !\r\n"));
            }
        }
        break;
    }
#endif
}

void FlowMovie_OnTimer1SecIndex(void)
{

    switch (gMovData.State)
    {
    case MOV_ST_VIEW:
    case MOV_ST_VIEW | MOV_ST_ZOOM:
    case MOV_ST_REC:
    case MOV_ST_REC | MOV_ST_ZOOM:
        gMovData.SysTimeCount++;
        if (UxCtrl_IsShow(&UIFlowWndMovie_YMD_StaticCtrl))
        {
            FlowMovie_IconDrawDateTime();
        }
        break;

    }
}


void FlowMovie_LwdsProcess(LDWS_OSD_COORDINATE LdwsOsdCoord)
{
    g_LdwsOsdCoord = LdwsOsdCoord;

    /* Enable FD frame show */
//    UxCtrl_SetShow(&UIFlowWndMovie_LDWS_FrameCtrl,TRUE);

    /* Redraw all window OSD */
    UxCtrl_SetDirty(&UIFlowWndMovieCtrl, TRUE);
}

UINT32 FlowMovie_GetLdwsOsdIno(void)
{
    return (UINT32)&g_LdwsOsdCoord;
}
INT32 Get_GSensorSensitivity(void)
{
    UINT32 Sensitivity = 0;

    #if (UI_STYLE == UI_STYLE_DRIVER)

    switch(SysGetFlag(FL_GSENSOR))
    {
    #if 1//DA380
    case GSENSOR_HIGH:
        Sensitivity = 200;
        break;
    case GSENSOR_MED:
        Sensitivity = 800;
        break;
    case GSENSOR_LOW:
        Sensitivity = 1400;
        break;
    case GSENSOR_OFF:
        Sensitivity = 32768;
        break;
    #elif 0//RD07
    case GSENSOR_HIGH:
        Sensitivity = 25;//20//30
        break;
    case GSENSOR_MED:
        Sensitivity = 45;//30//60
        break;
    case GSENSOR_LOW:
        Sensitivity = 65;//50//80
        break;
    case GSENSOR_OFF:
        Sensitivity = 368;
        break;
    #else
        case GSENSOR_HIGH:
            return 256;//128;// 4G
        case GSENSOR_MED:
            return 320;//256;// 5G
        case GSENSOR_LOW:
            return 403;//384; //6G 
        case GSENSOR_OFF:
            return 9000;//no use
    
    #endif            
    }
    #endif
    return Sensitivity;
}
