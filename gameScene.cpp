#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{

	_map = new earth;
	_map->init();
	_player = new ForagerPlayer;
	_player->setPMLink(_map);
	_player->init();
	_map->setLinkPlayer(_player);
	
	_cursor = new cursor;
	_cursor->init();
	_cursor->LinkMap(_map);
	_player->setCursorLink(_cursor);

	_Menu = new inGameMenu;
	_Menu->init();
	_Menu->setMapLink(_map);
	_player->setInvenLink(_Menu->GetInven());

	inven_open = false;
	
	_quick_slot = new quick_slot;
	_quick_slot->init();
	_quick_slot->quick_slot_update();
	_quick_slot->target(0);
	_cursor->quick_slot_info(_quick_slot);
	SAVEMANAGER->set_quick_slot_info(_quick_slot);
	PRODUCTIONMANAGER->init();
	CAMERA->init(_player->x, _player->y, _player->x, _player->y, 0.5f, 0.5f, WINSIZEX + 400, WINSIZEY + 300, -2000*5, -2000 * 5, 2000 * 5, 2000 * 5);
	UNITMANAGER->AddUnits(_player);
	UNITMANAGER->setLinkMap(_map);
	

	_player->getquick_slotInfo(_quick_slot);
	STATMANAGER->ForagerPlayerinfo(_player);
	money_pos.x = 55;
	money_pos.y = WINSIZEY - 50;
	SCENEMANAGER->set_ischeck(true);

	SAVEMANAGER->set_Tile_info(_map);
	SAVEMANAGER->load();
	

	if (SOUNDMANAGER->isPlaySound("�������"))
	{
		SOUNDMANAGER->stop("�������");
	}
	SOUNDMANAGER->play("�������", true);

	

	return S_OK;
}

void gameScene::release()
{
	if (SCENEMANAGER->get_ischeck()) {

	
	_player->release();
	_Menu->release();
	_map->release();
	SAFE_DELETE(_cursor);
	_quick_slot->release();
	PRODUCTIONMANAGER->relese();
	}
}

void gameScene::update()
{
	if (!_cursor->InteractionOpen()) {
		_player->update();

		if (INPUT->GetKeyDown('I')) {
			if (!CAMERA->movelimit) {
				CAMERA->forceZoomIn(0, 0.01f, false);
				CAMERA->movelimit = true;
			}
			if (inven_open) {
				inven_open = false;
				SOUNDMANAGER->play("�κ��丮�ݱ�");
				_player->setInvenOpen(false);
			}
			else {
				SOUNDMANAGER->play("�κ��丮����");
				_player->setInvenOpen(true);
				inven_open = true;
				_Menu->settion();
			}
		}
	}
	PRODUCTIONMANAGER->update();
	if (inven_open && !_cursor->InteractionOpen()) {
		_Menu->update();
	}
	else {
		_quick_slot->update();
	}
	
	CAMERA->update();
	CAMERA->targetFollow(_player->rc.left, _player->rc.top);
	CAMERA->camFocusCursor(_ptMouse); // ���콺 Ŀ���� ���� ī�޶� ���Ž�.


	EFFECTMANAGER->update();
	TEXTMANAGER->update();
	DIALOGUE->update();
	_map->update();

	// �κ��丮 ���� Ŀ�� Ÿ���� ������Ʈ ����
	if(!inven_open)
		_cursor->update();
	
	if (INPUT->GetKeyDown(VK_F1)) {
		SAVEMANAGER->save();
	}
	if (INPUT->GetKeyDown(VK_F2)) {
		SAVEMANAGER->load();
	}
}


void gameScene::render()
{
	_map->render(getMemDC());				// �� ����
	EFFECTMANAGER->render(getMemDC());		// ����Ʈ ����
	TEXTMANAGER->render(getMemDC());		// �ؽ�Ʈ ����
	PRODUCTIONMANAGER->render(getMemDC());	// ����ǰ ����
	DIALOGUE->render(getMemDC());			// ��ǳ�� ����
	if (inven_open) 						// �޴� ����
		_Menu->render(getMemDC());
	else 
		_quick_slot->render(getMemDC());
	
											// ��� ����
	IMAGEMANAGER->render("img_game_money_icon", getMemDC(), 10, WINSIZEY - 50);
	TEXTMANAGER->ShowText(getMemDC(), false, to_string(ITEMMANAGER->getMoney()), money_pos, 38);

	if (!_player->IsBow())
		_cursor->render(getMemDC());		// Ÿ���� �ڽ� ����
	CAMERA->render(getMemDC());				// ī�޶� �׽�Ʈ FrameRect ����
											// ���콺 Ŀ�� ����
	

	if (_player->IsBow() && !inven_open) {
		POINT clampPos = _player->GetBowXY();
		IMAGEMANAGER->findImage("BowCursor")->render(getMemDC(), clampPos.x, clampPos.y);
	}
	IMAGEMANAGER->findImage("TitleCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
}
