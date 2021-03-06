/**
    Lens calibration item

    @file       CalLens.c
    @ingroup    calibration
    @note       Nothing (or anything need to be mentioned).

    Copyright   Novatek Microelectronics Corp. 2011.  All rights reserved.
*/

#include "CalibrationInt.h"
#include "CalLens.h"
#include "Debug.h"
#include "UIFlow.h"

_ALIGNED(4) volatile CALLENS_INFO gCalLens_Info = {0};

BOOL CalLens_IsAdjust(void)
{
    if(gCalLens_Info.bFarAdjust && gCalLens_Info.bNearAdjust)
        return TRUE;
    else
        return FALSE;
}

BOOL CalLens_IsFarAdjust(void)
{
    if(gCalLens_Info.bFarAdjust)
        return TRUE;
    else
        return FALSE;
}

BOOL CalLens_IsNearAdjust(void)
{
    if(gCalLens_Info.bNearAdjust)
        return TRUE;
    else
        return FALSE;
}

UINT32 CalLens_GetFocusBL(void)
{
    return gCalLens_Info.uiLensFocusBL;
}

UINT32 CalLens_GetZoomBL(void)
{
    return gCalLens_Info.uiLensZoomBL;
}

INT32 CalLens_ReadCalData(void)
{
    PPSTORE_SECTION_HANDLE  pSection;
    INT32 retValue;

    // Enable PStore
    //PStore_EnablePS();
    #if 1
    if ((pSection = PStore_OpenSection(PS_CAL_LENS, PS_RDONLY)) != E_PS_SECHDLER)
    {
        PStore_ReadSection((UINT8 *)&gCalLens_Info, 0, sizeof(gCalLens_Info), pSection);
        PStore_CloseSection(pSection);
        retValue = CALLENS_STA_OK;
    }
    else
    {
        debug_err(("%s: Pstore open to read FAIL\r\n", __func__));
        memset((UINT8 *)&gCalLens_Info, 0, sizeof(gCalLens_Info));
        retValue = CALLENS_STA_FAIL;
    }
    #endif
    // Disable PStore
    //PStore_DisablePS();

    //debug_err(("%s: status = %d\r\n", __func__, retValue));

    return retValue;
}

INT32 CalLens_WriteCalData(void)
{
    PPSTORE_SECTION_HANDLE  pSection;
    INT32 retValue;

    //#NT#2014/05/20#KS Hung -begin
    #if (_DUAL_CARD_FUNC_ == ENABLE)
    //FileSys_Close(FST_TIME_INFINITE);
    System_OnStrgInit_PS();
    #endif
    //#NT#2014/05/20#KS Hung -end

    // Enable PStore
    //PStore_EnablePS();
    #if 1
    if ((pSection = PStore_OpenSection(PS_CAL_LENS, PS_RDWR|PS_CREATE)) != E_PS_SECHDLER)
    {
        PStore_WriteSection((UINT8 *)&gCalLens_Info, 0, sizeof(gCalLens_Info), pSection);
        PStore_CloseSection(pSection);
        retValue = CALLENS_STA_OK;
    }
    else
    {
        debug_err(("%s: Pstore open to write FAIL\r\n", __func__));
        retValue = CALLENS_STA_FAIL;
    }

    // Disable PStore
    //PStore_DisablePS();
    #endif
    debug_err(("%s: status = %d\r\n", __func__, retValue));

    //#NT#2013/07/17#KS Hung -begin
    #if (SDIO2_SPI_SHARE_PIN == ENABLE)
    //FileSys_Open(GxStrg_GetDevice(0),FST_TIME_INFINITE);
    #endif
    //#NT#2013/07/17#KS Hung -end

    return retValue;
}

void CalLens_ResetCalData(void)
{
    memset((UINT8 *)&gCalLens_Info, 0, sizeof(gCalLens_Info));
}

BOOL CalLens_IsTestMissStep(UINT32 *pZoomMissStep, UINT32 *pFocusMissStep)
{
    if(gCalLens_Info.bFocusStepMissTest == 1)
    {
        if(pZoomMissStep != NULL)
            *pZoomMissStep = gCalLens_Info.uiZoomMissStep;

        if(pFocusMissStep != NULL)
            *pFocusMissStep = gCalLens_Info.uiFocusMissStep;

        return TRUE;
    }
    else
        return FALSE;
}

void Cal_AFFar(void)
{
    Cal_RunItem(CAL_ITEM_AF_FAR);
}

void Cal_AFNear(void)
{
    Cal_RunItem(CAL_ITEM_AF_NEAR);
}

void Cal_FocusComp(void)
{
    Cal_RunItem(CAL_ITEM_CAPFOCUSCOMPENSITE);
}

void Cal_FocusOffset(void)
{
    Cal_RunItem(CAL_ITEM_FOCUSOFFSET);
}

void Cal_LENS(void)
{
    Cal_RunItem(CAL_ITEM_LENS);
}

void Cal_MShutterSWTest(void)
{
    Cal_RunItem(CAL_ITEM_MSHUTTER_SW_TEST);
}
void Cal_ApertureSWTest(void)
{
    Cal_RunItem(CAL_ITEM_APERTURE_SW_TEST);
}
void Cal_FAETest(void)
{
    Cal_RunItem(CAL_ITEM_FAE_TEST);
}
void Cal_ZoomSpeedTest(void)
{
    Cal_RunItem(CAL_ITEM_ZOOM_SPEED_TEST);
}
void Cal_ZoomStepMissTest(void)
{
    Cal_RunItem(CAL_ITEM_ZOOM_STEPMISS_TEST);
}
void Cal_ZoomStop2PR(void)
{
    Cal_RunItem(CAL_ITEM_ZOOM_STOP2PR);
}
void Cal_FocusStepMissTest(void)
{
    Cal_RunItem(CAL_ITEM_FOCUS_STEPMISS_TEST);
}
void Cal_LensQualityTest(void)
{
    Cal_RunItem(CAL_ITEM_LENS_QUALITY_TEST);
}
void Cal_AFTest(void)
{
    Cal_RunItem(CAL_ITEM_AF_TEST);
}

// EOF
