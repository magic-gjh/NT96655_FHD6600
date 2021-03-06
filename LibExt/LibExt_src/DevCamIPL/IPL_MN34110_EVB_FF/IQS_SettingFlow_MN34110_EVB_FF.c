#ifndef _IQS_SETTINGFLOW_SAMPLE_C
#define _IQS_SETTINGFLOW_SAMPLE_C
#include "IPL_MN34110_EVB_FF_Int.h"
PRE_VIG     IQ_PRE_Vig;
DCE_Distortion IQ_DCE_Distortion;

extern UINT32 AE_getCurLum(UINT32 LumBit);

IPE_EDGEEXT     IQ_IPE_EdgeExt;
IPE_EDGEMAP     IQ_IPE_EdgeMap;
IPE_EDGEENH     IQ_IPE_EdgeEnh;
IPE_CC          IQ_IPE_CC;
IPE_CCTRL       IQ_IPE_Cctrl;
IPE_CCOFS       IQ_IPE_CbCrofs;
IPE_CCON        IQ_IPE_YCCcon;
IPE_3DCC        IQ_IPE_3DCC;
IPE_GAMMA       IQ_IPE_RGBGAMMA;
IPE_YCCFIX      IQS_IPE_YCFixEffect;
IPE_CSTP        IQS_IPE_CSTP;
IFE2_AvgFilter  IQ_IFE2_AvgFilter;

///////////////////////////////////////////////
// Body
///////////////////////////////////////////////


static UINT32 IQS_GetCapIsoIndex(void)
{
    UINT32 IsoIdx;

    UINT32 ISO, ExpT, Iris;
    AE_GetCapAEArg(&ISO, &ExpT, &Iris);

    if ( ISO <= 150 )
        IsoIdx =  CAPISO0100;
    else if ( ISO <= 300 )
        IsoIdx =  CAPISO0200;
    else if ( ISO <= 600 )
        IsoIdx =  CAPISO0400;
    else if ( ISO <= 1200 )
        IsoIdx =  CAPISO0800;
    else
        IsoIdx =  CAPISO1600;

//    DBG_ERR("ISO = %d, Idx = %d\r\n", ISO, IsoIdx);

    UINT32 UD_ISOIndex, UD_SenModeIndex, UD_ZoomIndex;
    UserDefineIQIndexGet(&UD_ISOIndex, &UD_SenModeIndex, &UD_ZoomIndex);
    if ( UD_ISOIndex != IQS_UD_INDEX_NOSET )
        IsoIdx = UD_ISOIndex;

    if ( IsoIdx >= Total_ISONum )
    {
        IsoIdx = CAPISO0100;
    }
    return IsoIdx;
}

static UINT32 IQS_GetQVIsoIndex(void)
{
    UINT32 IsoIdx;

    UINT32 ISO, ExpT, Iris;
    AE_GetCapAEArg(&ISO, &ExpT, &Iris);

    if ( ISO <= 150 )
        IsoIdx =  QVISO0100;
    else if ( ISO <= 300 )
        IsoIdx =  QVISO0200;
    else if ( ISO <= 600 )
        IsoIdx =  QVISO0400;
    else if ( ISO <= 1200 )
        IsoIdx =  QVISO0800;
    else
        IsoIdx =  QVISO1600;


    //DBG_ERR("ISO = %d, Idx = %d\r\n", ISO, IsoIdx);

    UINT32 UD_ISOIndex, UD_SenModeIndex, UD_ZoomIndex;
    UserDefineIQIndexGet(&UD_ISOIndex, &UD_SenModeIndex, &UD_ZoomIndex);
    if ( UD_ISOIndex != IQS_UD_INDEX_NOSET )
        IsoIdx = UD_ISOIndex;

    if ( IsoIdx >= Total_ISONum )
    {
        IsoIdx = QVISO0100;
    }
    return IsoIdx;
}

static UINT32 IQS_GetPrvIsoIndex(void)
{
    UINT32 IsoIdx;
    UINT32 ISO, ExpT, Iris;
    AE_GetPrvAEArg(&ISO, &ExpT, &Iris);
    if ( IPL_AlgGetUIInfo(IPL_SEL_PRVSENMODE) != SENSOR_MODE_7 )
    {
        if ( ISO <= 150 )
            IsoIdx =  VQ2ISO0100;
        else if ( ISO <= 300 )
            IsoIdx =  VQ2ISO0200;
        else if ( ISO <= 600 )
            IsoIdx =  VQ2ISO0400;
        else if ( ISO <= 1200 )
            IsoIdx =  VQ2ISO0800;
        else
            IsoIdx =  VQ2ISO1600;
/*
        uiAE_AVG=AE_getCurLum(12); //12 bits
        if ( ISO >= 1000 && uiAE_AVG<=150 )
        {
            IsoIdx =  VQ2ISO1600L;
        }
*/
    }
    else
    {
        if ( ISO <= 150 )
            IsoIdx =  PRVISO0100;
        else if ( ISO <= 300 )
            IsoIdx =  PRVISO0200;
        else if ( ISO <= 600 )
            IsoIdx =  PRVISO0400;
        else if ( ISO <= 1200 )
            IsoIdx =  PRVISO0800;
        else
            IsoIdx =  PRVISO1600;
/*
        uiAE_AVG=AE_getCurLum(12); //12 bits
        if ( ISO >= 1000 && uiAE_AVG<=150 )
        {
            IsoIdx =  VQ2ISO1600L;
        }
*/
    }
    DBG_IND("ISO = %d, Idx = %d\r\n", ISO, IsoIdx);

    UINT32 UD_ISOIndex, UD_SenModeIndex, UD_ZoomIndex;
    UserDefineIQIndexGet(&UD_ISOIndex, &UD_SenModeIndex, &UD_ZoomIndex);
    if ( UD_ISOIndex != IQS_UD_INDEX_NOSET )
        IsoIdx = UD_ISOIndex;

    if ( IsoIdx >= Total_ISONum )
    {
        IsoIdx = PRVISO0100;
    }
    return IsoIdx;
}



static UINT32 IQS_GetISOIdx(IQS_FLOW_MSG MsgID)
{
    UINT32 IsoIdx;

    if ( MsgID >= IQCB_CAP_PRI_START && MsgID <= IQCB_CAP_PRI_END )
        IsoIdx = IQS_GetCapIsoIndex();
    else if (MsgID >= IQCB_CAP_QV_START  && MsgID <= IQCB_CAP_QV_END)
        IsoIdx = IQS_GetQVIsoIndex();
    else
        IsoIdx = IQS_GetPrvIsoIndex();

    return IsoIdx;
}

static UINT32 IQS_GetZoomIdx(IQS_FLOW_MSG MsgID)
{
    UINT32 ZoomIdx;
#if 0
    ZoomIdx = Lens_Zoom_GetSection(ZOOM_CUR_SECTION);
#endif

    ZoomIdx = ZOOMNUM0;

    UINT32 UD_ISOIndex, UD_SenModeIndex, UD_ZoomIndex;
    UserDefineIQIndexGet(&UD_ISOIndex, &UD_SenModeIndex, &UD_ZoomIndex);
    if ( UD_ZoomIndex != IQS_UD_INDEX_NOSET )
        ZoomIdx = UD_ZoomIndex;

    if ( ZoomIdx >= Total_ZOOMNum )
    {
        ZoomIdx = ZOOMNUM0;
    }

    return ZoomIdx;
}

static UINT32 IQS_GetSenModeIdx(IQS_FLOW_MSG MsgID)
{
    UINT32 SenModeIdx;
    SENSOR_MODE mode;
    if ( MsgID >= IQCB_CAP_PRI_START && MsgID <= IQCB_CAP_PRI_END )
        mode = (SENSOR_MODE)IPL_AlgGetUIInfo(IPL_SEL_CAPSENMODE);
    else
        mode = (SENSOR_MODE)IPL_AlgGetUIInfo(IPL_SEL_PRVSENMODE);

    SenModeIdx = SENMODENUM0;

    UINT32 UD_ISOIndex, UD_SenModeIndex, UD_ZoomIndex;
    UserDefineIQIndexGet(&UD_ISOIndex, &UD_SenModeIndex, &UD_ZoomIndex);
    if ( UD_SenModeIndex != IQS_UD_INDEX_NOSET )
        SenModeIdx = UD_SenModeIndex;

    if ( SenModeIdx >= Total_SENMODENum )
    {
        SenModeIdx = SENMODENUM0;
    }
    return SenModeIdx;
}



static ER PRE_IQparam(IQS_FLOW_MSG MsgID, PRE_SUBFUNC *subf,IPL_HAL_GROUP* group)
{
    UINT32 ISO_Value, Zoom_Value, SenMode_Value;

    ISO_Value = IQS_GetISOIdx(MsgID);
    Zoom_Value = IQS_GetZoomIdx(MsgID);
    SenMode_Value = IQS_GetSenModeIdx(MsgID);

    switch((UINT32)MsgID)
    {
        case IQS_MANUAL_TRIG:
        case IQCB_PRV_PRE_INIT:
        case IQCB_PREIME_D2D_PRE_PRI:
        case IQCB_PREIME_D2D_PRE_QV:
            //enable function
            subf->preFuncEn |= (
                                 0 //VigEn              ///< enable function: Vignette shading compensation
                                 );

            //Setting parameter
            group->preUpdate |= (
                                PRE_SubFEn      |    ///< update func enable/disable
                                PRE_VIG_
                              );
            if ( MsgID == IQCB_PREIME_D2D_PRE_PRI || MsgID == IQCB_PREIME_D2D_PRE_QV )
                subf->preFuncEn |= VigEn;              ///< enable function: Vignette shading compensation

            //////////////////
            // VIG Gain
            //////////////////
            #if 0
            IQ_PRE_Vig.Center.R     = PRE_ShadingCenter[SenMode_Value].R;
            IQ_PRE_Vig.Center.Gr    = PRE_ShadingCenter[SenMode_Value].Gr;
            IQ_PRE_Vig.Center.Gb    = PRE_ShadingCenter[SenMode_Value].Gb;
            IQ_PRE_Vig.Center.B     = PRE_ShadingCenter[SenMode_Value].B;
            #else
            if ( MsgID == IQCB_PREIME_D2D_PRE_PRI ||  MsgID == IQCB_PREIME_D2D_PRE_QV ) //capture
            {
                IQ_PRE_Vig.Center.R.x = IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_SIE_CH0_CAP_RAW_SIZE_H) >> 1;
                IQ_PRE_Vig.Center.R.y = IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_SIE_CH0_CAP_RAW_SIZE_V) >> 1;
                IQ_PRE_Vig.Center.Gr  = IQ_PRE_Vig.Center.R;
                IQ_PRE_Vig.Center.B    = IQ_PRE_Vig.Center.R;
                IQ_PRE_Vig.Center.Gb  = IQ_PRE_Vig.Center.R;
            }
            else  //preview
            {
                IQ_PRE_Vig.Center.R.x = IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_PRE_IN_SIZE_H) >> 1;
                IQ_PRE_Vig.Center.R.y = IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_PRE_IN_SIZE_V) >> 1;
                IQ_PRE_Vig.Center.Gr  = IQ_PRE_Vig.Center.R;
                IQ_PRE_Vig.Center.B    = IQ_PRE_Vig.Center.R;
                IQ_PRE_Vig.Center.Gb  = IQ_PRE_Vig.Center.R;
            }
            #endif

            IQ_PRE_Vig.DcExt.FuncEn = PRE_ShadingParam[SenMode_Value].FuncEn;
            IQ_PRE_Vig.DcExt.Th1    = PRE_ShadingParam[SenMode_Value].Th1;
            IQ_PRE_Vig.DcExt.Th2    = PRE_ShadingParam[SenMode_Value].Th2;
            IQ_PRE_Vig.Mul          = PRE_ShadingParam[SenMode_Value].Mul;
            IQ_PRE_Vig.T            = PRE_ShadingParam[SenMode_Value].T;
            IQ_PRE_Vig.TabGain      = PRE_ShadingParam[SenMode_Value].TabGain;
            IQ_PRE_Vig.XDIV         = PRE_ShadingParam[SenMode_Value].XDIV;
            IQ_PRE_Vig.YDIV         = PRE_ShadingParam[SenMode_Value].YDIV;
            IQ_PRE_Vig.bDither      = PRE_ShadingParam[SenMode_Value].bDither;
            IQ_PRE_Vig.DitherRstEn  = PRE_ShadingParam[SenMode_Value].DitherRstEn;

            IQ_PRE_Vig.R_LUT_TblAddr = (UINT32)PRE_ShadingLut[SenMode_Value][Zoom_Value];
            IQ_PRE_Vig.G_LUT_TblAddr = (UINT32)PRE_ShadingLut[SenMode_Value][Zoom_Value];
            IQ_PRE_Vig.B_LUT_TblAddr = (UINT32)PRE_ShadingLut[SenMode_Value][Zoom_Value];

            subf->pVig  = &IQ_PRE_Vig;

            break;

        case IQS_OZOOM_END:
            //enable function
            //Setting parameter
            group->preUpdate |= (
                                0 //PRE_VIG_
                              );
            //////////////////
            // VIG Gain
            //////////////////
            #if 0
            IQ_PRE_Vig.Center.R     = PRE_ShadingCenter[SenMode_Value].R;
            IQ_PRE_Vig.Center.Gr    = PRE_ShadingCenter[SenMode_Value].Gr;
            IQ_PRE_Vig.Center.Gb    = PRE_ShadingCenter[SenMode_Value].Gb;
            IQ_PRE_Vig.Center.B     = PRE_ShadingCenter[SenMode_Value].B;
            #else
            IQ_PRE_Vig.Center.R.x = IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_PRE_IN_SIZE_H) >> 1;
            IQ_PRE_Vig.Center.R.y = IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_PRE_IN_SIZE_V) >> 1;
            IQ_PRE_Vig.Center.Gr  = IQ_PRE_Vig.Center.R;
            IQ_PRE_Vig.Center.B    = IQ_PRE_Vig.Center.R;
            IQ_PRE_Vig.Center.Gb  = IQ_PRE_Vig.Center.R;
            #endif
            IQ_PRE_Vig.DcExt.FuncEn = PRE_ShadingParam[SenMode_Value].FuncEn;
            IQ_PRE_Vig.DcExt.Th1    = PRE_ShadingParam[SenMode_Value].Th1;
            IQ_PRE_Vig.DcExt.Th2    = PRE_ShadingParam[SenMode_Value].Th2;
            IQ_PRE_Vig.Mul          = PRE_ShadingParam[SenMode_Value].Mul;
            IQ_PRE_Vig.T            = PRE_ShadingParam[SenMode_Value].T;
            IQ_PRE_Vig.TabGain      = PRE_ShadingParam[SenMode_Value].TabGain;
            IQ_PRE_Vig.XDIV         = PRE_ShadingParam[SenMode_Value].XDIV;
            IQ_PRE_Vig.YDIV         = PRE_ShadingParam[SenMode_Value].YDIV;
            IQ_PRE_Vig.bDither      = PRE_ShadingParam[SenMode_Value].bDither;
            IQ_PRE_Vig.DitherRstEn  = PRE_ShadingParam[SenMode_Value].DitherRstEn;

            IQ_PRE_Vig.R_LUT_TblAddr = (UINT32)PRE_ShadingLut[SenMode_Value][Zoom_Value];
            IQ_PRE_Vig.G_LUT_TblAddr = (UINT32)PRE_ShadingLut[SenMode_Value][Zoom_Value];
            IQ_PRE_Vig.B_LUT_TblAddr = (UINT32)PRE_ShadingLut[SenMode_Value][Zoom_Value];

            subf->pVig  = &IQ_PRE_Vig;
            break;

        case IQS_AE_END:
        case IQS_AWB_END:
        case IQS_AF_START:
        case IQS_AF_END:
        case IQS_IMAGE_EFFECT:
            break;
        default :
            DBG_ERR("PRE_IQparam() param mode(%d) selection error!\r\n",MsgID);
            return E_SYS;
    }
    return E_OK;
}

static ER DCE_IQparam(IQS_FLOW_MSG MsgID, DCE_SUBFUNC *subf,IPL_HAL_GROUP* group)
{
    UINT32 ISO_Value, Zoom_Value, SenMode_Value,IMEffect_Value;

    IMEffect_Value = IPL_AlgGetUIInfo(IPL_SEL_IMAGEEFFECT);
    ISO_Value = IQS_GetISOIdx(MsgID);
    Zoom_Value = IQS_GetZoomIdx(MsgID);
    SenMode_Value = IQS_GetSenModeIdx(MsgID);

    switch((UINT32)MsgID)
    {
        case IQS_MANUAL_TRIG:
        case IQS_OZOOM_END:
        case IQCB_PRV_DCE_INIT:
        case IQCB_PREIME_D2D_DCE_QV:
        case IQCB_PREIME_D2D_DCE_PRI:
        case IQS_IMAGE_EFFECT:
            //enable function

            //Setting parameter
            group->dceUpdate |= (
                                DCE_DisT           | ///< update H/V distance factor/ratio selection
                                DCE_CAB            | ///< update color aberration factor
                                DCE_LUT            | ///< update LUT table address
                                DCE_FOV            | ///< update FOV
                                DCE_ENH            | ///< update enhancement
                                DCE_DISTOR           ///< update distortion parameter set
                              );
            if ( MsgID == IQCB_PREIME_D2D_DCE_QV )
            {
                IQ_DCE_Distortion.Center.x = IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_SIE_CH0_CAP_RAW_SIZE_H)>>1;
                IQ_DCE_Distortion.Center.y = IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_SIE_CH0_CAP_RAW_SIZE_V)>>1;
            }
            else if ( MsgID == IQCB_PREIME_D2D_DCE_PRI )
            {
                IQ_DCE_Distortion.Center.x = IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_SIE_CH0_CAP_RAW_SIZE_H)>>1;
                IQ_DCE_Distortion.Center.y = IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_SIE_CH0_CAP_RAW_SIZE_V)>>1;
            }
            else  //preview
            {
                IQ_DCE_Distortion.Center.x = IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_PRE_IN_SIZE_H)>>1;
                IQ_DCE_Distortion.Center.y = IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_PRE_IN_SIZE_V)>>1;
            }
            IQ_DCE_Distortion.Fov = DCE_Fov[SenMode_Value][Zoom_Value];
            IQ_DCE_Distortion.Enh = DCE_Enh[SenMode_Value][Zoom_Value];
            IQ_DCE_Distortion.ColorAber = DCE_ColorAbbration[SenMode_Value][Zoom_Value];
            IQ_DCE_Distortion.LUT_TblAddr = (UINT32)DCE_2D_LUT[SenMode_Value][Zoom_Value];
            IQ_DCE_Distortion.LutType = DCE_GetTableType(DCE_2D_LUT[SenMode_Value][Zoom_Value]);
            subf->pDistortion = &IQ_DCE_Distortion;
            subf->Dce_Dist = DCE_Dist[SenMode_Value];
            subf->Radious = DCE_Radious[SenMode_Value];

            switch (IMEffect_Value)
            {
                case SEL_IMAGEEFFECT_FISHEYE:
                    group->dceUpdate |= ( DCE_LUT | DCE_LUTType );
                    IQ_DCE_Distortion.LUT_TblAddr = (UINT32)IE_FISYEYE_LUT;
                    IQ_DCE_Distortion.LutType = NON_STRICTLY_INC_DEC; //DCE_GetTableType(IE_FISYEYE_LUT);
                    subf->pDistortion = &IQ_DCE_Distortion;
                    break;
                default:
                    break;
            }
            break;

        case IQS_AE_END:
        case IQS_AWB_END:
        case IQS_AF_START:
        case IQS_AF_END:
            break;
        default :
            DBG_ERR("DCE_IQparam() param mode(%d) selection error!\r\n",MsgID);
            return E_SYS;
    }
    return E_OK;
}


static ER IFE_IQparam(IQS_FLOW_MSG MsgID, IFE_SUBFUNC *subf,IPL_HAL_GROUP* group)
{
    UINT32 ISO_Value, Zoom_Value, SenMode_Value;
    UINT32 RGain, GGain, BGain;
    ISO_Value = IQS_GetISOIdx(MsgID);
    Zoom_Value = IQS_GetZoomIdx(MsgID);
    SenMode_Value = IQS_GetSenModeIdx(MsgID);

    switch((UINT32)MsgID)
    {
    case IQS_MANUAL_TRIG:
        case IQCB_PRV_IFE_INIT:
        case IQS_AE_END:
        case IQCB_PREIME_D2D_IFE_PRI:
        case IQCB_PREIME_D2D_IFE_QV:
            //enable function
            subf->ifeFuncEn |= FilterEn;
            if ( IFE_Func[ISO_Value].OUTLER == ENABLE )
                subf->ifeFuncEn |= OutlierEn;
            else
                subf->ifeFuncEn &= (~OutlierEn);

            //Setting parameter
            group->ifeUpdate |= (
                                    IFE_SubFEn      |       ///< update func enable/disable
                                    IFE_Outl_       |       ///< update outlier
                                    IFE_Cgain_      |       ///< update color gain
                                    IFE_Filter_            ///< update noise reduction filter
                              );

            //////////////////
            // IFE
            //////////////////
            subf->pOutl    = &IFE_Outl_param[ISO_Value];

            subf->pCrvMap  = &IFE_CurveMap_param_ycc;

            subf->pFilter  = &IFE_Filter_param[ISO_Value];

            AWB_GetColorGian(&RGain, &GGain, &BGain);
            subf->CGain.R  = 256;
            subf->CGain.Gr = 256;
            subf->CGain.Gb = 256;
            subf->CGain.B  = 256;
            subf->CGain.IfeGainSel = _2_8;
            subf->CGain.cfa = IPL_RAW_PIX_R;
            break;

        case IQS_AWB_END:
        case IQS_AF_START:
        case IQS_AF_END:
        case IQS_OZOOM_END:
        case IQS_IMAGE_EFFECT:
            break;
        default :
            DBG_ERR("IFE_IQparam() param mode(%d) selection error!\r\n",MsgID);
            return E_SYS;
    }
    return E_OK;
}



static ER IPE_IQparam(IQS_FLOW_MSG MsgID, IPE_SUBFUNC *subf,IPL_HAL_GROUP* group)
{
    UINT32 ISO_Value, Zoom_Value, Sharpness_Value, Saturation_Value, IMEffect_Value;
    UINT32 RGain, GGain, BGain;
    ER ret = E_OK;

    IMEffect_Value = IPL_AlgGetUIInfo(IPL_SEL_IMAGEEFFECT);
    Sharpness_Value = IPL_AlgGetUIInfo(IPL_SEL_SHARPNESS);
    Saturation_Value = IPL_AlgGetUIInfo(IPL_SEL_SATURATION);
    ISO_Value = IQS_GetISOIdx(MsgID);
    Zoom_Value = IQS_GetZoomIdx(MsgID);

    switch((UINT32)MsgID)
    {
        case IQS_MANUAL_TRIG:
        case IQCB_PRV_IPE_INIT:
        case IQS_AE_END:
        case IQS_IMAGE_EFFECT:
        case IQCB_PREIME_D2D_IPE_PRI:
        case IQCB_PREIME_D2D_IPE_QV:
             //enable function
            //leak random noise enable
            subf->IpeFuncEn |= (
                                 IPE_CgainEn     |      ///< Color gain function enable
                                 IPE_GBALEn      |      ///< GBAL function enable
                                 IPE_CFAINTEEn   |      ///< CFA interpolation function enable
                                 IPE_RGBLPEn     |      ///< RGB low-pass filter function enable
                                 IPE_CCREn       |      ///< Color correction function enable
                                 IPE_CSTEn       |      ///< Color space transform function enable, RGB->YCC
                                 IPE_CSTPEn      |      ///< Color space transform protect function enable, RGB->YCC
                                 IPE_Y_ENHEn     |      ///< Color component edge enhance function enable, sub-function of IPE_CADJEn
                                 IPE_RGBGAMMAEn  |      ///< RGB Gamma function enable
                                 //IPE_3DCCREn     |      ///< 3D color correction function enable
                                 IPE_CCTRLEn     |      ///< Color control function enable
                                 IPE_HADJEn      |      ///< Hue adjustment function enable
                                 IPE_CADJEn      |      ///< Color component adjust function enable
                                 IPE_Y_CONEn     |      ///< Color component Y contrast adjust function enable, sub-function of IPE_CADJEn
                                 IPE_CC_CONEn    |      ///< Color component CbCr contrast adjust function enable, sub-function of IPE_CADJEn
                                 IPE_YCC_STTEn   |      ///< Color component YCbCr substitution function enable, sub-function of IPE_CADJEn
                                 0
                               );

            //Setting parameter
            group->ipeUpdate |= (
                                IPE_SubFEn      |    ///< update func enable/disable
                                IPE_GBal_       |    ///< update g channel balance
                                IPE_CFAinter_   |    ///< update cfa interpolation
                                IPE_RGBLpf_     |    ///< update rgb low pass
                                IPE_CC_         |    ///< update color correction
                                IPE_CSTP_       |    ///< update color space transfor protection
                                IPE_EdgeExt_    |    ///< update edge extraction
                                IPE_EdgeEnh_    |    ///< update positive/negative edge enhance/inverse
                                IPE_EdgeMap_    |    ///< update edge map
                                IPE_C_Ctrl_     |    ///< update color control
                                IPE_C_Con_      |    ///< update color contrast(Y/CC)
                                IPE_C_Ofs_      |    ///< update Cb/Cr offset
                                IPE_YCCFix_     |    ///< update YCC fix replace
                                IPE_THRES_      |    ///For DIS
                                0
                              );

            if ( MsgID == IQCB_PRV_IPE_INIT || MsgID == IQCB_PREIME_D2D_IPE_PRI || MsgID == IQCB_PREIME_D2D_IPE_QV )
            {
                group->ipeUpdate |= ( IPE_CG_Gain_ | IPE_CG_Ofs_ | IPE_CG_GEffect_ );
            }

            if ( MsgID == IQCB_PRV_IPE_INIT || MsgID == IQCB_PREIME_D2D_IPE_PRI || MsgID == IQCB_PREIME_D2D_IPE_QV || MsgID == IQS_MANUAL_TRIG )
            {
                group->ipeUpdate |= ( IPE_RGBGAMMA_ | IPE_3DCC_);
            }

            //////////////////
            // AWb Gain
            //////////////////
            AWB_GetColorGian(&RGain, &GGain, &BGain);
            subf->Cg.Gain.IpeGainSel = d2f8;
            subf->Cg.Gain.R  = RGain;
            subf->Cg.Gain.Gr = GGain;
            subf->Cg.Gain.Gb = GGain;
            subf->Cg.Gain.B  = BGain;
            subf->Cg.Ofs.R  = 0;
            subf->Cg.Ofs.Gr = 0;
            subf->Cg.Ofs.Gb = 0;
            subf->Cg.Ofs.B  = 0;
            subf->Cg.Mask.GainMask = 0x3ff;

            //////////////////
            // GBal
            //////////////////
            subf->pGbal = &(IPE_Gbal[ISO_Value]);
            subf->pCFAInterpolation = &IPE_CFAInter[ISO_Value];

            //////////////////
            // Edge Ext
            //////////////////
            subf->pedgeExt          = &IPE_EdgeExt[ISO_Value];

            //////////////////
            // Edge Map
            //////////////////
            IQ_IPE_EdgeMap.edMap = IPE_EDMap[ISO_Value];
            IQ_IPE_EdgeMap.esMap = IPE_ESymMap[ISO_Value];
            IQ_IPE_EdgeMap.ESTAB_TblAddr = (UINT32)IPE_EStab[ISO_Value];
            IQ_IPE_EdgeMap.EMapOut = _EEXT;
            subf->pedgeMap          = &IQ_IPE_EdgeMap;

            //////////////////
            // Edge Enh
            //////////////////
            IQ_IPE_EdgeEnh = IPE_EdgeEnh[ISO_Value];
            IQ_IPE_EdgeEnh.EnhP = (IQ_IPE_EdgeEnh.EnhP * Sharpness[ISO_Value][Sharpness_Value])>>7;
            IQ_IPE_EdgeEnh.EnhN = (IQ_IPE_EdgeEnh.EnhN * Sharpness[ISO_Value][Sharpness_Value])>>7;
            subf->pedgeEnh          = &IQ_IPE_EdgeEnh;

            //////////////////
            // RGB lpf
            //////////////////
            subf->prgblpf           = &IPE_RGBLpf[ISO_Value];

            //////////////////
            // Color Matrix
            //////////////////
            IQ_IPE_CC.CCaccu = d2f8;
            IQ_IPE_CC.CCcoef_TblAddr = (UINT32)&Normal_CC;
            IQ_IPE_CC.SupSel = toIdentity;
            IQ_IPE_CC.Fstab_TblAddr = (UINT32)CC_fmStab[ISO_Value];
            IQ_IPE_CC.Fdtab_TblAddr = (UINT32)CC_fmDtab[ISO_Value];
            subf->pCC = &IQ_IPE_CC;

            //////////////////
            // Color Control
            //////////////////
            IQ_IPE_Cctrl.HueTab_TblAddr = (UINT32)IPE_hueTab;
            IQ_IPE_Cctrl.SatTab_TblAddr = (UINT32)IPE_satTab;
            IQ_IPE_Cctrl.IntTab_TblAddr = (UINT32)IPE_intTab;
            IQ_IPE_Cctrl.EdgTab_TblAddr = (UINT32)IPE_edgTab[ISO_Value];
            IQ_IPE_Cctrl.DDSTab_TblAddr = (UINT32)IPE_ddsTab;
            IQ_IPE_Cctrl.IntOfs = ColorEffectTable[IMEffect_Value].IntOfs;
            //IQ_IPE_Cctrl.SatOfs = (ColorEffectTable[IMEffect_Value].SatOfs * Saturation[ISO_Value][Saturation_Value])>>7;
            IQ_IPE_Cctrl.SatOfs = (ColorEffectTable[IMEffect_Value].SatOfs + Saturation[ISO_Value][Saturation_Value]);
            IQ_IPE_Cctrl.HueRotateEn = ColorEffectTable[IMEffect_Value].HueRotateEn;
            IQ_IPE_Cctrl.Suppress.EdgSel = ESD_OUT;
            IQ_IPE_Cctrl.Suppress.VdetDiv = 0x60;
            subf->pCctrl = &IQ_IPE_Cctrl;

            /////////////////
            //Image Effect
            /////////////////
            IQ_IPE_CbCrofs.Cbofs = ColorEffectTable[IMEffect_Value].CbOfs;
            IQ_IPE_CbCrofs.Crofs = ColorEffectTable[IMEffect_Value].CrOfs;
            IQ_IPE_YCCcon.YCon   = ColorEffectTable[IMEffect_Value].YCon;
            IQ_IPE_YCCcon.UVCon  = ColorEffectTable[IMEffect_Value].CCon;
            subf->pCbCrofs = &IQ_IPE_CbCrofs;
            subf->pYCCcon = &IQ_IPE_YCCcon;

            subf->pRandNoise = &IPE_NoiseParam;

            //subf->pyccmask = IPE_yccMask;
            //subf->pCST;

            ////////////////////////////
            // Color Space Protect
            ////////////////////////////
            IQS_IPE_CSTP.CSTPratio = 8;
            subf->pCstp = &IQS_IPE_CSTP;

            ////////////////////////////
            // YCC fix effect
            ////////////////////////////
            IQS_IPE_YCFixEffect = IPE_YCFixEffect;
            subf->pYccFix = &IQS_IPE_YCFixEffect;

            //subf->CCout;
            //subf->Vout;

            //////////////////
            // Color Control
            //////////////////
            IQ_IPE_RGBGAMMA.GammaTbl_TblAddr = (UINT32)IPE_GammaReorgon((UINT32 *)GammaLUT_128Tab, (UINT32 *)GammaLUT_128Tab, (UINT32 *)GammaLUT_128Tab);
            subf->pGamma = &IQ_IPE_RGBGAMMA;

            //////////////////
            // 3D Color Control
            //////////////////
            IQ_IPE_3DCC.TCC_TblAddr = (UINT32)IPE_3DCCLut;
            subf->p3d_cc = &IQ_IPE_3DCC;

            //////////////////
            // DIS
            //////////////////
            subf->EdgeThreshold.pEdgeThreshold = &IPE_EdgeThre[ISO_Value];

            ///////////////////
            // Image Effect
            ///////////////////
            switch (IMEffect_Value)
            {

                case SEL_IMAGEEFFECT_BW:
                case SEL_IMAGEEFFECT_SEPIA:
                case SEL_IMAGEEFFECT_VIVID:
                case SEL_IMAGEEFFECT_NEUTRAL:
                case SEL_IMAGEEFFECT_LOWSHARPING:
                case SEL_IMAGEEFFECT_FASION2:
                case SEL_IMAGEEFFECT_CUSTOMMANUAL:
                case SEL_IMAGEEFFECT_RED:
                case SEL_IMAGEEFFECT_GREEN:
                case SEL_IMAGEEFFECT_BLUE:
                case SEL_IMAGEEFFECT_YELLOW:
                case SEL_IMAGEEFFECT_PURPLE:
                    subf->pCctrl->IntOfs = ColorEffectTable[IMEffect_Value].IntOfs;
                    //subf->pCctrl->SatOfs = (ColorEffectTable[IMEffect_Value].SatOfs * Saturation[ISO_Value][Saturation_Value])>>7;
                    subf->pCctrl->SatOfs = (ColorEffectTable[IMEffect_Value].SatOfs + Saturation[ISO_Value][Saturation_Value]);
                    subf->pCctrl->HueRotateEn = ColorEffectTable[IMEffect_Value].HueRotateEn;
                    subf->pCctrl->Suppress.EdgSel = ESD_OUT;
                    subf->pCctrl->Suppress.VdetDiv = 0x60;
                    subf->pCbCrofs->Cbofs = ColorEffectTable[IMEffect_Value].CbOfs;
                    subf->pCbCrofs->Crofs = ColorEffectTable[IMEffect_Value].CrOfs;
                    subf->pYCCcon->YCon   = ColorEffectTable[IMEffect_Value].YCon;
                    subf->pYCCcon->UVCon  = ColorEffectTable[IMEffect_Value].CCon;
                    break;
                case SEL_IMAGEEFFECT_COLORPENCIL:
                    subf->pYccFix->Yth1.EdgeThres = IE_ColorPencil_Param[ISO_Value].EdgeThres;
                    subf->pYccFix->Yth1.Threshold = IE_ColorPencil_Param[ISO_Value].Threshold;
                    subf->pYccFix->Yth1.HIT_FixOutputEn = IE_ColorPencil_Param[ISO_Value].HIT_FixOutputEn;
                    subf->pYccFix->Yth1.NONEHIT_FixOutputEn = IE_ColorPencil_Param[ISO_Value].NONEHIT_FixOutputEn;
                    subf->pYccFix->Yth1.HIT_value = IE_ColorPencil_Param[ISO_Value].HIT_value;
                    subf->pYccFix->Yth1.NONHIT_value = IE_ColorPencil_Param[ISO_Value].NONHIT_value;
                    break;
                case SEL_IMAGEEFFECT_SKETCH:
                    subf->pYccFix->Yth1.EdgeThres = IE_PencilSketch_Param[ISO_Value].EdgeThres;
                    subf->pYccFix->Yth1.Threshold = IE_PencilSketch_Param[ISO_Value].Threshold;
                    subf->pYccFix->Yth1.HIT_FixOutputEn = IE_PencilSketch_Param[ISO_Value].HIT_FixOutputEn;
                    subf->pYccFix->Yth1.NONEHIT_FixOutputEn = IE_PencilSketch_Param[ISO_Value].NONEHIT_FixOutputEn;
                    subf->pYccFix->Yth1.HIT_value = IE_PencilSketch_Param[ISO_Value].HIT_value;
                    subf->pYccFix->Yth1.NONHIT_value = IE_PencilSketch_Param[ISO_Value].NONHIT_value;

                    subf->pedgeEnh->InvP = IE_PencilSketch_Param[ISO_Value].EInvP;
                    subf->pedgeEnh->InvN = IE_PencilSketch_Param[ISO_Value].EInvN;

                    subf->pCbCrofs->Cbofs = IE_PencilSketch_Param[ISO_Value].CbOfs;
                    subf->pCbCrofs->Crofs = IE_PencilSketch_Param[ISO_Value].CrOfs;
                    subf->pYCCcon->UVCon  = IE_PencilSketch_Param[ISO_Value].CCon;

                    break;
                case SEL_IMAGEEFFECT_FISHEYE:
                case SEL_IMAGEEFFECT_WDR:
                default:
                    break;
            }
            break;

        case IQS_AWB_END:
            //Setting parameter

            group->ipeUpdate |= ( IPE_CG_Gain_ | IPE_CG_Ofs_ | IPE_CG_GEffect_ );
            AWB_GetColorGian(&RGain, &GGain, &BGain);
            subf->Cg.Gain.IpeGainSel = d2f8;
            subf->Cg.Gain.R  = RGain;
            subf->Cg.Gain.Gr = GGain;
            subf->Cg.Gain.Gb = GGain;
            subf->Cg.Gain.B  = BGain;
            subf->Cg.Ofs.R  = 0;
            subf->Cg.Ofs.Gr = 0;
            subf->Cg.Ofs.Gb = 0;
            subf->Cg.Ofs.B  = 0;
            subf->Cg.Mask.GainMask = 0x3ff;
            break;

        case IQS_DISCOMP_ON:
            subf->IpeFuncEn |= ( IPE_EDGETHREEn );
            group->ipeUpdate |= ( IPE_SubFEn );
            break;
        case IQS_DISCOMP_OFF:
            subf->IpeFuncEn &= ~( IPE_EDGETHREEn );
            group->ipeUpdate |= ( IPE_SubFEn );
            break;

        case IQS_AF_START:
            group->ipeUpdate |= ( IPE_SubFEn | IPE_EdgeExt_ | IPE_EdgeEnh_ | IPE_EdgeMap_ | IPE_VA_ );
            subf->IpeFuncEn |= ( IPE_VACCEn );

            //////////////////
            // Edge Ext
            //////////////////
            subf->pedgeExt = &IPE_EdgeExt[ISO_Value];

            //////////////////
            // Edge Map
            //////////////////
            IQ_IPE_EdgeMap.edMap = IPE_EDMap[ISO_Value];
            IQ_IPE_EdgeMap.esMap = IPE_ESymMap[ISO_Value];
            IQ_IPE_EdgeMap.ESTAB_TblAddr = (UINT32)IPE_EStab[ISO_Value];
            IQ_IPE_EdgeMap.EMapOut = _EEXT;
            subf->pedgeMap = &IQ_IPE_EdgeMap;

            //////////////////
            // Edge Enh
            //////////////////
            IQ_IPE_EdgeEnh = IPE_EdgeEnh[ISO_Value];
            subf->pedgeEnh = &IQ_IPE_EdgeEnh;

            //////////////////
            // VA
            //////////////////
            subf->va.pVa = &IPE_VAParam[ISO_Value];
            break;

        case IQS_AF_END:
            group->ipeUpdate |= ( IPE_SubFEn  | IPE_EdgeExt_ | IPE_EdgeEnh_ | IPE_EdgeMap_ );
            subf->IpeFuncEn &= ~( IPE_VA_ );

            //////////////////
            // Edge Ext
            //////////////////
            subf->pedgeExt          = &IPE_EdgeExt[ISO_Value];

            //////////////////
            // Edge Map
            //////////////////
            IQ_IPE_EdgeMap.edMap = IPE_EDMap[ISO_Value];
            IQ_IPE_EdgeMap.esMap = IPE_ESymMap[ISO_Value];
            IQ_IPE_EdgeMap.ESTAB_TblAddr = (UINT32)IPE_EStab[ISO_Value];
            IQ_IPE_EdgeMap.EMapOut = _EEXT;
            subf->pedgeMap          = &IQ_IPE_EdgeMap;

            //////////////////
            // Edge Enh
            //////////////////
            IQ_IPE_EdgeEnh = IPE_EdgeEnh[ISO_Value];
            IQ_IPE_EdgeEnh.EnhP = (IQ_IPE_EdgeEnh.EnhP * Sharpness[ISO_Value][Sharpness_Value])>>7;
            IQ_IPE_EdgeEnh.EnhN = (IQ_IPE_EdgeEnh.EnhN * Sharpness[ISO_Value][Sharpness_Value])>>7;
            subf->pedgeEnh          = &IQ_IPE_EdgeEnh;
            break;

        case IQS_OZOOM_END:
            break;
        default :
            DBG_ERR("IPE_IQparam() param mode(%d) selection error!\r\n",MsgID);
            ret = E_SYS;
         break;
    }
    return ret;
}

static ER IME_IQparam(IQS_FLOW_MSG MsgID, IME_SUBFUNC *subf,IPL_HAL_GROUP* group)
{
    UINT32 ISO_Value, Zoom_Value, SenMode_Value, IMEffect_Value;

    IMEffect_Value = IPL_AlgGetUIInfo(IPL_SEL_IMAGEEFFECT);
    ISO_Value = IQS_GetISOIdx(MsgID);
    Zoom_Value = IQS_GetZoomIdx(MsgID);
    SenMode_Value = IQS_GetSenModeIdx(MsgID);

    switch((UINT32)MsgID)
    {
        case IQS_MANUAL_TRIG:
        case IQCB_PRV_IME_INIT:
            if ( IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_IPE_V_EN) == ENABLE )
            {
                DBG_IND("PRV Enable RetinexEn\r\n");
                subf->imeFuncEn |= (RetinexEn);
                group->imeUpdate |= (IME_Retinex_);
            }
            if ( IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_IPE_LCA_EN) == ENABLE &&
                 IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_IPEIFE2_LCA_EN) == ENABLE )
            {
                DBG_IND("PRV Enable ChromaAdaptEn\r\n");
                subf->imeFuncEn |= (ChromaAdaptEn);
                group->imeUpdate |= (IME_ChromaA_);
            }
            subf->imeFuncEn |= ( ChromaFiltEn );
            group->imeUpdate |= ( IME_SubFEn | IME_ChromaF_ | IME_3DNR_ );
            subf->TDnr.p3DNR    = &IME_3DNR[ISO_Value];
            subf->pChromaFilter = &IME_Chroma_Filter_param[ISO_Value];

            subf->Retinex.RtxMode = RTX_Outer;
            subf->Retinex.pRetinex = &IME_RetInex[IE_HDR_LEVEL];
            subf->ChromaAdap.pChromaAdaption = &IME_Chroma_Adapt_param[ISO_Value];
            switch (IMEffect_Value)
            {
                case SEL_IMAGEEFFECT_WDR:
                    subf->imeFuncEn |= (RetinexEn | RGBtoYCCEn | YCCtoRGBEn);
                    group->imeUpdate |= (IME_Retinex_);
                    subf->Retinex.RtxMode = RTX_Inner;
                    break;
                default:
                    break;
            }
            break;
        case IQS_AE_END:
            subf->imeFuncEn |= ( ChromaFiltEn );
            group->imeUpdate |= ( IME_SubFEn | IME_ChromaF_ | IME_3DNR_ );
            subf->TDnr.p3DNR    = &IME_3DNR[ISO_Value];
            subf->pChromaFilter = &IME_Chroma_Filter_param[ISO_Value];
            subf->ChromaAdap.pChromaAdaption = &IME_Chroma_Adapt_param[ISO_Value];
/*
            switch (IMEffect_Value)
            {
                case SEL_IMAGEEFFECT_WDR:
                    subf->imeFuncEn |= (RetinexEn | RGBtoYCCEn | YCCtoRGBEn);
                    group->imeUpdate |= (IME_Retinex_);
                    subf->Retinex.RtxMode = RTX_Inner;
                    subf->Retinex.pRetinex = &IME_RetInex[IE_HDR_LEVEL];
                    break;
                default:
                    break;
            }
*/
            break;
        case IQCB_PRV_IME_LCA:
            if ( IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_IPE_LCA_EN) == ENABLE &&
                 IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_IPEIFE2_LCA_EN) == ENABLE )
            {
                subf->imeFuncEn |= (ChromaAdaptEn);
                group->imeUpdate |= (IME_ChromaA_);
            }
            subf->ChromaAdap.pChromaAdaption = &IME_Chroma_Adapt_param[ISO_Value];
            break;
        case IQCB_PRV_IME_RETINEX:
            if ( IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_IPE_V_EN) == ENABLE )
            {
                DBG_IND("Post process flow, RetinexEn Enable\r\n");
                subf->imeFuncEn |= (RetinexEn);
                group->imeUpdate |= (IME_Retinex_);
                subf->Retinex.RtxMode = RTX_Outer;
                subf->Retinex.pRetinex = &IME_RetInex[IE_HDR_LEVEL];
            }
            break;
        case IQCB_D2D_IME_QVREF:
        case IQCB_PREIME_D2D_IME_QV:
            subf->imeFuncEn &= ~(RetinexEn | ChromaAdaptEn);
            group->imeUpdate |= ( IME_SubFEn );
            break;
        case IQCB_PREIME_D2D_IME_PRI:
        case IQCB_D2D_IME_QV:
            subf->imeFuncEn |= ( ChromaFiltEn );
            group->imeUpdate |= ( IME_SubFEn | IME_ChromaF_ );

            if (MsgID == IQCB_PREIME_D2D_IME_PRI)
            {
                if (IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_CAP_PRI_V_EN) == ENABLE)
                {
                    subf->imeFuncEn |= (RetinexEn);
                    group->imeUpdate |= (IME_Retinex_);
                }

                if (IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_CAP_PRI_CC_EN) == ENABLE)
                {
                    subf->imeFuncEn |= (ChromaAdaptEn);
                    group->imeUpdate |= (IME_ChromaA_);
                    DBG_IND("IME_ChromaA_ = enable, %d\r\n", ISO_Value);
                }
                //if ( (IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_IPE_LCA_EN) == DISABLE) && (group->imeUpdate &IME_ChromaA_)  )
                //{
                //    DBG_ERR("IME_IQparam(): Need to allocate buffer for LCA!\r\n");
                //}
                //subf->imeFuncEn |= (IME3DNREn);
                //group->imeUpdate |= (IME_3DNR_);
            }
            else if (MsgID == IQCB_D2D_IME_QV)
            {
                if (IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_CAP_QV_V_EN) == ENABLE)
                {
                    subf->imeFuncEn |= (RetinexEn);
                    group->imeUpdate |= (IME_Retinex_);
                }

                if (IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_CAP_QV_CC_EN) == ENABLE)
                {
                    subf->imeFuncEn |= (ChromaAdaptEn);
                    group->imeUpdate |= (IME_ChromaA_);
                    DBG_IND("IME_ChromaA_ = enable, %d\r\n", ISO_Value);
                }
            }

            //////////////////
            // IME
            //////////////////
            subf->TDnr.p3DNR    = &IME_3DNR[ISO_Value];
            subf->pChromaFilter = &IME_Chroma_Filter_param[ISO_Value];
            subf->ChromaAdap.pChromaAdaption = &IME_Chroma_Adapt_param[ISO_Value];
            DBG_IND("Lca Weight = %d\r\n", subf->ChromaAdap.pChromaAdaption->LcaWeight);
            if ( IMEffect_Value == SEL_IMAGEEFFECT_WDR )
            {   //WDR
                subf->Retinex.RtxMode = RTX_Outer;
                subf->Retinex.pRetinex = &IME_RetInex[IE_HDR_LEVEL];
            }
            else
            {   //MFR
                subf->Retinex.RtxMode = RTX_Outer;
                subf->Retinex.pRetinex = &IME_mfr[ISO_Value];
            }
            break;
        case IQS_AWB_END:
        case IQS_AF_START:
        case IQS_AF_END:
        case IQS_OZOOM_END:
            break;
        case IQS_IMAGE_EFFECT:
            // Normal Flow,
            switch (IMEffect_Value)
            {
                case SEL_IMAGEEFFECT_WDR:
                    subf->imeFuncEn |= (RetinexEn | RGBtoYCCEn | YCCtoRGBEn);
                    group->imeUpdate |= (IME_SubFEn | IME_Retinex_);
                    subf->Retinex.RtxMode = RTX_Inner;
                    subf->Retinex.pRetinex = &IME_RetInex[IE_HDR_LEVEL];
                    break;
                default:
                    subf->imeFuncEn &= (~RetinexEn);
                    group->imeUpdate |= (IME_SubFEn);
                    break;
            }
            break;
        default :
            DBG_ERR("IME_IQparam() param mode(%d) selection error!\r\n",MsgID);
            return E_SYS;
    }
    return E_OK;
}

static ER IFE2_IQparam(IQS_FLOW_MSG MsgID, IFE2_SUBFUNC *subf,IPL_HAL_GROUP* group)
{
    UINT32 ISO_Value, IMEffect_Value;
    IMEffect_Value = IPL_AlgGetUIInfo(IPL_SEL_IMAGEEFFECT);
    ISO_Value = IQS_GetISOIdx(MsgID);
    switch((UINT32)MsgID)
    {
        case IQCB_D2D_IFE2_PRI_Y:
        case IQCB_D2D_IFE2_QV_Y:
        case IQCB_PRV_IFE2_RETINEX:
            if ( IMEffect_Value == SEL_IMAGEEFFECT_WDR )
            {   //WDR
                subf->ife2FuncEn |= ( AvgFiltEn );
                subf->ife2FuncEn &= ( ~IFE2_Chroma_);
                group->ife2Update |= ( IFE2_SubFEn | IFE2_AvgFilter_ );
                IQ_IFE2_AvgFilter.Nonpack_Filter = IFE2_AvgFilter_WDR[ISO_Value];
                subf->pAvgFilter = &IQ_IFE2_AvgFilter;
            }
            else
            {   //MFR
                subf->ife2FuncEn  |= ( AvgFiltEn );
                subf->ife2FuncEn &= ( ~IFE2_Chroma_);
                group->ife2Update |= ( IFE2_SubFEn | IFE2_AvgFilter_ );
                IQ_IFE2_AvgFilter.Nonpack_Filter = IFE2_AvgFilter_y_mfr[ISO_Value];
                subf->pAvgFilter = &IQ_IFE2_AvgFilter;
            }
            break;

        case IQCB_PRV_IFE2_INIT_CC:
        case IQCB_PRV_IFE2_CC:
            subf->ife2FuncEn |= ( AvgFiltEn);
            group->ife2Update |= ( IFE2_SubFEn | IFE2_AvgFilter_ );
            if ( IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_IPE_LCA_EN) == ENABLE &&
                 IPL_CtrlGetInfor(IPL_ID_1, IPLCTRL_IPEIFE2_LCA_EN) == ENABLE )
            {
                subf->ife2FuncEn |= ( ChromaEn );
                group->ife2Update |= ( IFE2_Chroma_ );
            }
            IQ_IFE2_AvgFilter.UVpack.Pack_UFilter = IFE2_AvgFilter_cb[ISO_Value];
            IQ_IFE2_AvgFilter.UVpack.Pack_VFilter = IFE2_AvgFilter_cr[ISO_Value];
            subf->pAvgFilter = &IQ_IFE2_AvgFilter;
            subf->pChromaAdj = &IFE2_Chroma_param[ISO_Value];
            break;
        case IQCB_D2D_IFE2_QV_CC:
        case IQCB_D2D_IFE2_PRI_CC:
            subf->ife2FuncEn |= ( ChromaEn | AvgFiltEn);
            group->ife2Update |= ( IFE2_SubFEn | IFE2_Chroma_ | IFE2_AvgFilter_ );
            IQ_IFE2_AvgFilter.UVpack.Pack_UFilter = IFE2_AvgFilter_cb[ISO_Value];
            IQ_IFE2_AvgFilter.UVpack.Pack_VFilter = IFE2_AvgFilter_cr[ISO_Value];
            subf->pAvgFilter = &IQ_IFE2_AvgFilter;
            subf->pChromaAdj = &IFE2_Chroma_param[ISO_Value];
            break;
        case IQS_MANUAL_TRIG:
        case IQS_AE_END:
        case IQS_AWB_END:
        case IQS_AF_START:
        case IQS_AF_END:
        case IQS_OZOOM_END:
        case IQS_IMAGE_EFFECT:
            break;
        default:
            DBG_ERR("IFE2_IQparam() param mode(%d) selection error!\r\n",MsgID);
            break;
    }

    return E_OK;
}

///////////////////////////////////////////////
// FlowSetting Interface
///////////////////////////////////////////////
static ER IQS_SIE_IQparam(IQS_FLOW_MSG MsgID)
{
    return E_OK;
}

static ER IQS_PRE_IQparam(IQS_FLOW_MSG MsgID)
{
    ER ret = E_OK;
    PRE_SUBFUNC preSubf = {0};
    PRE pre;
    IPL_HAL_PARASET idx = IPL_CtrlGetHalSetId(IPL_ID_1);
    IPL_HAL_READ    readItem = {0};
    IPL_HAL_GROUP   group = {0};
    IPC_IQparam     Ipc_IQ;
    WAI_PRESEM;

    pre.pSubFunc = &preSubf;
    readItem.preRead = PRE_R_SubEn;
    IPH_ENG_Read(IPL_ID_1,IPL_HAL_PRE, idx, readItem, (void*)&preSubf.preFuncEn);

    ret = PRE_IQparam(MsgID, &preSubf, &group);
    if ( ret != E_OK )
    {
        SIG_PRESEM;
        return ret;
    }

    //IPH_PRE_ChgParam(idx, group, &pre);
    //IPH_ENG_Load(IPL_HAL_PRE, idx, group);
    Ipc_IQ.EngSubF.pPre_sub = &preSubf;
    Ipc_IQ.pGrp = &group;
    Ipc_IQ.Idx = idx;
    IPL_CTRLRunTimeChg_IQ(IPC_PRE_IQparam,(void*)&Ipc_IQ);
    SIG_PRESEM;
    return ret;
}

static ER IQS_DCE_IQparam(IQS_FLOW_MSG MsgID)
{
    DCE_SUBFUNC dceSubf = {0};
    IPL_HAL_GROUP group = {0};
    IPC_IQparam dce_info = {0};

    DCE_IQparam(MsgID, &dceSubf,&group);

    dce_info.EngSubF.pDce_sub = &dceSubf;
    dce_info.Idx = IPL_CtrlGetHalSetId(IPL_ID_1);
    dce_info.pGrp = &group;

    IPL_CTRLRunTimeChg(IPC_Chg_DCE,(void*)&dce_info);
    return E_OK;
}

static ER IQS_IFE_IQparam(IQS_FLOW_MSG MsgID)
{
    ER ret = E_OK;
    IFE_SUBFUNC ifeSubf = {0};
    IFE ife;
    IPL_HAL_PARASET idx = IPL_CtrlGetHalSetId(IPL_ID_1);
    IPL_HAL_READ    readBit = {0};
    IPL_HAL_GROUP   group = {0};
    IPC_IQparam     Ipc_IQ = {0};
    WAI_IFESEM;
    ife.pSubFunc = &ifeSubf;
    readBit.ifeRead = IFE_R_SubFEn;
    IPH_ENG_Read(IPL_ID_1,IPL_HAL_IFE, idx, readBit, (void*)&ifeSubf.ifeFuncEn);

    ret = IFE_IQparam(MsgID, &ifeSubf, &group);
    if ( ret != E_OK )
    {
        SIG_IFESEM;
        return ret;
    }

    //IPH_IFE_ChgParam(idx, group, &ife);
    //IPH_ENG_Load(IPL_HAL_IFE, idx, group);
    Ipc_IQ.EngSubF.pIfe_sub = &ifeSubf;
    Ipc_IQ.pGrp = &group;
    Ipc_IQ.Idx = idx;
    IPL_CTRLRunTimeChg_IQ(IPC_IFE_IQparam,(void*)&Ipc_IQ);
    SIG_IFESEM;
    return E_OK;
}

static ER IQS_IPE_IQparam(IQS_FLOW_MSG MsgID)
{
    ER ret = E_OK;
    IPE_SUBFUNC ipeSubf = {0};
    IPE ipe;
    IPL_HAL_PARASET idx = IPL_CtrlGetHalSetId(IPL_ID_1);
    IPL_HAL_READ    readBit = {0};
    IPL_HAL_GROUP   group = {0};
    IPC_IQparam     Ipc_IQ = {0};
    WAI_IPESEM;

    ipe.pSubFunc = &ipeSubf;
    //read previous function enable
    readBit.ipeRead = IPE_R_SubFEn;
    IPH_ENG_Read(IPL_ID_1,IPL_HAL_IPE, idx, readBit, (void*)&ipeSubf.IpeFuncEn);

    ret = IPE_IQparam(MsgID, &ipeSubf, &group);
    if ( ret != E_OK )
    {
        SIG_IPESEM;
        return ret;
    }

    Ipc_IQ.EngSubF.pIpe_sub = &ipeSubf;
    Ipc_IQ.pGrp = &group;
    Ipc_IQ.Idx = idx;
    IPL_CTRLRunTimeChg_IQ(IPC_IPE_IQparam,(void*)&Ipc_IQ);
    SIG_IPESEM;
    return E_OK;
}


static ER IQS_IFE2_IQparam(IQS_FLOW_MSG MsgID)
{
    ER ret = E_OK;
    IFE2_SUBFUNC ife2Subf = {0};
    IFE2 ife2;
    IPL_HAL_PARASET idx = IPL_CtrlGetHalSetId(IPL_ID_1);
    IPL_HAL_READ    readBit = {0};
    IPL_HAL_GROUP   group = {0};
    IPC_IQparam     Ipc_IQ = {0};
    WAI_IFESEM;
    ife2.pSubFunc = &ife2Subf;
    readBit.ifeRead = IFE2_R_SubFEn;
    IPH_ENG_Read(IPL_ID_1,IPL_HAL_IFE2, idx, readBit, (void*)&ife2Subf.ife2FuncEn);

    ret = IFE2_IQparam(MsgID, &ife2Subf, &group);
    if ( ret != E_OK )
    {
        SIG_IFESEM;
        return ret;
    }

    Ipc_IQ.EngSubF.pIfe2_sub = &ife2Subf;
    Ipc_IQ.pGrp = &group;
    Ipc_IQ.Idx = idx;
    IPL_CTRLRunTimeChg_IQ(IPC_IFE2_IQparam,(void*)&Ipc_IQ);
    SIG_IFESEM;
    return E_OK;
}

static ER IQS_IME_IQparam(IQS_FLOW_MSG MsgID)
{
    ER ret = E_OK;
    IME_SUBFUNC imeSubf = {0};
    IME ime;
    IPL_HAL_PARASET idx = IPL_CtrlGetHalSetId(IPL_ID_1);
    IPL_HAL_READ    readBit = {0};
    IPL_HAL_GROUP   group = {0};
    IPC_IQparam     Ipc_IQ = {0};
    WAI_IMESEM;

    ime.pSubFunc = &imeSubf;
    readBit.imeRead = IME_R_SubFEn;
    IPH_ENG_Read(IPL_ID_1,IPL_HAL_IME, idx, readBit, (void*)&imeSubf.imeFuncEn);

    ret = IME_IQparam(MsgID, &imeSubf, &group);
    if ( ret != E_OK )
    {
        SIG_IMESEM;
        return ret;
    }

    //IPH_IME_ChgParam(idx, group, &ime);
    //IPH_ENG_Load(IPL_HAL_IME, idx, group);
    Ipc_IQ.EngSubF.pIme_sub = &imeSubf;
    Ipc_IQ.pGrp = &group;
    Ipc_IQ.Idx = idx;
    IPL_CTRLRunTimeChg_IQ(IPC_IME_IQparam,(void*)&Ipc_IQ);
    SIG_IMESEM;
    return E_OK;
}

ER IQS_SettingFlowFunc(IQS_FLOW_MSG MsgID)
{
    switch((UINT32)MsgID)
    {
        case IQS_MANUAL_TRIG:
            IQS_SIE_IQparam(MsgID);
            IQS_PRE_IQparam(MsgID);
            IQS_DCE_IQparam(MsgID);
            IQS_IFE_IQparam(MsgID);
            IQS_IPE_IQparam(MsgID);
            IQS_IFE2_IQparam(MsgID);
            IQS_IME_IQparam(MsgID);
            break;
        case IQS_AWB_END:
            IQS_IPE_IQparam(MsgID);
            break;
        case IQS_AE_END:
            IQS_IFE_IQparam(MsgID);
            IQS_IPE_IQparam(MsgID);
            //IQS_IFE2_IQparam(MsgID);
            IQS_IME_IQparam(MsgID);
            break;
        case IQS_OZOOM_END:
            IQS_PRE_IQparam(MsgID);
            IQS_DCE_IQparam(MsgID);
            break;
        case IQS_DISCOMP_ON:
        case IQS_DISCOMP_OFF:
            IQS_IPE_IQparam(MsgID);
            break;
        case IQS_AF_START:
        case IQS_AF_END:
            break;

        case IQS_IMAGE_EFFECT:
            IQS_DCE_IQparam(MsgID);
            IQS_IPE_IQparam(MsgID);
            IQS_IME_IQparam(MsgID);
            break;
        default:
            DBG_ERR("^R-E- MsgID(%x)\r\n", MsgID);
            break;
    }
    return E_OK;
}


///////////////////////////////////////////////
// CBSetting Interface
///////////////////////////////////////////////

ER IQCB_SettingFlowFunc(IQS_FLOW_MSG MsgID, ENG_SUBFUNC *Info, IPL_HAL_GROUP* group)
{
    switch((UINT32)MsgID)
    {
        //preview
        case IQCB_PRV_SIE_INIT:
            break;

        case IQCB_PRV_IPE_INIT:
        case IQCB_PREIME_D2D_IPE_PRI:
        case IQCB_PREIME_D2D_IPE_QV:
            IPE_IQparam(MsgID, Info->pIpe_sub, group);
            break;

        case IQCB_PRV_PRE_INIT:
        case IQCB_PREIME_D2D_PRE_PRI:
        case IQCB_PREIME_D2D_PRE_QV:
            PRE_IQparam(MsgID, Info->pPre_sub, group);
            break;

        case IQCB_PRV_DCE_INIT:
        case IQCB_PREIME_D2D_DCE_QV:
        case IQCB_PREIME_D2D_DCE_PRI:
            DCE_IQparam(MsgID, Info->pDce_sub, group);
            break;

        case IQCB_PRV_IFE_INIT:
        case IQCB_PREIME_D2D_IFE_PRI:
        case IQCB_PREIME_D2D_IFE_QV:
            IFE_IQparam(MsgID, Info->pIfe_sub, group);
            break;

        case IQCB_PRV_IME_INIT:
        case IQCB_PRV_IME_LCA:
        case IQCB_PRV_IME_RETINEX:
            IME_IQparam(MsgID, Info->pIme_sub, group);
            break;

        case IQCB_D2D_IME_QVREF:
        case IQCB_D2D_IME_QV:  //FQV LCA & HDR
        case IQCB_PREIME_D2D_IME_QV:  //disbale LCA
        case IQCB_PREIME_D2D_IME_PRI: //enable LCA
            IME_IQparam(MsgID, Info->pIme_sub, group);
            break;

        case IQCB_PRV_IFE2_INIT_CC:
        case IQCB_PRV_IFE2_CC:
        case IQCB_PRV_IFE2_RETINEX:
        case IQCB_D2D_IFE2_QV_Y:
        case IQCB_D2D_IFE2_QV_CC:
        case IQCB_D2D_IFE2_PRI_Y:
        case IQCB_D2D_IFE2_PRI_CC:
            IFE2_IQparam(MsgID, Info->pIfe2_sub, group);
            break;

        default:
            DBG_ERR("^R-E- MsgID(%x)\r\n", MsgID);
            break;
    }
    return E_OK;
}


///////////////////////////////////////////////
// Flow Export
///////////////////////////////////////////////
UINT32 IQS_GetIFE2RetinexTime(IQS_FLOW_MSG MsgID) //PRV & CAP
{
    UINT32 ISO_Value, IMEffect_Value;
    IMEffect_Value = IPL_AlgGetUIInfo(IPL_SEL_IMAGEEFFECT);
    ISO_Value = IQS_GetISOIdx(MsgID);
    if ( IMEffect_Value == SEL_IMAGEEFFECT_WDR )
        return IFE2_Filter_Times[ISO_Value].RTXTimes;
    else
        return IFE2_Filter_Times[ISO_Value].MFRTimes;
}

UINT32 IQS_GetIFE2LcaTime(IQS_FLOW_MSG MsgID)  //PRV & CAP
{
    UINT32 ISO_Value;
    ISO_Value = IQS_GetISOIdx(MsgID);
    ////DBG_IND("LCATimes = %d", IFE2_Filter_Times[ISO_Value].LCATimes);
    return IFE2_Filter_Times[ISO_Value].LCATimes;
}

//preview
UINT32 IQS_GetRetinexMinRatio(void)
{
    //get IQS min chroma adaption ratio in streaming mode
    //for IPL prepare buffer
    return IME_RetInex[IE_HDR_LEVEL].SubRatio;
}

UINT32 IQS_GetChromaAdaptMinRatio(void)
{
    //get IQS min chroma adaption ratio in streaming mode
    //for IPL prepare buffer
    UINT32 MinRatio = 0xf;
    UINT32 i;
    for ( i=0; i<Total_ISONum; i++ )
    {
        if ( MinRatio > IME_Chroma_Adapt_param[i].SubRatio )
            MinRatio= IME_Chroma_Adapt_param[i].SubRatio;
    }
    return MinRatio;
}

UINT32 IQS_PRV_IsChromaAdaptEn(void)
{
    //get IQS chroma adaption on/off in streaming mode
    //for IPL prepare buffer
    return ENABLE;
}

UINT32 IQS_CAPPRI_GetLCARefImgRatio(void)
{
    UINT32 ISO_Value;
    ISO_Value  = IQS_GetISOIdx(IQCB_CAP_PRI_START);
    return IME_Chroma_Adapt_param[ISO_Value].SubRatio;
}

UINT32 IQS_CAPQV_GetLCARefImgRatio(void)
{
    UINT32 ISO_Value;
    ISO_Value  = IQS_GetISOIdx(IQCB_CAP_QV_START);
    return IME_Chroma_Adapt_param[ISO_Value].SubRatio;
}

UINT32 IQS_CAPPRI_GetRetinexRefImgRatio(void)
{
    UINT32 ISO_Value, IMEffect_Value;
    IMEffect_Value = IPL_AlgGetUIInfo(IPL_SEL_IMAGEEFFECT);
    ISO_Value  = IQS_GetISOIdx(IQCB_CAP_PRI_START);
    if ( IMEffect_Value == SEL_IMAGEEFFECT_WDR )
    {
        return IME_RetInex[IE_HDR_LEVEL].SubRatio;
    }
    else
    {
        return IME_mfr[ISO_Value].SubRatio;
    }
}

UINT32 IQS_CAPQV_GetRetinexRefImgRatio(void)
{
    UINT32 ISO_Value, IMEffect_Value;
    IMEffect_Value = IPL_AlgGetUIInfo(IPL_SEL_IMAGEEFFECT);
    ISO_Value  = IQS_GetISOIdx(IQCB_CAP_QV_START);
    if ( IMEffect_Value == SEL_IMAGEEFFECT_WDR )
    {
        return IME_RetInex[IE_HDR_LEVEL].SubRatio;
    }
    else
    {
        return IME_mfr[ISO_Value].SubRatio;
    }
}

UINT32 IQS_CAPQV_IsChromaAdaptEn(void)
{
    UINT32 ISO_Value;
    ISO_Value  = IQS_GetISOIdx(IQCB_CAP_QV_START);
    if ( IFE2_Filter_Times[ISO_Value].LCATimes == 0 )
    {
        return DISABLE;
    }
    else
    {
        return ENABLE;
    }
}

UINT32 IQS_CAPQV_IsRetinexEn(void)
{
    //get IQS chroma adaption on/off in streaming mode
    //for IPL prepare buffer
    UINT32 ISO_Value, IMEffect_Value;
    IMEffect_Value = IPL_AlgGetUIInfo(IPL_SEL_IMAGEEFFECT);
    ISO_Value  = IQS_GetISOIdx(IQCB_CAP_QV_START);
    if ( IMEffect_Value == SEL_IMAGEEFFECT_WDR )
    {
        if ( IFE2_Filter_Times[ISO_Value].RTXTimes == 0 )
        {
            DBG_ERR("^RMust set RTXTimes for SEL_IMAGEEFFECT_WDR\r\n");
            return DISABLE;
        }
        else
            return ENABLE;
    }
    else
    {
        if ( IFE2_Filter_Times[ISO_Value].MFRTimes == 0 )
        {
            return DISABLE;
        }
        else
        {
            return ENABLE;
        }
    }
}

UINT32 IQS_CAPPRI_IsChromaAdaptEn(void)
{
    UINT32 ISO_Value;
    ISO_Value  = IQS_GetISOIdx(IQCB_CAP_PRI_START);
    if ( IFE2_Filter_Times[ISO_Value].LCATimes == 0 )
    {
        return DISABLE;
    }
    else
    {
        return ENABLE;
    }
}

UINT32 IQS_CAPPRI_IsRetinexEn(void)
{
    //get IQS chroma adaption on/off in streaming mode
    //for IPL prepare buffer
    UINT32 ISO_Value, IMEffect_Value;
    IMEffect_Value = IPL_AlgGetUIInfo(IPL_SEL_IMAGEEFFECT);
    ISO_Value  = IQS_GetISOIdx(IQCB_CAP_PRI_START);
    if ( IMEffect_Value == SEL_IMAGEEFFECT_WDR )
    {
        if ( IFE2_Filter_Times[ISO_Value].RTXTimes == 0 )
        {
            DBG_ERR("^RMust set RTXTimes for SEL_IMAGEEFFECT_WDR\r\n");
            return DISABLE;
        }
        else
        {
            return ENABLE;
        }
    }
    else
    {
        if ( IFE2_Filter_Times[ISO_Value].MFRTimes == 0 )
        {
            return DISABLE;
        }
        else
        {
            return ENABLE;
        }
    }
}

#endif
