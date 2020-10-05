#include "stdafx.h"
#include "inventory_images.h"

HRESULT inventory_images::init()
{
	IMAGEMANAGER->addImage("Q", "Images/�̹���/GUI/Q��ư.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("E", "Images/�̹���/GUI/E��ư.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ŀ��", "Images/�̹���/GUI/Ŀ��.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("inventory_Kinds", "Images/�̹���/GUI/inventory_Kinds.bmp", 468, 104, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_item_icon", "Images/�̹���/GUI/img_item_icon.bmp", 78, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_equip_icon", "Images/�̹���/GUI/img_equip_icon.bmp", 78, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Img_UI_EquipmentSlotFilled", "Images/�̹���/GUI/Img_UI_EquipmentSlotFilled.bmp", 72, 72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���׹̳�", "Images/�̹���/GUI/img_UI_StaminaGaugeBar.bmp", 72, 72, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("img_UI_TargetingBox", "Images/�̹���/GUI/img_UI_TargetingBox.bmp", 72, 21, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_UI_ItemTooltip", "Images/�̹���/GUI/img_UI_ItemTooltip.bmp", 296, 216, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_slot", "Images/�̹���/GUI/img_UI_InventorySlotBoundary.bmp", 88, 88, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_equip_slot", "Images/�̹���/GUI/img_equip_slot.bmp", 582, 102, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_construction_icon", "Images/�̹���/GUI/img_construction_icon.bmp", 78, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("inventory_background", "Images/�̹���/GUI/inventory_background.bmp", 1280, 720);
	IMAGEMANAGER->addImage("img_industry_icon", "Images/�̹���/GUI/img_industry_icon.bmp", 226, 72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_steelwork_icon", "Images/�̹���/GUI/img_steelwork_icon.bmp", 205, 59, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_anvil_icon", "Images/�̹���/GUI/img_anvil_icon.bmp", 205, 59, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_sewingmachine_icon", "Images/�̹���/GUI/img_sewingmachine_icon.bmp", 205, 59, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("purchase_land", "Images/�̹���/GUI/purchase_land.bmp", 105, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_Agriculture_icon", "Images/�̹���/GUI/img_Agriculture_icon.bmp", 226, 72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("game_setting", "Images/�̹���/GUI/game_setting.bmp", 64, 82, true, RGB(255, 0, 255));


	//IMAGEMANAGER->addImage("�뱤��", "Images/�̹���/������Ʈ/�뱤��.bmp", 112, 160, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�뱤��", "Images/�̹���/������Ʈ/�뱤��.bmp", 112 / 2, 160 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���", "Images/�̹���/������Ʈ/���.bmp", 100 / 2, 90 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("construction_background", "Images/�̹���/GUI/construction_background.bmp", 324, 720);

	IMAGEMANAGER->addImage("pick", "Images/�̹���/������/���.bmp", 56, 56, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("0", "Images/�̹���/GUI/0.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1", "Images/�̹���/GUI/1.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2", "Images/�̹���/GUI/2.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3", "Images/�̹���/GUI/3.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("4", "Images/�̹���/GUI/4.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("5", "Images/�̹���/GUI/5.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("6", "Images/�̹���/GUI/6.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("7", "Images/�̹���/GUI/7.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("8", "Images/�̹���/GUI/8.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("9", "Images/�̹���/GUI/9.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("greentile", "Images/�̹���/Ÿ��/img_tile_green.bmp", 56, 56);
	IMAGEMANAGER->addImage("redtile", "Images/�̹���/Ÿ��/img_tile_red.bmp", 56, 56);
	return S_OK;
}
