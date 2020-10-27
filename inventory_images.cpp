#include "stdafx.h"
#include "inventory_images.h"

HRESULT inventory_images::init()
{
	// UI ���
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
	IMAGEMANAGER->addImage("quick_slot_background", "Images/�̹���/GUI/inventory_background.bmp", 56, 56);
	IMAGEMANAGER->addImage("img_industry_icon", "Images/�̹���/GUI/img_industry_icon.bmp", 250, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_steelwork_icon", "Images/�̹���/GUI/img_steelwork_icon.bmp", 220, 53, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_missing_icon", "Images/�̹���/GUI/img_missing_icon.bmp", 220, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_anvil_icon", "Images/�̹���/GUI/img_anvil_icon.bmp", 220, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_sewingmachine_icon", "Images/�̹���/GUI/img_sewingmachine_icon.bmp", 220, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("purchase_land", "Images/�̹���/GUI/purchase_land.bmp", 105, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_Agriculture_icon", "Images/�̹���/GUI/img_Agriculture_icon.bmp", 250, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("game_setting", "Images/�̹���/GUI/game_setting.bmp", 64, 82, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_bridge_icon", "Images/�̹���/GUI/img_bridge_icon.bmp", 220, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_fish_trap_icon", "Images/�̹���/GUI/img_fish_trap_icon.bmp", 220, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_Agriculture_missing_icon", "Images/�̹���/GUI/img_Agriculture_missing_icon.bmp", 220, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_UI_construction_Tooltip", "Images/�̹���/GUI/img_UI_construction_Tooltip.bmp", 220, 100, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("targetMenu", "Images/�̹���/GUI/targetMenu.bmp", 319, 54, true, RGB(255, 0, 255));


	// ��� �޴� UI ���
	IMAGEMANAGER->addImage("mouse_construction_icon", "Images/�̹���/GUI/mouse_construction_icon.bmp", 62, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mouse_equip_icon", "Images/�̹���/GUI/mouse_equip_icon.bmp", 58, 81, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mouse_game_setting", "Images/�̹���/GUI/mouse_game_setting.bmp", 74, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mouse_item_icon", "Images/�̹���/GUI/mouse_item_icon.bmp", 81, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mouse_purchase_land", "Images/�̹���/GUI/mouse_purchase_land.bmp", 116, 82, true, RGB(255, 0, 255));


	// �ǹ� ��ȣ�ۿ� ��� UI ���
	IMAGEMANAGER->addImage("img_steelwork_menu", "Images/�̹���/GUI/img_steelwork_menu.bmp",	350, 650, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_sewingmachine_menu", "Images/�̹���/GUI/img_sewingmachine_menu.bmp",	350, 485, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_anvil_menu", "Images/�̹���/GUI/img_anvil_menu.bmp",	350, 595, true, RGB(255, 0, 255));
	
	// �ǹ� ���� ����Ʈ
	IMAGEMANAGER->addFrameImage("smoke_img", "Images/�̹���/GUI/smoke_img.bmp", 364, 28, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("steelwork_yellow", "Images/�̹���/������Ʈ/�뱤��_��ƼŬ.bmp", 33, 21, true, RGB(255, 0, 255));

	// ������ ���� �̹��� ���
	IMAGEMANAGER->addImage("img_game_money_icon", "Images/�̹���/GUI/img_game_money_icon.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bag", "Images/�̹���/GUI/bag_image.bmp", 112, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wood", "Images/�̹���/������/wood.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stone", "Images/�̹���/������/��.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bow", "Images/�̹���/������/Bow.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pickaxe", "Images/�̹���/������/���.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sword", "Images/�̹���/������/sword.bmp", 56, 56, true, RGB(255, 0, 255));

	// ��� ���� ��� �̹���
	IMAGEMANAGER->addImage("sword_right", "Images/�̹���/������/sword_right.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword_att", "Images/�̹���/������/sword_att.bmp", 342, 176, 3, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("img_smoke", "Images/�̹���/Effects/img_smoke.bmp", 600, 200,7,1, true, RGB(255, 0, 255));

	// �Ǽ� ���� �̹��� ���
	//IMAGEMANAGER->addImage("�뱤��", "Images/�̹���/������Ʈ/�뱤��.bmp", 112, 160, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�뱤��", "Images/�̹���/������Ʈ/�뱤��.bmp", 112 / 2, 160 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���", "Images/�̹���/������Ʈ/���.bmp", 100 / 2, 90 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("construction_background", "Images/�̹���/GUI/construction_background.bmp", 324, 720);
	IMAGEMANAGER->addImage("greentile", "Images/�̹���/Ÿ��/img_tile_green.bmp", 56, 56);
	IMAGEMANAGER->addImage("redtile", "Images/�̹���/Ÿ��/img_tile_red.bmp", 56, 56);





	// ��Ÿ UI ���
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




	return S_OK;
}
