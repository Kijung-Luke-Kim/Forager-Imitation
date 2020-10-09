#pragma once
#include "inventory_images.h"
#include "inventory.h"
#include "equipMent.h"
#include "construction.h"
#include "purchase_land.h"
#include "gamesetting.h"
#include "buildinginteraction.h"
enum INVENKINDS
{
	INVENTORY,				//�κ��丮
	EQUIP,					//���
	CONSTRUCTION,			//�Ǽ�
	PURCHASE_LAND,			//��������
	GAME_SETTING			//���Ӽ���
};
struct MOUSEMENU
{
	RECT rc;
	INVENKINDS kinds;
};
class inGameMenu 
{
private:
	vector<MOUSEMENU*> ingameMenuRc;

	INVENKINDS _inven_Kind;				//�κ� ����
	inventory_images *inven_imgs;		//�κ� �̹���

	inventory *_inven;
	equipMent *_equip;
	construction *_construction;
	purchase_land *_purchaese;
	gamesetting *_game_setting;

	buildinginteraction* _buildinginteraction;


	
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void inven_Change_Key_Down();

	void mouse_touch_icon(HDC hdc);
	void settion();


public:
	inventory* GetInven() { return _inven; };
public:
	void setMapLink(earth* map) { 
		_construction->setMapLink(map); 
		_purchaese->setMapLink(map);
	};
};