#include "stdafx.h"
#include "item_info.h"

void item_info::render(HDC hdc,string item_name)
{
	/*berryDrop
		rockDrop
		treeDrop*/
	if (item_name == "berryDrop") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 950, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, "����", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, "(�Ҹ�ǰ)", pos, 30, 1);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, "��ġ : 1", pos, 30, 0);
		pos.x = 990;
		pos.y = 320;
		TEXTMANAGER->ShowText(hdc, "+5 ������", pos, 30, 0,RGB(0,255,0));
	}
	else if (item_name == "rockDrop") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, "��", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, "(���)", pos, 30, 1);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, "��ġ : 1", pos, 30, 0);
	}
	else if (item_name == "treeDrop") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, "����", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, "(���)", pos, 30, 1);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, "��ġ : 1", pos, 30, 0);
	}



}
