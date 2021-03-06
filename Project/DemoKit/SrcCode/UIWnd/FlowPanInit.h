//This source code is generated by UI Designer Studio.

#ifndef FLOWPANINIT_H
#define FLOWPANINIT_H

#include "UIFramework.h"

extern VControl FlowPanInitCtrl;//Panel type 

extern VControl PanInitSelRightCtrl;//Status type 

typedef enum
{
PanInitSelRight_ICONID_PANARAMA_START_R1,
PanInitSelRight_MAX
}PanInitSelRight_Setting;

extern VControl PanInitUnselRightCtrl;//Status type 

typedef enum
{
PanInitUnselRight_ICONID_PANARAMA_START_R1_3,
PanInitUnselRight_MAX
}PanInitUnselRight_Setting;

extern VControl PanInitSelLeftCtrl;//Status type 

typedef enum
{
PanInitSelLeft_ICONID_PANARAMA_START_L1,
PanInitSelLeft_MAX
}PanInitSelLeft_Setting;

extern VControl PanInitUnselLeftCtrl;//Status type 

typedef enum
{
PanInitUnselLeft_ICONID_PANARAMA_START_L1_3,
PanInitUnselLeft_MAX
}PanInitUnselLeft_Setting;

extern VControl PanInitPictNumberCtrl;//Static type 

//---------------------FlowPanInitCtrl User Export---------------------------
typedef enum
{
    PanCapDir_L2R,
    PanCapDir_R2L,
    PanCapDir_MAX
}PanCapDir_Setting;


typedef enum
{
    FLOWPANINIT_CHILD_WND_NULL        = 0x00,
    FLOWPANINIT_CHILD_WND_MENU,
    FLOWPANINIT_CHILD_WND_DSCMODE,
    FLOWPANINIT_CHILD_WND_WRNSTORAGE,
    FLOWPANINIT_CHILD_WND_PANDIR,
    FLOWPANINIT_CHILD_WND_SETUPLANG,
    FLOWPANINIT_CHILD_WND_SETUPDATE,
    FLOWPANINIT_CHILD_WND_SETUPFORMAT
} FLOWPANINIT_CHILD_WND_MODE;

typedef struct _UIFlowInfoTypePanInit
{
    BOOL                       isDispIcon;
    UINT32                     PictNumber;
    UINT8                      PictNumberStr[6];       //Picture number display string
    UINT32                     uiPanInitTimerID;       //Timer ID for pan-capture
    UINT32                     uiPanCapDir;            //Directrion of pan-capture
    UINT32                     uiChildWnd;
    UINT32                     uiWarnType;             //Warn type
} UIFlowInfoTypePanInit;

extern UINT32 UIFlowWndPanInit_GetDir(void);
#endif
