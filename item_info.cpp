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
		TEXTMANAGER->ShowText(hdc, false, "����", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, false, "(�Ҹ�ǰ)", pos, 30, 1);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, false, "��ġ : 1", pos, 30, 0);
		pos.x = 990;
		pos.y = 320;
		TEXTMANAGER->ShowText(hdc, false, "+5 ������", pos, 30, 0,RGB(0,255,0));
	}
	else if (item_name == "rockDrop") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, false, "��", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, false, "(���)", pos, 30, 1);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, false, "��ġ : 1", pos, 30, 0);
	}
	else if (item_name == "treeDrop") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, false, "����", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, false, "(���)", pos, 30, 1);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, false, "��ġ : 1", pos, 30, 0);
	}
	else if (item_name == "�ݱ�") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, "�ݱ�", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, "(���)", pos, 30, 0);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, "��ġ : 8", pos, 30, 0);
	}
	else if (item_name == "��ö") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, "��ö", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, "(���)", pos, 30, 0);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, "��ġ : 8", pos, 30, 0);
	}
	else if (item_name == "�ݱ���") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, "�ݱ���", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, "(���)", pos, 30, 0);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, "��ġ : 8", pos, 30, 0);
	}
	else if (item_name == "Iron_ore") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, "ö����", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, "(���)", pos, 30, 0);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, "��ġ : 5", pos, 30, 0);
	}
	else if (item_name == "coal") {
	IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
	IMAGEMANAGER->render("bag", hdc, 1000, 450);
	IMAGEMANAGER->render(item_name, hdc, 920, 180);
	POINT pos;
	pos.x = 1030;
	pos.y = 195;
	TEXTMANAGER->ShowText(hdc, "��ź", pos, 30, 0);
	pos.x = 1000;
	pos.y = 250;
	TEXTMANAGER->ShowText(hdc, "(���)", pos, 30, 0);
	pos.x = 1000;
	pos.y = 280;
	TEXTMANAGER->ShowText(hdc, "��ġ : 5", pos, 30, 0);
	}
	else if (item_name == "skullHead") {
	IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
	IMAGEMANAGER->render("bag", hdc, 1000, 450);
	IMAGEMANAGER->render(item_name, hdc, 920, 180);
	POINT pos;
	pos.x = 1030;
	pos.y = 195;
	TEXTMANAGER->ShowText(hdc, "���øӸ�", pos, 30, 0);
	pos.x = 1000;
	pos.y = 250;
	TEXTMANAGER->ShowText(hdc, "(���)", pos, 30, 0);
	pos.x = 1000;
	pos.y = 280;
	TEXTMANAGER->ShowText(hdc, "��ġ : 3", pos, 30, 0);
	}
	else if (item_name == "�����") {
	IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
	IMAGEMANAGER->render("bag", hdc, 1000, 450);
	IMAGEMANAGER->render(item_name, hdc, 950, 180);
	POINT pos;
	pos.x = 1030;
	pos.y = 195;
	TEXTMANAGER->ShowText(hdc, "�����", pos, 30, 0);
	pos.x = 1000;
	pos.y = 250;
	TEXTMANAGER->ShowText(hdc, "(�Ҹ�ǰ)", pos, 30, 0);
	pos.x = 1000;
	pos.y = 280;
	TEXTMANAGER->ShowText(hdc, "��ġ : 1", pos, 30, 0);
	pos.x = 990;
	pos.y = 320;
	TEXTMANAGER->ShowText(hdc, "+5 ������", pos, 30, 0, RGB(0, 255, 0));
	}



}
