#pragma once
#include "inventory_images.h"
#include "inventory.h"
#include "equipMent.h"
#include "construction.h"
#include "purchase_land.h"
#include "gamesetting.h"
enum INVENKINDS
{
	INVENTORY,				//인벤토리
	EQUIP,					//장비
	CONSTRUCTION,			//건설
	PURCHASE_LAND,			//토지구매
	GAME_SETTING			//게임설정
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

	INVENKINDS _inven_Kind;				//인벤 종류
	inventory_images *inven_imgs;		//인벤 이미지

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