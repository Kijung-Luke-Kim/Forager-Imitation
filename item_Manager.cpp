#include "stdafx.h"
#include "item_Manager.h"


int item_Manager::equip_count()
{
	int count=0;
	for (int i = 0; i < _equip.size(); i++) {
		if (_equip[i]->_item.itemType == ItemType::EQUIPMENT) {
			count++;
		}
	}
	for (int i = 0; i < ITEMMANAGER->getvInventory_info().size(); i++) {
		if (ITEMMANAGER->getvInventory_info()[i]->_item.itemType != ItemType::CONSUMABLE) continue;
			count++;
		
	}
	return count;
}

void item_Manager::vItem_push(string key)
{

	if (key == "img_game_money_icon") {
		*money += 1;
	}
	else if (isItemCheck(key)) {
		int number = itemfind(key);
		_item_push[number]->count += 1;
	}
	else {
		int number = itemempty();
		_item_push[number]->_item = DATABASE->GetItem(key);
		_item_push[number]->count += 1;
	}

}

//������ �κ��� �־��ִ°�
void item_Manager::vequip_push(string key)
{
	if (!isequipCheck(key)) {
		for (int i = 0; i < _equip.size(); i++) {
			if (_equip[i]->_item.itemKey == "") {
				_equip[i]->_item = DATABASE->GetItem(key);
				break;
			}
		}
	}

}
bool item_Manager::isequipCheck(string key)
{
	for (int i = 0; i < _equip.size(); i++) {
		if (_equip[i]->_item.itemKey == key) {
			return true;
		}
	}
	return false;
}
void item_Manager::vItem_count_zoro()
{
	for (int i = 0; i < _item_push.size(); i++) {
		if (_item_push[i]->_item.itemKey == "")continue;
		if (_item_push[i]->count <= 0) {
			_item_push[i]->_item = tagItem();;
		}
	}
}
//������ ī��Ʈ�� 0 �̵Ǹ� ����


bool item_Manager::Item_industry_check(string key)
{			//rockDrop treeDrop
	int first_material_num = itemfind("rockDrop"); 
	int second_material_num = itemfind("treeDrop");
	if (key == "steelwork") {
		if (first_material_num != -1 && second_material_num != -1) {
			if (_item_push[first_material_num]->count >= 5 && _item_push[second_material_num]->count >= 3) {
				return true;
			}
		}
	}
	else if (key == "anvil") {
		if (first_material_num != -1) {
			if (_item_push[first_material_num]->count >= 10) {
				return true;
			}
		}
	}
	else if (key == "sewingmachine") {
		if (first_material_num != -1 && second_material_num != -1) {
			if (_item_push[first_material_num]->count >= 5 && _item_push[second_material_num]->count >= 5) {
				return true;
			}
		}
	}
	else if (key == "bridge") {
		if (second_material_num != -1) {
			if (_item_push[second_material_num]->count >= 5) {
				
				return true;
			}
		}
	}
	else if (key == "fishtrap") {
		if (second_material_num != -1) {
			if (_item_push[second_material_num]->count >= 5) {
				return true;
			}
		}
	}


	return false;
}
//�κ��丮���� �Ǽ��� ������ üũ ������ true ������ false

void item_Manager::_Item_industry_decrease(string key)
{
	int first_material_num = itemfind("rockDrop");
	int second_material_num = itemfind("treeDrop");
	if (key == "steelwork") {
		if (first_material_num != -1 && second_material_num != -1) {
			if (_item_push[first_material_num]->count >= 5 && _item_push[second_material_num]->count >= 3) {
				_item_push[first_material_num]->count -= 5;
				_item_push[second_material_num]->count -= 3;
				vItem_count_zoro();
			}
		}
	}
	else if (key == "anvil") {
		if (first_material_num != -1) {
			if (_item_push[first_material_num]->count >= 10) {
				_item_push[first_material_num]->count -= 10;
				vItem_count_zoro();
			}
		}
	}
	else if (key == "sewingmachine") {
		if (first_material_num != -1 && second_material_num != -1) {
			if (_item_push[first_material_num]->count >= 5 && _item_push[second_material_num]->count >= 5) {
				_item_push[first_material_num]->count -= 5;
				_item_push[second_material_num]->count -= 5;
				vItem_count_zoro();
			}
		}
	}
	else if (key == "bridge") {
		if (second_material_num != -1) {
			if (_item_push[second_material_num]->count >= 5) {
				_item_push[second_material_num]->count -= 5;
				vItem_count_zoro();
			}
		}
	}
	else if (key == "fishtrap") {
		if (second_material_num != -1) {
			if (_item_push[second_material_num]->count >= 5) {
				_item_push[second_material_num]->count -= 5;
				vItem_count_zoro();
			}
		}
	}
}

//�Ǽ� �Ϸ�� ��� ����
bool item_Manager::Item_count_Minus(string key, int count)
{
	if (isItemCheck(key) && _item_push[itemfind(key)]->count >= count) {
		_item_push[itemfind(key)]->count -= count;
		vItem_count_zoro();
		return true;
	}
	return false;

}
bool item_Manager::Item_count_Minus(string key, int count, string key2, int count2)
{
	if (isItemCheck(key) && _item_push[itemfind(key)]->count >= count &&isItemCheck(key2) && _item_push[itemfind(key2)]->count >= count2) {
		_item_push[itemfind(key)]->count -= count;
		_item_push[itemfind(key2)]->count -= count2;
		return true;
	}
	return false;
}
//Ű���� ã�Ƽ� ��� ����

bool item_Manager::isItemCheck(string key)
{
	for (int i = 0; i < _item_push.size(); i++) {
		if (_item_push[i]->_item.itemKey == key) {
			return true;
		}
	}
	return false;
}
//�κ��丮�� �ִ��� ������ Ȯ��


int item_Manager::itemempty()
{
	int i = 0;
	for (; i < _item_push.size(); i++) {
		if (_item_push[i]->_item.itemKey == "") {
			return i;
		}
	}
	return 888;
}
//����ִ� �ڸ��� ��ȯ 888�� ������ ���̻� ������ ������ ��ȯ


//������ ���� Ȯ��


int item_Manager::itemfind(string key)
{
	
	for (int i = 0; i < _item_push.size(); i++) {
		if (_item_push[i]->_item.itemKey == key) {
			return i;
		}
	}
	return -1;
}
//�κ��丮�� �������� ����ִ��� ã���Լ� -1�� ���ٴ¶�

void item_Manager::inventorysection()
{


}//�ߺ��� key�� �ֳ����� �˻�//���������� �ߵ�...�ߺ� ���װ� �߻��ϸ�..�׶�����

int item_Manager::item_count(string key)
{
	if (isItemCheck(key)) {
		return _item_push[itemfind(key)]->count;
	}
	else {
		return 0;
	}
}
//������ �̸����� count�� ��������