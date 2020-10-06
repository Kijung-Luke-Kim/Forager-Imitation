#pragma once
#include "inventory_images.h"
#include "inventory.h"
#include "equipMent.h"
#include "construction.h"
#include "purchase_land.h"
#include "gamesetting.h"

enum INVENKINDS
{
	INVENTORY,				//�κ��丮
	EQUIP,					//���
	CONSTRUCTION,			//�Ǽ�
	PURCHASE_LAND,			//��������
	GAME_SETTING			//���Ӽ���
};
class inGameMenu 
{
private:
	INVENKINDS _inven_Kind;				//�κ� ����
	inventory_images *inven_imgs;		//�κ� �̹���

	inventory *_inven;
	equipMent *_equip;
	construction *_construction;
	purchase_land *_purchaese;
	gamesetting *_game_setting;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void inven_Change_Key_Down();

public:
	inventory* GetInven() { return _inven; };
public:
	void setInMapLink(earth* map) { _construction->setInMapLink(map); };
};