#include "stdafx.h"
#include "item_info.h"

void item_info::render(HDC hdc,string item_name)
{
	/*berryDrop
		rockDrop
		treeDrop*/

	if (item_name == "") return;

	// ������ �̹��� ���
	 tagItem t_item = DATABASE->_itemDictionary[item_name];
	 IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
	 IMAGEMANAGER->render("bag", hdc, 1000, 450);
	 IMAGEMANAGER->render(t_item.itemKey, hdc, 950, 180);


	 // ������ �̸� ���
	 POINT pos;
	 pos.x = 1030;
	 pos.y = 195;
	 TEXTMANAGER->ShowText(hdc, false, t_item.itemName, pos, 30, 0);


	 // ������ ���� ���
	 string t_typeName = "�ش����";
	 if (t_item.itemType == ItemType::CONSUMABLE)
		 t_typeName = "�Ҹ�ǰ";
	 else if (t_item.itemType == ItemType::EQUIPMENT)
		 t_typeName = "���";
	 else if (t_item.itemType == ItemType::INGREDIANT)
		 t_typeName = "���";

	 char str[10];
	 wsprintf(str, "(%s)", t_typeName.c_str());
	 pos.x = 1050;
	 pos.y = 250;
	 TEXTMANAGER->ShowText(hdc, false, str, pos, 30, 1);


	 // ������ ��ġ ���
	 int t_value = t_item.value;
	 wsprintf(str, "��ġ : %d", t_value);
	 pos.x = 1000;
	 pos.y = 280;
	 TEXTMANAGER->ShowText(hdc, false, str, pos, 30, 0);


	 // ������ �ɼ� ���
	 if (t_item.option > 0) {
		 int t_option = t_item.option;
		 wsprintf(str, "+%d ������", t_option);
		 pos.x = 990;
		 pos.y = 320;
		 TEXTMANAGER->ShowText(hdc, false, str, pos, 30, 0, RGB(0, 255, 0));
	 }

}
