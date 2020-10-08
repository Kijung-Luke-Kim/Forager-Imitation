#pragma once
#include "inventory_slot.h"
#include "item_info.h"

class inventory 
{
private:
	vector<inventory_slot*> player_inventory;		//�κ��丮 
	bool isCheck;									//		
	string item_count[9];							//���� �̹��� �̸�
	int StaminaMax;									//���׹̳� �ִ밪
	targetingBox* _targetBox;
	item_info* _item_info;
	int *money;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void mouse_targetBox();
	void food_eat();
	int* getMoney() { return money; };
	void item_info_print(HDC hdc);
	
	void setIsCheck(bool check) {
		isCheck = check;
	}
	vector<inventory_slot*> get_inven() { return player_inventory; };
};

