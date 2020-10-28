#include "stdafx.h"
#include "ItemDatabase.h"

#define ITEM_MAX 24



void ItemDatabase::init()
{
	_itemDictionary.clear();

	// �ӽ÷� 10��
	tagItem items[ITEM_MAX];
	int t_cnt = 0;

	// �Һ���			    �ʵ������Ű   ����Ű   �̸�  ����  ����������      �������    ��ġ �ɼ�1 �ɼ�2
	items[t_cnt++] = tagItem("berryDrop", "berryDrop", "����", "ü���� ȸ�������ش�.", CONSUMABLE, WeaponType::NONE2, 1, 5, 0);
	items[t_cnt++] = tagItem("fishDrop", "fishDrop", "�����", "ü���� ȸ�������ش�.", CONSUMABLE, WeaponType::NONE2, 1, 5);
	items[t_cnt++] = tagItem("milkDrop", "milkDrop", "����", "ü���� ȸ�������ش�.", CONSUMABLE, WeaponType::NONE2, 3, 5);
	items[t_cnt++] = tagItem("roast_fishDrop", "roast_fishDrop", "���� ���", " ", CONSUMABLE, WeaponType::NONE2, 1, 10);
	// �߰��Ҷ����� Define�� ITEM_MAX ũ�� �÷��� ��!!!


	// �����			    �ʵ������Ű   ����Ű   �̸�  ����  ����������      �������    ��ġ �ɼ�1 �ɼ�2
	items[t_cnt++] = tagItem("rockDrop", "rockDrop", "��", " ", INGREDIANT, WeaponType::NONE2, 1, 0, 0);
	items[t_cnt++] = tagItem("treeDrop", "treeDrop", "����", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("goldBarDrop", "goldBarDrop", "�ݱ�", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("ironBarDrop", "ironBarDrop", "��ö", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("goldOreDrop", "goldOreDrop", "�ݱ���", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("ironOreDrop", "ironOreDrop", "ö����", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("coalDrop", "coalDrop", "��ź", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("brickDrop", "brickDrop", "����", " ", INGREDIANT, WeaponType::NONE2, 3, 0);
	items[t_cnt++] = tagItem("skullHeadDrop", "skullHeadDrop", "���øӸ�", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("leatherDrop", "leatherDrop", "����", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("threadDrop", "threadDrop", "��", " ", INGREDIANT, WeaponType::NONE2, 1, 0);

	items[t_cnt++] = tagItem("high_class_cloth", "high_class_cloth", "��� �ʰ�", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("high_class_SteelDrop", "high_class_SteelDrop", "��� ��ö", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("SteelhDrop", "SteelhDrop", "��ö", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("arrowDrop", "arrowDrop", "ȭ��", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	// �߰��Ҷ����� Define�� ITEM_MAX ũ�� �÷��� ��!!!
	
	// �����			    �ʵ������Ű   ����Ű   �̸�  ����  ����������      �������    ��ġ �ɼ�1 �ɼ�2
	items[t_cnt++] = tagItem("bow1Drop", "bow1Drop", "Ȱ", " ", EQUIPMENT, BOW, 1, 10);
	items[t_cnt++] = tagItem("bow2Drop", "bow2Drop", "��ö Ȱ", " ", EQUIPMENT, BOW, 1, 10);
	items[t_cnt++] = tagItem("bow3Drop", "bow3Drop", "�ձ� Ȱ", " ", EQUIPMENT, BOW, 1, 10);
	items[t_cnt++] = tagItem("swordDrop", "sword", "Į", " ", EQUIPMENT, SWORD, 1, 35);
	items[t_cnt++] = tagItem("pickaxeDrop", "pickaxe", "���", " ", EQUIPMENT, PICKAXE, 1, 20);
	// �߰��Ҷ����� Define�� ITEM_MAX ũ�� �÷��� ��!!!


	for (int i = 0; i < ITEM_MAX; i++) {
		_itemDictionary.insert(make_pair(items[i].itemKey, items[i]));
	}
}
