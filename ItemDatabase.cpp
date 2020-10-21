#include "stdafx.h"
#include "ItemDatabase.h"

#define ITEM_MAX 14

void ItemDatabase::init()
{
	_itemDictionary.clear();

	// �ӽ÷� 10��
	tagItem items[ITEM_MAX];
	items[0] = tagItem("berryDrop", "����", CONSUMABLE, 1, 5);
	items[1] = tagItem("�����", "�����", CONSUMABLE, 1, 5);
	items[2] = tagItem("milkDrop", "����", CONSUMABLE, 3, 5);
	items[3] = tagItem("rockDrop", "��", INGREDIANT, 1, 0);
	items[4] = tagItem("treeDrop", "����", INGREDIANT, 1, 0);
	items[5] = tagItem("�ݱ�", "�ݱ�", INGREDIANT, 1, 0);
	items[6] = tagItem("��ö", "��ö", INGREDIANT, 1, 0);
	items[7] = tagItem("�ݱ���", "�ݱ���", INGREDIANT, 1, 0);
	items[8] = tagItem("Iron_ore", "ö����", INGREDIANT, 1, 0);
	items[9] = tagItem("coal", "��ź", INGREDIANT, 1, 0);
	items[10] = tagItem("skullHeadDrop", "���øӸ�", INGREDIANT, 1, 0);
	items[11] = tagItem("leather", "����", INGREDIANT, 1, 0);
	items[12] = tagItem("slot_Bow", "Ȱ", EQUIPMENT, 1, 0);
	items[13] = tagItem("sword", "Į", EQUIPMENT, 1, 0);

	for (int i = 0; i < ITEM_MAX; i++) {
		_itemDictionary.insert(make_pair(items[i].itemKey, items[i]));
	}


}
