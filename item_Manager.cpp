#include "stdafx.h"
#include "item_Manager.h"


void item_Manager::vItem_push(string key)
{
	if (isItemCheck(key)) {
		int number = itemfind(key);
		_item_push[number]->count += 1;
	}
	else {
		int number = itemempty();
		_item_push[number]->img_name = key;
		_item_push[number]->Kinds = itemKind(key);
		_item_push[number]->count += 1;
	}

}//������ �κ��� �־��ִ°�

bool item_Manager::Item_industry_check(string key)
{			//rockDrop treeDrop
		int first_material_num = itemfind("rockDrop");
		int second_material_num = itemfind("treeDrop");

		cout << first_material_num << endl;
		cout << second_material_num << endl;
		if (key == "steelwork") {

			if (_item_push[first_material_num]->count >= 5 && _item_push[second_material_num]->count >= 3) {
				_item_push[first_material_num]->count -= 5;
				_item_push[second_material_num]->count -= 3;
				return true;
			}
		}
		else if (key == "anvil") {

			if (_item_push[first_material_num]->count >= 10) {
				_item_push[first_material_num]->count -= 10;
				return true;
			}
		}
		else if (key == "sewingmachine") {

			if (_item_push[first_material_num]->count >= 5 && _item_push[second_material_num]->count >= 5) {
				_item_push[first_material_num]->count -= 5;
				_item_push[second_material_num]->count -= 5;
				return true;
			}
		}
	return false;
}
//�κ��丮���� �Ǽ��� ������ üũ ������ true ������ false




bool item_Manager::isItemCheck(string key)
{
	for (int i = 0; i < _item_push.size(); i++) {
		if (_item_push[i]->img_name == key) {
			return true;
		}
	}
	return false;
}//�κ��丮�� �ִ��� ������ Ȯ��


int item_Manager::itemempty()
{
	int i = 0;
	for (; i < _item_push.size(); i++) {
		if (_item_push[i]->img_name == "") {
			return i;
		}
	}
	return 888;
}//����ִ� �ڸ��� ��ȯ 888�� ������ ���̻� ������ ������ ��ȯ

ItemKinds item_Manager::itemKind(string key)
{
	if (key == "berryDrop") {
		return ITEM_FOOD;
	}
	else if (key == "rockDrop") {
		return ITEM_MATERIAL;
	}
	else if (key == "treeDrop") {
		return ITEM_MATERIAL;
	}
	return ITEM_NULL;
}

//item ���� Ȯ��(������ ������ �þ�� if�� �߰��ؾߵ�)
/*
	ITEM_NULL,
	ITEM_FOOD,
	ITEM_EQUIP,
	ITEM_MATERIAL,
*/

int item_Manager::itemfind(string key)
{
	
	for (int i = 0; i < _item_push.size(); i++) {
		if (_item_push[i]->img_name == key) {
			return i;
		}
	}
	return -1;
}//�κ��丮�� �������� ����ִ��� ã���Լ� -1�� ���ٴ¶�

void item_Manager::inventorysection()
{


}//�ߺ��� key�� �ֳ����� �˻�//���������� �ߵ�...�ߺ� ���װ� �߻��ϸ�..�׶�����