//This source code is generated by UI Designer Studio.

#ifndef UIMENUWNDWIFIMOBILELINKOKRES_H
#define UIMENUWNDWIFIMOBILELINKOKRES_H

#include "UIFramework.h"
#include "UIFrameworkExt.h"
#include "UIGraphics.h"
#include "NVTToolCommand.h"
#include "UIDisplayUtil.h"
//------------------------------------------------------------

SHOW_ITEM_RECT(CMD_Rectangle,Skin1Rect,0,0,319,239,0,0,0,0,0,0,0)
SHOW_MAP_BEGIN(Skin1)
SHOW_MAP_BODY(Skin1Rect)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin1,0,0,319,239)

SHOW_ITEM_RECT(CMD_Rectangle,Skin3Rect,0,0,201,21,0,0,0,0,0,0,0)
SHOW_MAP_BEGIN(Skin3)
SHOW_MAP_BODY(Skin3Rect)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin3,0,0,201,21)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text5,0,0,201,21,STRID_NULL,0,0,0,0,2,1,1,0,0,16,0,0,0,0)
SHOW_MAP_BEGIN(Normal2)
SHOW_MAP_BODY(Skin3)
SHOW_MAP_BODY(Text5)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Normal2,84,74,285,95)

SHOW_MAP_BEGIN(UIMenuWndWiFiMobileLinkOK_StaticTXT_LinkSts)
SHOW_MAP_BODY(Normal2)
SHOW_MAP_END

DECLARE_EVENT(UIMenuWndWiFiMobileLinkOK_StaticTXT_LinkSts)
CREATE_STATIC_DATA(UIMenuWndWiFiMobileLinkOK_StaticTXT_LinkSts,STRID_NULL_)
CREATE_STATIC_CTRL(UIMenuWndWiFiMobileLinkOK_StaticTXT_LinkSts,0,84,74,285,95)

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

SHOW_MAP_BEGIN(Skin8)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin8,0,0,91,27)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text10,1,6,270,21,STRID_NULL,0,0,0,0,7,1,1,256,0,0,0,0,0,0)
SHOW_MAP_BEGIN(Normal7)
SHOW_MAP_BODY(Skin8)
SHOW_MAP_BODY(Text10)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Normal7,36,192,127,219)

SHOW_MAP_BEGIN(Skin12)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin12,0,0,91,27)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text14,1,6,270,21,STRID_NULL,0,0,0,0,1,1,1,256,0,0,0,0,0,0)
SHOW_MAP_BEGIN(Focused11)
SHOW_MAP_BODY(Skin12)
SHOW_MAP_BODY(Text14)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Focused11,36,192,127,219)

SHOW_MAP_BEGIN(Skin16)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin16,0,0,91,27)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text18,1,6,270,21,STRID_NULL,0,0,0,0,1,1,1,256,0,0,0,0,0,0)
SHOW_MAP_BEGIN(Normal_Disable15)
SHOW_MAP_BODY(Skin16)
SHOW_MAP_BODY(Text18)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Normal_Disable15,36,192,127,219)

SHOW_MAP_BEGIN(Skin20)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin20,0,0,91,27)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text22,1,6,270,21,STRID_NULL,0,0,0,0,1,1,1,256,0,0,0,0,0,0)
SHOW_MAP_BEGIN(Focused_Disable19)
SHOW_MAP_BODY(Skin20)
SHOW_MAP_BODY(Text22)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Focused_Disable19,36,192,127,219)

SHOW_MAP_BEGIN(Skin24)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin24,0,0,91,27)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text26,1,6,270,21,STRID_NULL,0,0,0,0,7,1,1,256,0,0,0,0,0,0)
SHOW_MAP_BEGIN(Pressed23)
SHOW_MAP_BODY(Skin24)
SHOW_MAP_BODY(Text26)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Pressed23,36,192,127,219)

CREATE_BUTTON_ITEM_DATA(STRID_NULL_27,STRID_NULL_,ICON__EMPTY,STATUS_ENABLE,NULL) 
SHOW_MAP_BEGIN(UIMenuWndWiFiMobileLinkOK_Button_Disconnect)
SHOW_MAP_BODY(Normal7)
SHOW_MAP_BODY(Focused11)
SHOW_MAP_BODY(Normal_Disable15)
SHOW_MAP_BODY(Focused_Disable19)
SHOW_MAP_BODY(Pressed23)
SHOW_MAP_END

DECLARE_EVENT(UIMenuWndWiFiMobileLinkOK_Button_Disconnect)
BUTTON_LIST_BEGIN(UIMenuWndWiFiMobileLinkOK_Button_Disconnect)
BUTTON_LIST_ITEM(STRID_NULL_27)
BUTTON_LIST_END

CREATE_BUTTON_DATA(UIMenuWndWiFiMobileLinkOK_Button_Disconnect,BTN_DRAW_IMAGE_LIST)

CREATE_BUTTON_CTRL(UIMenuWndWiFiMobileLinkOK_Button_Disconnect,UIMenuWndWiFiMobileLinkOK_Button_Disconnect,0,36,192,127,219)
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

SHOW_ITEM_RECT(CMD_Rectangle,Skin29Rect,0,0,249,21,0,0,0,0,0,0,0)
SHOW_MAP_BEGIN(Skin29)
SHOW_MAP_BODY(Skin29Rect)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Skin29,0,0,249,21)

SHOW_ITEM_TEXT(CMD_Text|CMD_ITEM,Text31,0,0,249,21,STRID_NULL,0,0,0,0,2,1,1,0,0,16,0,0,0,0)
SHOW_MAP_BEGIN(Normal28)
SHOW_MAP_BODY(Skin29)
SHOW_MAP_BODY(Text31)
SHOW_MAP_END

SHOW_ITEM_GROUP(CMD_Group,Normal28,50,110,299,131)

SHOW_MAP_BEGIN(UIMenuWndWiFiMobileLinkOK_StaticTXT_MAC)
SHOW_MAP_BODY(Normal28)
SHOW_MAP_END

DECLARE_EVENT(UIMenuWndWiFiMobileLinkOK_StaticTXT_MAC)
CREATE_STATIC_DATA(UIMenuWndWiFiMobileLinkOK_StaticTXT_MAC,STRID_NULL_)
CREATE_STATIC_CTRL(UIMenuWndWiFiMobileLinkOK_StaticTXT_MAC,0,50,110,299,131)

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

SHOW_MAP_BEGIN(UIMenuWndWiFiMobileLinkOK)
SHOW_MAP_BODY(Skin1)
SHOW_MAP_END

DECLARE_EVENT(UIMenuWndWiFiMobileLinkOK)
DECLARE_CTRL_LIST(UIMenuWndWiFiMobileLinkOK)
CREATE_CTRL(UIMenuWndWiFiMobileLinkOK,UIMenuWndWiFiMobileLinkOK,CTRL_WND,NULL,0 ,0,0,319,239)
#endif
