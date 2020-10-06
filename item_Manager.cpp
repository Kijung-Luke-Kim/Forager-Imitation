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
		cout << _item_push[number]->count << endl;
	}

}



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
}//�κ��丮�� �������� ����ִ��� ã���Լ�

void item_Manager::inventorysection()
{


}//�ߺ��� key�� �ֳ����� �˻�//���������� �ߵ�...�ߺ� ���װ� �߻��ϸ�..�׶�����