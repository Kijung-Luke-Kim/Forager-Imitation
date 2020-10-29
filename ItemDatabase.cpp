#include "stdafx.h"
#include "ItemDatabase.h"

#define ITEM_MAX 33
#define ITEM_MAKE_MAX 27


void ItemDatabase::init()
{
	_itemDictionary.clear();
	_itemMaterials.clear();
	// �ӽ÷� 10��
	tagItem items[ITEM_MAX];
	tagItemInfo item_make[ITEM_MAKE_MAX];
	int t_cnt = 0;
	int m_cnt = 0;

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

	
	// �����			    �ʵ������Ű   ����Ű   �̸�  ����  ����������      �������    ��ġ �ɼ�1 �ɼ�2
	items[t_cnt++] = tagItem("bowDrop1", "bowDrop1", "Ȱ", " ", EQUIPMENT, BOW, 1, 10);
	items[t_cnt++] = tagItem("bowDrop2", "bowDrop2", "��ö Ȱ", " ", EQUIPMENT, BOW, 1, 10);
	items[t_cnt++] = tagItem("bowDrop3", "bowDrop3", "�ձ� Ȱ", " ", EQUIPMENT, BOW, 1, 10);
	items[t_cnt++] = tagItem("bowDrop4", "bowDrop4", "���� Ȱ", " ", EQUIPMENT, BOW, 1, 10);

	items[t_cnt++] = tagItem("pickaxeDrop", "pickaxe", "���", " ", EQUIPMENT, PICKAXE, 1, 15);
	items[t_cnt++] = tagItem("pickax1", "pickax1", "�ܴ��� ���", " ", EQUIPMENT, PICKAXE, 1, 10);
	items[t_cnt++] = tagItem("pickax2", "pickax2", "��ö ���", " ", EQUIPMENT, PICKAXE, 1, 10);
	items[t_cnt++] = tagItem("pickax3", "pickax3", "�ձ� ���", " ", EQUIPMENT, PICKAXE, 1, 10);


	items[t_cnt++] = tagItem("swordDrop1", "swordDrop1", "��", " ", EQUIPMENT, SWORD, 1, 30);
	items[t_cnt++] = tagItem("swordDrop2", "swordDrop2", "��ö ��", " ", EQUIPMENT, SWORD, 1, 30);
	items[t_cnt++] = tagItem("swordDrop3", "swordDrop3", "Ȳ�� ��", " ", EQUIPMENT, SWORD, 1, 30);
	items[t_cnt++] = tagItem("swordDrop4", "swordDrop4", "ȭ�� ��", " ", EQUIPMENT, SWORD, 1, 30);

	
	

	//======================================================================================================
	//����								�̸�			���1  �ʿ䰳��1   ���2	 �ʿ䰳��2  ���3  �ʿ䰳��3  ���4  �ʿ䰳��4  �ð�  ��᰹�� �����̸�
	//������
	item_make[m_cnt++] = tagItemInfo("threadDrop","treeDrop",1,"",0,"",0,"",0,5,1, MaterialsType::SEWINGMACHINE);
	item_make[m_cnt++] = tagItemInfo("Flag1", "threadDrop", 100, "treeDrop", 50, "boositemDrop", 10, "", 0, 72, 3, MaterialsType::SEWINGMACHINE);
	item_make[m_cnt++] = tagItemInfo("Flag2", "threadDrop", 120, "treeDrop", 100, "boositemDrop", 20, "", 0, 96, 3, MaterialsType::SEWINGMACHINE);
	item_make[m_cnt++] = tagItemInfo("Flag3", "threadDrop", 150, "treeDrop", 150, "boositemDrop", 30, "", 0, 126, 3, MaterialsType::SEWINGMACHINE);
	item_make[m_cnt++] = tagItemInfo("Flag4", "threadDrop", 200, "treeDrop", 200, "boositemDrop", 40, "", 0, 168, 3, MaterialsType::SEWINGMACHINE);


	//���
	item_make[m_cnt++] = tagItemInfo("img_game_money_icon","goldOreDrop",1,"",0,"",0,"",0,5,1, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("arrowDrop","treeDrop",2,"rockDrop",2,"",0,"",0,5,2, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("pickax1","ironOreDrop",3,"rockDrop",5,"",0,"",0,5,2, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("pickax2","SteelhDrop",2,"coalDrop",5,"",0,"",0,5,2, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("pickax3","high_class_SteelDrop",2,"ironBarDrop",4,"",0,"",0,5,2, MaterialsType::ANVIL);


	item_make[m_cnt++] = tagItemInfo("swordDrop1","goldBarDrop",2,"rockDrop",5,"",0,"",0,16,2, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("swordDrop2","ironBarDrop",6,"ironOreDrop",8,"",0,"",0,24,2, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("swordDrop3","SteelhDrop",5,"goldBarDrop",5,"goldOreDrop",10,"",0,32,3, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("swordDrop4","high_class_SteelDrop",5,"goldBarDrop",5,"ironBarDrop",5,"coalDrop",25,64,4, MaterialsType::ANVIL);

	item_make[m_cnt++] = tagItemInfo("bowDrop1","ironBarDrop",2,"rockDrop",5,"",0,"",0,5,2, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("bowDrop2","threadDrop",2,"SteelhDrop",2,"ironOreDrop",5,"",0,15,3, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("bowDrop3","threadDrop",5,"goldBarDrop",5,"goldOreDrop",5,"",0,30,3, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("bowDrop4","threadDrop",10,"goldBarDrop",5,"ironBarDrop",5,"coalDrop",10,60,4, MaterialsType::ANVIL);


	//�뱤��
	item_make[m_cnt++] = tagItemInfo("coalDrop","treeDrop",1,"",0,"",0,"",0,5,1, MaterialsType::STEELWORK);
	item_make[m_cnt++] = tagItemInfo("brickDrop","coalDrop",2,"rockDrop",2,"",0,"",0,5,2, MaterialsType::STEELWORK);
	item_make[m_cnt++] = tagItemInfo("ironBarDrop","ironOreDrop",1,"coalDrop",1,"",0,"",0,5,2, MaterialsType::STEELWORK);
	item_make[m_cnt++] = tagItemInfo("goldBarDrop","goldOreDrop",1,"coalDrop",1,"",0,"",0,5,2, MaterialsType::STEELWORK);
	item_make[m_cnt++] = tagItemInfo("SteelhDrop","ironOreDrop",2,"rockDrop",2,"",0,"",0,5,2, MaterialsType::STEELWORK);
	item_make[m_cnt++] = tagItemInfo("high_class_SteelDrop","SteelhDrop",1,"ironOreDrop",3,"",0,"",0,5,2, MaterialsType::STEELWORK);
	item_make[m_cnt++] = tagItemInfo("roast_fishDrop","fishDrop",1,"coalDrop",2,"",0,"",0,5,2, MaterialsType::STEELWORK);




	for (int i = 0; i < ITEM_MAX; i++) {
		_itemDictionary.insert(make_pair(items[i].itemKey, items[i]));
	}

	for (int i = 0; i < ITEM_MAKE_MAX; i++) {
		_itemMaterials.insert(make_pair(item_make[i].itemKey, item_make[i]));
	}

}
