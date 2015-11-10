//This source code is generated by UI Designer Studio.

#ifndef UIFLOWWNDAIR_WARINGRES_H
#define UIFLOWWNDAIR_WARINGRES_H

#include "UIFramework.h"
#include "UIFrameworkExt.h"
#include "UIGraphics.h"
#include "NVTToolCommand.h"
#include "UIDisplayUtil.h"
//------------------------------------------------------------

SHOW_ITEM_IMAGE(CMD_Image,Image2, 0, 0, 319,239, ICON_AIR_BG,83886080,0,0,0,0,0,0,0)
SHOW_ITEM_RECT(CMD_Rectangle,Skin1Rect,0,0,319,239,0,0,18,18,0,0,0)
SHOW_MAP_BEGIN(Skin1)
SHOW_MAP_BODY(Skin1Rect)
SHOW_MAP_BODY(Image2)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin1,0,0,319,239)

SHOW_MAP_BEGIN(Skin4)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin4,0,0,52,27)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text6,1,6,52,21,STRID_NULL,0,0,0,0,2,1,1,0,0,18,0,0,0,0)
SHOW_MAP_BEGIN(Normal3)
SHOW_MAP_BODY(Skin4)
SHOW_MAP_BODY(Text6)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Normal3,130,107,182,134)

SHOW_MAP_BEGIN(UIFlowWndAIR_PW25_value)
SHOW_MAP_BODY(Normal3)
SHOW_MAP_END

DECLARE_EVENT(UIFlowWndAIR_PW25_value)
CREATE_STATIC_DATA(UIFlowWndAIR_PW25_value,STRID_MODE)
CREATE_STATIC_CTRL(UIFlowWndAIR_PW25_value,0,130,107,182,134)

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

SHOW_MAP_BEGIN(Skin9)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin9,0,0,65,46)

SHOW_ITEM_IMAGE(CMD_Image|CMD_ITEM,Icon10, 0, 1, 64,45, ICONID_NULL,83886080,0,0,0,0,0,17,0)
SHOW_MAP_BEGIN(Normal8)
SHOW_MAP_BODY(Skin9)
SHOW_MAP_BODY(Icon10)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Normal8,121,59,186,105)

CREATE_STATE_ITEM_DATA(ICON_AIR_PM_GOOD11,STRID_NULL,ICON_AIR_PM_GOOD,NULL) 
CREATE_STATE_ITEM_DATA(ICON_AIR_PM_NORMAL12,STRID_NULL,ICON_AIR_PM_NORMAL,NULL) 
CREATE_STATE_ITEM_DATA(ICON_AIR_PM_BAD13,STRID_NULL,ICON_AIR_PM_BAD,NULL) 
SHOW_MAP_BEGIN(UIFlowWndAIR_Quality)
SHOW_MAP_BODY(Normal8)
SHOW_MAP_END

DECLARE_EVENT(UIFlowWndAIR_Quality)
STATE_LIST_BEGIN(UIFlowWndAIR_Quality)
STATE_LIST_ITEM(ICON_AIR_PM_GOOD11)
STATE_LIST_ITEM(ICON_AIR_PM_NORMAL12)
STATE_LIST_ITEM(ICON_AIR_PM_BAD13)
STATE_LIST_END

CREATE_STATE_DATA(UIFlowWndAIR_Quality,0)
CREATE_STATE_CTRL(UIFlowWndAIR_Quality,0,121,59,186,105)

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

SHOW_MAP_BEGIN(Skin15)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin15,0,0,47,27)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text17,1,6,46,21,STRID_NULL,0,0,0,0,2,1,1,0,0,18,0,0,0,0)
SHOW_MAP_BEGIN(Normal14)
SHOW_MAP_BODY(Skin15)
SHOW_MAP_BODY(Text17)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Normal14,142,144,189,171)

SHOW_MAP_BEGIN(UIFlowWndAIR_DetTime_value)
SHOW_MAP_BODY(Normal14)
SHOW_MAP_END

DECLARE_EVENT(UIFlowWndAIR_DetTime_value)
CREATE_STATIC_DATA(UIFlowWndAIR_DetTime_value,STRID_MODE)
CREATE_STATIC_CTRL(UIFlowWndAIR_DetTime_value,0,142,144,189,171)

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

SHOW_MAP_BEGIN(Skin19)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin19,0,0,177,41)

SHOW_ITEM_IMAGE(CMD_Image,Image22, 1, 2, 54,37, ICON_AIR_HIGH_SPEED,83886080,0,0,0,0,0,17,0)
SHOW_MAP_BEGIN(Skin21)
SHOW_MAP_BODY(Image22)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin21,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text24,2,10,35,21,STRID_NULL,0,0,0,0,2,1,1,0,0,17,0,0,0,0)
SHOW_MAP_BEGIN(Normal20)
SHOW_MAP_BODY(Skin21)
SHOW_MAP_BODY(Text24)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Normal20,225,190,279,229)

SHOW_ITEM_RECT(CMD_Rectangle,Rect28,5,8,51,32,272,0,0,4,0,0,0)
SHOW_ITEM_IMAGE(CMD_Image,Image29, 1, 2, 54,37, ICON_AIR_HIGH_SPEED,83886080,0,0,0,0,0,17,0)
SHOW_MAP_BEGIN(Skin26)
SHOW_MAP_BODY(Rect28)
SHOW_MAP_BODY(Image29)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin26,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text31,2,10,35,21,STRID_NULL,0,0,0,0,14,1,1,0,0,17,0,0,0,0)
SHOW_MAP_BEGIN(Focused25)
SHOW_MAP_BODY(Skin26)
SHOW_MAP_BODY(Text31)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Focused25,225,190,279,229)

SHOW_ITEM_RECT(CMD_Rectangle,Skin33Rect,0,0,54,39,0,0,255,255,0,0,0)
SHOW_MAP_BEGIN(Skin33)
SHOW_MAP_BODY(Skin33Rect)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin33,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text35,2,10,35,21,STRID_NULL,0,0,0,0,2,1,1,0,0,17,0,0,0,0)
SHOW_MAP_BEGIN(Normal_Disable32)
SHOW_MAP_BODY(Skin33)
SHOW_MAP_BODY(Text35)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Normal_Disable32,225,190,279,229)

SHOW_ITEM_RECT(CMD_Rectangle,Skin37Rect,0,0,54,39,0,0,255,255,0,0,0)
SHOW_MAP_BEGIN(Skin37)
SHOW_MAP_BODY(Skin37Rect)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin37,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text39,2,10,35,21,STRID_NULL,0,0,0,0,2,1,1,0,0,17,0,0,0,0)
SHOW_MAP_BEGIN(Focused_Disable36)
SHOW_MAP_BODY(Skin37)
SHOW_MAP_BODY(Text39)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Focused_Disable36,225,190,279,229)

SHOW_MAP_BEGIN(Skin41)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin41,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text43,2,10,35,21,STRID_NULL,0,0,0,0,2,1,1,256,0,0,0,0,0,0)
SHOW_MAP_BEGIN(Pressed40)
SHOW_MAP_BODY(Skin41)
SHOW_MAP_BODY(Text43)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Pressed40,225,190,279,229)

CREATE_BUTTON_ITEM_DATA(STRID_NULL_44,STRID_NULL_,ICONID_NULL,STATUS_ENABLE,NULL) 
SHOW_MAP_BEGIN(UIFlowWndAIR_HIGH_SPEED_WIN)
SHOW_MAP_BODY(Normal20)
SHOW_MAP_BODY(Focused25)
SHOW_MAP_BODY(Normal_Disable32)
SHOW_MAP_BODY(Focused_Disable36)
SHOW_MAP_BODY(Pressed40)
SHOW_MAP_END

DECLARE_EVENT(UIFlowWndAIR_HIGH_SPEED_WIN)
BUTTON_LIST_BEGIN(UIFlowWndAIR_HIGH_SPEED_WIN)
BUTTON_LIST_ITEM(STRID_NULL_44)
BUTTON_LIST_END

CREATE_BUTTON_DATA(UIFlowWndAIR_HIGH_SPEED_WIN,BTN_DRAW_IMAGE)

CREATE_BUTTON_CTRL(UIFlowWndAIR_HIGH_SPEED_WIN,UIFlowWndAIR_HIGH_SPEED_WIN,0,109,1,163,40)
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

SHOW_ITEM_IMAGE(CMD_Image,Image47, 1, 2, 54,37, ICON_AIR_MID_SPEED,83886080,0,0,0,0,0,17,0)
SHOW_MAP_BEGIN(Skin46)
SHOW_MAP_BODY(Image47)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin46,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text49,2,10,35,21,STRID_NULL,0,0,0,0,2,1,1,0,0,17,0,0,0,0)
SHOW_MAP_BEGIN(Normal45)
SHOW_MAP_BODY(Skin46)
SHOW_MAP_BODY(Text49)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Normal45,171,190,225,229)

SHOW_ITEM_RECT(CMD_Rectangle,Rect53,5,8,52,32,272,0,0,4,0,0,0)
SHOW_ITEM_IMAGE(CMD_Image,Image54, 1, 2, 54,37, ICON_AIR_MID_SPEED,83886080,0,0,0,0,0,17,0)
SHOW_MAP_BEGIN(Skin51)
SHOW_MAP_BODY(Rect53)
SHOW_MAP_BODY(Image54)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin51,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text56,2,10,35,21,STRID_NULL,0,0,0,0,14,1,1,0,0,17,0,0,0,0)
SHOW_MAP_BEGIN(Focused50)
SHOW_MAP_BODY(Skin51)
SHOW_MAP_BODY(Text56)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Focused50,171,190,225,229)

SHOW_ITEM_RECT(CMD_Rectangle,Skin58Rect,0,0,54,39,0,0,255,255,0,0,0)
SHOW_MAP_BEGIN(Skin58)
SHOW_MAP_BODY(Skin58Rect)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin58,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text60,2,10,35,21,STRID_NULL,0,0,0,0,2,1,1,0,0,17,0,0,0,0)
SHOW_MAP_BEGIN(Normal_Disable57)
SHOW_MAP_BODY(Skin58)
SHOW_MAP_BODY(Text60)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Normal_Disable57,171,190,225,229)

SHOW_ITEM_RECT(CMD_Rectangle,Skin62Rect,0,0,54,39,0,0,255,255,0,0,0)
SHOW_MAP_BEGIN(Skin62)
SHOW_MAP_BODY(Skin62Rect)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin62,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text64,2,10,35,21,STRID_NULL,0,0,0,0,2,1,1,0,0,17,0,0,0,0)
SHOW_MAP_BEGIN(Focused_Disable61)
SHOW_MAP_BODY(Skin62)
SHOW_MAP_BODY(Text64)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Focused_Disable61,171,190,225,229)

SHOW_MAP_BEGIN(Skin66)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin66,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text68,2,10,35,21,STRID_NULL,0,0,0,0,2,1,1,256,0,0,0,0,0,0)
SHOW_MAP_BEGIN(Pressed65)
SHOW_MAP_BODY(Skin66)
SHOW_MAP_BODY(Text68)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Pressed65,171,190,225,229)

CREATE_BUTTON_ITEM_DATA(STRID_NULL_69,STRID_NULL_,ICONID_NULL,STATUS_ENABLE,NULL) 
SHOW_MAP_BEGIN(UIFlowWndAIR_MID_SPEED_WIN)
SHOW_MAP_BODY(Normal45)
SHOW_MAP_BODY(Focused50)
SHOW_MAP_BODY(Normal_Disable57)
SHOW_MAP_BODY(Focused_Disable61)
SHOW_MAP_BODY(Pressed65)
SHOW_MAP_END

DECLARE_EVENT(UIFlowWndAIR_MID_SPEED_WIN)
BUTTON_LIST_BEGIN(UIFlowWndAIR_MID_SPEED_WIN)
BUTTON_LIST_ITEM(STRID_NULL_69)
BUTTON_LIST_END

CREATE_BUTTON_DATA(UIFlowWndAIR_MID_SPEED_WIN,BTN_DRAW_IMAGE)

CREATE_BUTTON_CTRL(UIFlowWndAIR_MID_SPEED_WIN,UIFlowWndAIR_MID_SPEED_WIN,0,55,1,109,40)
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

SHOW_ITEM_IMAGE(CMD_Image,Image72, 1, 2, 54,37, ICON_AIR_LOW_SPEED,83886080,0,0,0,0,0,17,0)
SHOW_MAP_BEGIN(Skin71)
SHOW_MAP_BODY(Image72)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin71,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text74,2,10,35,21,STRID_NULL,0,0,0,0,2,1,1,0,0,17,0,0,0,0)
SHOW_MAP_BEGIN(Normal70)
SHOW_MAP_BODY(Skin71)
SHOW_MAP_BODY(Text74)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Normal70,117,190,171,229)

SHOW_ITEM_RECT(CMD_Rectangle,Rect78,5,8,51,32,272,0,0,4,0,0,0)
SHOW_ITEM_IMAGE(CMD_Image,Image79, 1, 2, 54,37, ICON_AIR_LOW_SPEED,83886080,0,0,0,0,0,17,0)
SHOW_MAP_BEGIN(Skin76)
SHOW_MAP_BODY(Rect78)
SHOW_MAP_BODY(Image79)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin76,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text81,2,10,35,21,STRID_NULL,0,0,0,0,14,1,1,0,0,17,0,0,0,0)
SHOW_MAP_BEGIN(Focused75)
SHOW_MAP_BODY(Skin76)
SHOW_MAP_BODY(Text81)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Focused75,117,190,171,229)

SHOW_ITEM_RECT(CMD_Rectangle,Skin83Rect,0,0,54,39,0,0,255,255,0,0,0)
SHOW_MAP_BEGIN(Skin83)
SHOW_MAP_BODY(Skin83Rect)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin83,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text85,2,10,35,21,STRID_NULL,0,0,0,0,2,1,1,0,0,17,0,0,0,0)
SHOW_MAP_BEGIN(Normal_Disable82)
SHOW_MAP_BODY(Skin83)
SHOW_MAP_BODY(Text85)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Normal_Disable82,117,190,171,229)

SHOW_ITEM_RECT(CMD_Rectangle,Skin87Rect,0,0,54,39,0,0,255,255,0,0,0)
SHOW_MAP_BEGIN(Skin87)
SHOW_MAP_BODY(Skin87Rect)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin87,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text89,2,10,35,21,STRID_NULL,0,0,0,0,2,1,1,0,0,17,0,0,0,0)
SHOW_MAP_BEGIN(Focused_Disable86)
SHOW_MAP_BODY(Skin87)
SHOW_MAP_BODY(Text89)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Focused_Disable86,117,190,171,229)

SHOW_MAP_BEGIN(Skin91)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin91,0,0,54,39)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text93,2,10,35,21,STRID_NULL,0,0,0,0,2,1,1,256,0,0,0,0,0,0)
SHOW_MAP_BEGIN(Pressed90)
SHOW_MAP_BODY(Skin91)
SHOW_MAP_BODY(Text93)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Pressed90,117,190,171,229)

CREATE_BUTTON_ITEM_DATA(STRID_NULL_94,STRID_NULL_,ICONID_NULL,STATUS_ENABLE,NULL) 
SHOW_MAP_BEGIN(UIFlowWndAIR_LOW_SPEED_WIN)
SHOW_MAP_BODY(Normal70)
SHOW_MAP_BODY(Focused75)
SHOW_MAP_BODY(Normal_Disable82)
SHOW_MAP_BODY(Focused_Disable86)
SHOW_MAP_BODY(Pressed90)
SHOW_MAP_END

DECLARE_EVENT(UIFlowWndAIR_LOW_SPEED_WIN)
BUTTON_LIST_BEGIN(UIFlowWndAIR_LOW_SPEED_WIN)
BUTTON_LIST_ITEM(STRID_NULL_94)
BUTTON_LIST_END

CREATE_BUTTON_DATA(UIFlowWndAIR_LOW_SPEED_WIN,BTN_DRAW_IMAGE)

CREATE_BUTTON_CTRL(UIFlowWndAIR_LOW_SPEED_WIN,UIFlowWndAIR_LOW_SPEED_WIN,0,1,1,55,40)
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

SHOW_MAP_BEGIN(UIFlowWndAIR_Tab)
SHOW_MAP_BODY(Skin19)
SHOW_MAP_END

DECLARE_EVENT(UIFlowWndAIR_Tab)
CTRL_LIST_BEGIN(UIFlowWndAIR_Tab)
CTRL_LIST_ITEM(UIFlowWndAIR_HIGH_SPEED_WIN)
CTRL_LIST_ITEM(UIFlowWndAIR_MID_SPEED_WIN)
CTRL_LIST_ITEM(UIFlowWndAIR_LOW_SPEED_WIN)
CTRL_LIST_END

CREATE_TAB_DATA(UIFlowWndAIR_Tab,0)

CREATE_TAB_CTRL(UIFlowWndAIR_Tab,UIFlowWndAIR_Tab,0,116,189,293,230)
SHOW_MAP_BEGIN(UIFlowWndAIR_Waring)
SHOW_MAP_BODY(Skin1)
SHOW_MAP_END

DECLARE_EVENT(UIFlowWndAIR_Waring)
DECLARE_CTRL_LIST(UIFlowWndAIR_Waring)
CREATE_CTRL(UIFlowWndAIR_Waring,UIFlowWndAIR_Waring,CTRL_WND,NULL,0 ,0,0,319,239)
#endif