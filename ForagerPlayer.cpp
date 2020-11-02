#include "stdafx.h"
#include "ForagerPlayer.h"
#include "quick_slot.h"

HRESULT ForagerPlayer::init()
{
	tileIndex = 0;
	_dir = 0;

	// ��ġ �ʱ�ȭ
	objKey = "Player";
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	rc = RectMakeCenter(x, y, 30, 41);
	_playerTilePos = FindPlayerTilePos();

	// Object ���� �ʱ�ȭ
	tag = TAG::PLAYER;
	layer = LAYER::OBJECT;
	_handleItem = DATABASE->GetItem("pickaxeDrop");

	// ���� �ʱ�ȭ
	maxHp = 1;
	currentHp = 1;
	exp = 0;
	Atk = 0;
	_bowPowerGauge = 0.1f;

	//�÷��̾� ���� �Ұ� �ʱ�ȭ 
	_isLeft = false;
	_isUp = false;
	_isMoveHorizon = false;
	_isMoveVertical = false;
	_isMoveRotate = false;
	_isRun = false;
	_isHammering = false;
	_isBowPulling = false;
	_isGotDamage = false;
	
	_balloonRatio = 0.2f;			// ������ ������ ���϶� ��ǳ���� ������
	_cntBalloonMax = 1200;			// ��ǳ�� ��� ī��Ʈ
	_cntBalloon = 0;				// ��ǳ�� ī��Ʈ

	_cntBowDelay = 0;			// ���� ȭ�� ���� ������ ��ġ
	_bowDelay = 20;				// �� 0.2��
	_canBowFire = true;
	_spinAngle = 0.0f;
	_state = STATE::IDLE;
	_priorState = _state;
	_angle = 0.0f;
	// ���� ��ġ �ʱ�ȭ
	_rcHammer = RectMake((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 - 28, 56, 56);

	//�⺻ �÷��̾� �̹���
	IMAGEMANAGER->addFrameImage("playerStop", "Images/�̹���/�÷��̾�/player_idle_frame.bmp", 120,112, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRUN", "Images/�̹���/�÷��̾�/player_run_frame.bmp", 160, 112, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("playerRUN")->initForRotateImage(true);
	IMAGEMANAGER->addFrameImage("playerWork", "Images/�̹���/�÷��̾�/player_hammering_frame.bmp", 130, 100, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pickaxe_att1", "Images/�̹���/������/�����1.bmp", 255, 140, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pickaxe_att2", "Images/�̹���/������/�����2.bmp", 255, 140, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pickaxe_att3", "Images/�̹���/������/�����3.bmp", 255, 140, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pickaxe_att4", "Images/�̹���/������/�����4.bmp", 255, 140, 3, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("sword_att1", "Images/�̹���/������/sword_att1.bmp", 342, 176, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword_att2", "Images/�̹���/������/sword_att2.bmp", 342, 176, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword_att3", "Images/�̹���/������/sword_att3.bmp", 342, 176, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword_att4", "Images/�̹���/������/sword_att4.bmp", 342, 176, 3, 2, true, RGB(255, 0, 255));
	//��� �̹���
	IMAGEMANAGER->addFrameImage("Hammer1", "Images/�̹���/������/���1.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Hammer2", "Images/�̹���/������/���2.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Hammer3", "Images/�̹���/������/���3.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Hammer4", "Images/�̹���/������/���4.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword1", "Images/�̹���/������/sword1.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword2", "Images/�̹���/������/sword2.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword3", "Images/�̹���/������/sword3.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword4", "Images/�̹���/������/sword4.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));

	// �̹��� �Ľ�
	_foragerIdle = IMAGEMANAGER->findImage("playerStop");
	_foragerRun = IMAGEMANAGER->findImage("playerRUN");
	_foragerAttacking = IMAGEMANAGER->findImage("pickaxe_att1");
	_playerHammering = IMAGEMANAGER->findImage("playerWork");

	_handleWeapon = IMAGEMANAGER->findImage("Hammer1");
	_bow = IMAGEMANAGER->findImage("bowDrop1");

	//�������̹��� �ִϸ��̼� ���� ���� �ʱ�ȭ 
	_count = 0;
	_index = 0;
	_hitDelayCount = 1;

	//ȸ������ ���� �ʱ�ȭ 
	_Acount = 0;
	_spinCount = 0;
	_spinSpeed = 0;


	//�÷��̾� ���� �Ұ� �ʱ�ȭ 
	_isLeft = false;
	_isUp = false;
	_isMoveHorizon = false;
	_isMoveVertical = false;
	_isMoveRotate = false;
	_isRun = false;
	_isHammering = false;

	maxHp = 1;
	currentHp = 1;
	STATMANAGER->init();

	// �ȱ� �ִϸ��̼� �ʱ�ȭ
	_footWalkCount = 0;
	_footWalkEffectInterval = 12;

	// ��Ÿ
	inven_open = false;

	_startBalloon = false;		// ���� ��ǳ��
	_cntDelayStartBalloon = 0;
	_delayStartBalloon = 240;
	_powerOverwhelmingTime = 1000;

	STATMANAGER->SetLinkPlayer(this);

	return S_OK;
}

void ForagerPlayer::release()
{
}

void ForagerPlayer::update()
{
	BlinkProcess();		// ���� ������ ������ ���
	animation();		// �ִϸ��̼� Ȱ��ȭ
	if (_handleItem.weaponType == WeaponType::BOW && !inven_open) bowAnimation();
	_rcHammer = RectMake((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 - 28, 56, 56); // ��ġ �Ľ�


	CalcBowDelay();		// ȭ�� ���� üũ
	weaponCheck();		// ���� ���� üũ
	hungryBalloon();	// ����� ��ġ
	CAMERA->targetFollow(rc.left, rc.top); // ī�޶� ����
	STATMANAGER->update();				   // �������ͽ� ������Ʈ
	STATMANAGER->setinvenopen(inven_open); // �κ��丮 üũ

	// �÷��̾� ������ & �浹 ó��
	if (!inven_open) {
		PlayerControll();
		playerMove();
		playerLookingDirection();
		CheckPlayerTile();
		CheckCollision();
	}

	// ���� ��ȭ üũ
	if (_priorState != _state) {
		_count = 0;
		_index = 0;
		_hitDelayCount = 0;
	}
	_priorState = _state;


	if (INPUT->GetKeyDown(VK_F5)) {
		ITEMMANAGER->getvInventory_info()[0]->count += 100;
		ITEMMANAGER->getvInventory_info()[0]->_item = DATABASE->GetItem("rockDrop");

		 ITEMMANAGER->getvInventory_info()[1]->count += 100;
		 ITEMMANAGER->getvInventory_info()[1]->_item = DATABASE->GetItem("treeDrop");

		 ITEMMANAGER->getvInventory_info()[2]->count += 100;
		 ITEMMANAGER->getvInventory_info()[2]->_item = DATABASE->GetItem("berryDrop");

		 ITEMMANAGER->getvInventory_info()[3]->count += 100;
		 ITEMMANAGER->getvInventory_info()[3]->_item = DATABASE->GetItem("goldOreDrop");

		 ITEMMANAGER->getvInventory_info()[4]->count += 100;
		 ITEMMANAGER->getvInventory_info()[4]->_item = DATABASE->GetItem("coalDrop");

		 ITEMMANAGER->getvInventory_info()[5]->count += 100;
		 ITEMMANAGER->getvInventory_info()[5]->_item = DATABASE->GetItem("ironOreDrop");

		 ITEMMANAGER->getvInventory_info()[6]->count += 100;
		 ITEMMANAGER->getvInventory_info()[6]->_item = DATABASE->GetItem("ironBarDrop");

		 ITEMMANAGER->getvInventory_info()[7]->count += 100;
		 ITEMMANAGER->getvInventory_info()[7]->_item = DATABASE->GetItem("goldBarDrop");

		 ITEMMANAGER->getvInventory_info()[8]->count += 100;
		 ITEMMANAGER->getvInventory_info()[8]->_item = DATABASE->GetItem("high_class_SteelDrop");

		 ITEMMANAGER->getvInventory_info()[9]->count += 100;
		 ITEMMANAGER->getvInventory_info()[9]->_item = DATABASE->GetItem("SteelhDrop");

		 ITEMMANAGER->getvInventory_info()[10]->count += 100;
		 ITEMMANAGER->getvInventory_info()[10]->_item = DATABASE->GetItem("roast_fishDrop");

		 ITEMMANAGER->getvInventory_info()[11]->count += 100;
		 ITEMMANAGER->getvInventory_info()[11]->_item = DATABASE->GetItem("fishDrop");

		 ITEMMANAGER->getvInventory_info()[12]->count += 100;
		 ITEMMANAGER->getvInventory_info()[12]->_item = DATABASE->GetItem("threadDrop");

		ITEMMANAGER->setMoney(ITEMMANAGER->getMoney() + 100);
		_quick->quick_slot_update();

	}


}

void ForagerPlayer::render(HDC hdc)
{
	if (_isGotDamage) {
		if (_count % 5 == 0) 
			renderPlayer(hdc);
	}
	else 
		renderPlayer(hdc);
}


void ForagerPlayer::renderPlayer(HDC hdc)
{
	int relX = CAMERA->GetRelativeX(rc.left);
	int relY = CAMERA->GetRelativeY(rc.top);
	int relWeaponX = CAMERA->GetRelativeX(_rcHammer.left);
	int relWeaponY = CAMERA->GetRelativeY(_rcHammer.top);
	float zoomRate = CAMERA->GetZoom();

	switch (_state)
	{
		case IDLE:
			_foragerIdle->frameRender(hdc, relX, relY, zoomRate);
			break;

		case RUN:
			_foragerRun->frameRender(hdc, relX, relY, zoomRate);
			break;

		case ROTATE:
			_foragerRun->rotateFrameRender(hdc, relX + 20, relY + 20, _foragerRun->getFrameX(), _foragerRun->getFrameY(), _spinAngle * PI / 180.0f);
			if (_handleItem.weaponType == WeaponType::PICKAXE)
				_handleWeapon->rotateFrameRender(hdc, relWeaponX, relWeaponY + 20, 0, _dir, _spinAngle * PI / 180.0f);
			break;

		case HAMMERING:
			_playerHammering->frameRender(hdc, relX, relY, zoomRate);
			if (_handleItem.weaponType == PICKAXE  ) {
				_foragerAttacking->frameRender(hdc, CAMERA->GetRelativeX(rc.left - 16), CAMERA->GetRelativeY(rc.top - 20), zoomRate);
			}
			else if (_handleItem.weaponType == SWORD) {
				_foragerAttacking->frameRender(hdc, CAMERA->GetRelativeX(rc.left-30), CAMERA->GetRelativeY(rc.top - 17), zoomRate);
			}
			break;
	}

	if (_state != ROTATE && _state != HAMMERING)
	{
		if (_handleItem.weaponType == PICKAXE || _handleItem.weaponType == SWORD) {
			if(_isLeft)
				_handleWeapon->frameRender(hdc, relWeaponX, relWeaponY, 0, _dir, zoomRate);
			else
				_handleWeapon->frameRender(hdc, relWeaponX - 45, relWeaponY, 0, _dir, zoomRate);
		}

		// ����
		else if (_handleItem.weaponType == BOW)
			_bow->rotateRender(hdc, relWeaponX * zoomRate, (relWeaponY + 35) * zoomRate, _angle * PI / 180.0f);
		
		else if (_handleItem.itemType == ItemType::CONSUMABLE) {

			if (_handleItem.itemKey == "milkDrop") {
				if (_isLeft) {
					IMAGEMANAGER->render("carryMilk", hdc, relWeaponX - 30, relWeaponY + 30, zoomRate);
				}
				else {
					IMAGEMANAGER->render("carryMilk", hdc, relWeaponX + 10, relWeaponY + 30, zoomRate);
				}

			}if (_handleItem.itemKey == "berryDrop") {
				if (_isLeft) {
					IMAGEMANAGER->render("carryBerry", hdc, relWeaponX - 30, relWeaponY + 30, zoomRate);
				}
				else {
					IMAGEMANAGER->render("carryBerry", hdc, relWeaponX + 10, relWeaponY + 30, zoomRate);
				}
			}
		}
	}
}



void ForagerPlayer::animation()
{

	switch (_state)
	{
	case IDLE:
		_foragerIdle->setFrameY((_isLeft) ? 1 : 0);
		_foragerIdle->setFrameX(_index);
		if (_count++ % 10 == 0)
		{
			if (_index++ > 2)
				_index = 0;
		}
		break;
	case RUN:
		_foragerRun->setFrameY((_isLeft) ? 1 : 0);
		_foragerRun->setFrameX(_index);
		if (_count++ % 10 == 0)
		{
			if (_index++ > 3)
				_index = 0;
		}
		break;

	case ROTATE:
		if (_isLeft)
			_spinAngle += 10.0f;
		else
			_spinAngle -= 10.0f;

		if (abs(_spinAngle) >= 360.0f) {
			_spinAngle = .0f;
			_index = 0;
			_state = STATE::IDLE;
			_isMoveRotate = false;
		}
		break;
	case HAMMERING:
		if (_handleItem.weaponType == WeaponType::PICKAXE) {
			if (STATMANAGER->GetHammerUpgradeCount() == 1)
				_foragerAttacking = IMAGEMANAGER->findImage("pickaxe_att1");
			else if (STATMANAGER->GetHammerUpgradeCount() == 2)
				_foragerAttacking = IMAGEMANAGER->findImage("pickaxe_att2");
			else if (STATMANAGER->GetHammerUpgradeCount() == 3)
				_foragerAttacking = IMAGEMANAGER->findImage("pickaxe_att3"); 
			else if (STATMANAGER->GetHammerUpgradeCount() == 4)
				_foragerAttacking = IMAGEMANAGER->findImage("pickaxe_att4");

		}
		else if (_handleItem.weaponType == WeaponType::SWORD) {
			if (STATMANAGER->GetSwordUpgradeCount() == 1)
				_foragerAttacking = IMAGEMANAGER->findImage("sword_att1");
			else if (STATMANAGER->GetSwordUpgradeCount() == 2)
				_foragerAttacking = IMAGEMANAGER->findImage("sword_att2");
			else if (STATMANAGER->GetSwordUpgradeCount() == 3)
				_foragerAttacking = IMAGEMANAGER->findImage("sword_att3");
			else if (STATMANAGER->GetSwordUpgradeCount() == 4)
				_foragerAttacking = IMAGEMANAGER->findImage("sword_att4");

		}

		_foragerAttacking->setFrameY((_isLeft) ? 1 : 0);
		_foragerAttacking->setFrameX(_index);
		_playerHammering->setFrameY((_isLeft) ? 1 : 0);
		_playerHammering->setFrameX(_index);
		if (_hitDelayCount++ % 10 == 0)
		{
			if (_index++ > 3)
			{
				_index = 0;
				_hitDelayCount = 1;
			}
		}
		break;
	}
}
	

void ForagerPlayer::bowAnimation()
{
	// ���콺�� �÷��̾� ������ ����
	POINT t_mousePos = _ptMouse;
	POINT t_myPos = { CAMERA->GetRelativeX(GetCenterX() + 4), CAMERA->GetRelativeY(GetCenterY() + 4)};
	int x = t_mousePos.x - t_myPos.x;
	int y = t_mousePos.y - t_myPos.y;
	_angle = atan2f(-y, x);
	_angle = (_angle / PI * 180.f);

	// ������ ������ ��� ����� ġȯ
	if (_angle < 0)
		_angle = 180.0f + (180.0f - (_angle * -1));
	
}


void ForagerPlayer::PlayerControll()
{
	// ��ȭ �׽�Ʈ
	if(INPUT->GetKeyDown('U')) {
		
		switch (_handleItem.weaponType)
		{
		case WeaponType::PICKAXE:
			STATMANAGER->SetHammerUpgradeCount(STATMANAGER->GetHammerUpgradeCount() + 1);
			break;
		case WeaponType::SWORD:
			STATMANAGER->SetSwordUpgradeCount(STATMANAGER->GetSwordUpgradeCount() + 1);
			break;
		case WeaponType::BOW:
			STATMANAGER->SetBowUpgradeCount(STATMANAGER->GetBowUpgradeCount() + 1);
			break;
		}
	}



	if (_state != ROTATE) {
		if (!INPUT->GetKey(VK_LEFT) || !INPUT->GetKey(VK_RIGHT))
		{
			_state = IDLE;
			_isMoveHorizon = false;
			_isMoveVertical = false;
		}
		//�پ�ٴϴ� ���� (�¿� ������)
		if (INPUT->GetKey('A') || INPUT->GetKey('D'))
		{
			if (!SOUNDMANAGER->isPlaySound("�÷��̾����2") && !SOUNDMANAGER->isPlaySound("�÷��̾����1")) {
				switch (RANDOM->range(2)) {
				case 0:
					SOUNDMANAGER->play("�÷��̾����1");

					break;
				case 1:
					SOUNDMANAGER->play("�÷��̾����2");

					break;
				}
			}
			_isMoveHorizon = true;
			_state = RUN;
			_isLeft = (INPUT->GetKey('A')) ? true : false;	//���⼳��
		}
		//�پ�ٴϴ� ���� (���� ������)
		if (INPUT->GetKey('W') || INPUT->GetKey('S'))
		{
			if (!SOUNDMANAGER->isPlaySound("�÷��̾����2") && !SOUNDMANAGER->isPlaySound("�÷��̾����1")) {
				switch (RANDOM->range(2)) {
				case 0:
					SOUNDMANAGER->play("�÷��̾����1");
					break;
				case 1:
					SOUNDMANAGER->play("�÷��̾����2");
					break;
				}
			}
			_isMoveVertical = true;
			_state = RUN;
			_isUp = (INPUT->GetKey('W')) ? true : false;	//���� ����
		}

		// ������ ���� ������ �� �ְ�
		if (_state != IDLE)
		{
			//�����ٴϴ� ���� 
			if (INPUT->GetKeyDown(VK_SPACE))
			{
				_state = ROTATE;
				_isMoveRotate = false;
				STATMANAGER->setRight(5);
			}
		}

		// ���� ��Ŭ��
		if (INPUT->GetKey(VK_LBUTTON))
		{
			if (_handleItem.weaponType == WeaponType::PICKAXE || _handleItem.weaponType == WeaponType::SWORD) {
				MeleeWeaponClick();
			}
			else if (_handleItem.weaponType == WeaponType::BOW)
			{
				if (_canBowFire)
				{
					BowClick();
				}
			}
		}

		if (INPUT->GetKeyDown(VK_LBUTTON)) {
			if (_handleItem.itemType == ItemType::CONSUMABLE) {
				if (ITEMMANAGER->Item_count_Minus(_handleItem.itemKey, 1)) {
					_quick->Item_Minus(_handleItem.itemKey, 1);
					STATMANAGER->setRight(-_handleItem.option);
					if (_handleItem.option2 > 0)
						STATMANAGER->RecoverHp(_handleItem.option2);
					SOUNDMANAGER->play("�������Ҹ�", false);
				}
				else {
					_quick->changeQuickSlot(0);
					_quick->settargetNum(0);
				}

			}
		}
		if (INPUT->GetKeyUp(VK_LBUTTON))
		{
			if (_handleItem.weaponType == WeaponType::PICKAXE)
			{
				_hitDelayCount = 1;
				_index = (_isLeft) ? 3 : 0;
				_foragerAttacking->setFrameX(_index);
				_playerHammering->setFrameX(_index);
			}
			else if (_handleItem.weaponType == WeaponType::BOW) {
				ArrowFire();
			}
		}
	}
}

void ForagerPlayer::MeleeWeaponClick()
{
	if (_hitDelayCount == 18)
	{
		SOUNDMANAGER->play("��������");
	}
	unit* targetUnit = _cursor->GetTargetUnit();
	if (targetUnit != nullptr)
	{
		if (targetUnit->tag == TAG::OBJECT || targetUnit->tag == TAG::ENEMY || targetUnit->tag == TAG::NPC || targetUnit->tag == TAG::BUILDING)
		{
			// Ÿ�� ������
			if (_hitDelayCount == 18)
			{
				//SOUNDMANAGER->play("��������");
				// Ÿ�ٰ��� �Ÿ��� ������
				int tarWidth = targetUnit->rc.left + (targetUnit->rc.right - targetUnit->rc.left) / 2;
				if (abs(targetUnit->GetCenterX() - GetCenterX()) <= MAXTOUCHDISTANCE + tarWidth && abs(targetUnit->GetCenterY() - PLAYER_OFFSET_Y) <= MAXTOUCHDISTANCE + tarWidth)
				{
					// Ÿ�� ����
					if (_handleItem.itemType == ItemType::EQUIPMENT) {
						targetUnit->hurt(Atk);
						if (_handleItem.weaponType == WeaponType::PICKAXE) {
							if (STATMANAGER->GetHammerUpgradeCount() == 4) 
								EFFECTMANAGER->ShowEffectFrame("pickEff4", { targetUnit->GetCenterX(), targetUnit->GetCenterY() }, 7, true);
						}
						else if (_handleItem.weaponType == WeaponType::SWORD) {
							if (STATMANAGER->GetSwordUpgradeCount() == 4)
								EFFECTMANAGER->ShowEffectFrame("swordEff4", { targetUnit->GetCenterX(), targetUnit->GetCenterY() }, 1, true);
						}
					}
						
					
					// ������ �ı��Ǹ�
					if (targetUnit->isDead() )
					{
						if (targetUnit->objKey == "skull")
							SOUNDMANAGER->play("�ذ����Ҹ�");
						else if (targetUnit->objKey =="cow")
							SOUNDMANAGER->play("Ȳ�һ���Ҹ�");
					
						//���´ϸ� ����
							STATMANAGER->setRight(5);

							//�� ������ ����ġ ȹ��.
							int t_exp = targetUnit->exp;
							if (t_exp > 0) {
								t_exp = RANDOM->range(t_exp - 2, t_exp + 3);
								POINT pt = { targetUnit->rc.left, targetUnit->rc.top };
								string str = std::to_string(t_exp);
								str.insert(0, "EXP ");
								TEXTMANAGER->ShowFloatingText(str, pt, RGB(100, 255, 100), RGB(0, 0, 0));
								STATMANAGER->IncreaseExp(t_exp);
							}
						// Ÿ�� ���� ����
						CAMERA->forceZoomIn(0.04f, 0.008f);
					}
					else {
						CAMERA->forceZoomIn(0.008f, 0.002f);
					}
				}
			}
		}
	}
	_state = HAMMERING;
}

void ForagerPlayer::CalcBowDelay()
{
	if (!_canBowFire) {
		if (_cntBowDelay++ >= _bowDelay) {
			_cntBowDelay = 0;
			_canBowFire = true;
		}
	}
}

void ForagerPlayer::BowClick()
{
	if (!_isBowPulling) {
		_isBowPulling = true;
		CAMERA->forceZoomIn(-0.15f, -0.002f, false);
	}
	else {
		if (_bowPowerGauge >= 1.0f)
			_bowPowerGauge = 1.0f;
		else
			_bowPowerGauge += 0.01f;
	}
}

void ForagerPlayer::ArrowFire()
{


	if (_isBowPulling) {

		_canBowFire = false;
		_isBowPulling = false;
		CAMERA->forceZoomIn(0.0f, 0.02f, false);

		if (ITEMMANAGER->Item_count_Minus("arrowDrop", 1)) {
			SOUNDMANAGER->play("���Ÿ�����");
			int arrowDamage = Atk * _bowPowerGauge;
			EFFECTMANAGER->ShowEffectFrame("DigSmoke", { GetCenterX(), GetCenterY() }, 2, 10, true);

			int t_bowUpgrade = STATMANAGER->GetBowUpgradeCount();
			if (t_bowUpgrade == 1)
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle, 7.0f, 20, false, false);
			else if (t_bowUpgrade == 2) {
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle - 15.0f, 7.0f, 20, false, false);
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle + 15.0f, 7.0f, 20, false, false);
			}
			else if (t_bowUpgrade == 3) {
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle - 15.0f, 7.0f, 20, false, false);
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle, 7.0f, 20, false, false);
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle + 15.0f, 7.0f, 20, false, false);
			}
			else if (t_bowUpgrade == 4) {
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle - 15.0f, 7.0f, 20, false, false);
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle - 5.0f, 7.0f, 20, false, false);
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle + 5.0f, 7.0f, 20, false, false);
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle + 15.0f, 7.0f, 20, false, false);
			}
		}
		else {
			vector<string> t_vStr;
			string str;
			int t_random = RANDOM->range(0, 2);
			if (t_random == 0)
				str = "ȭ���� ������!";
			else if (t_random == 1)
				str = "���濡 ȭ���� ����!";

			t_vStr.push_back(str);
			DIALOGUE->ShowDialogue(t_vStr, &rc, 10);
		}
		_bowPowerGauge = .1f;
	}
}

void ForagerPlayer::playerMove()
{
	//�÷��̾� �¿� ������ ó�� 
	if (_isMoveHorizon)
	{
		bool _cantMove = false;
		int applySpeed = (_isLeft) ? -3 : 3;

		_cantMove = (_isLeft) ? CanCheckMove(-1) : CanCheckMove(1);

		if (!_cantMove) {

			OffsetRect(&rc, applySpeed, 0);
			//�÷��̾ �����̴ٰ�, �����̽��� ������ ȸ���ϸ鼭 ����
			if (_state == STATE::ROTATE) {
				_spinSpeed = applySpeed * 1.5f;
				OffsetRect(&rc, _spinSpeed, 0);
			}
		}
	}

	//�÷��̾� ���� ������ ó�� 
	if (_isMoveVertical)
	{
		bool _cantMove = false;
		int applySpeed = (_isUp) ? -3 : 3;

		_cantMove = (_isUp) ? CanCheckMove(-MAPTILEX) : CanCheckMove(MAPTILEX);

		if (!_cantMove) {

			OffsetRect(&rc, 0, applySpeed);

			//�÷��̾ �����̴ٰ�, �����̽��� ������ ȸ���ϸ鼭 ����
			if (_state == STATE::ROTATE)
			{
				_spinSpeed = applySpeed * 1.5f;
				OffsetRect(&rc, 0, _spinSpeed);
			}
		}
	}

	if (_state == ROTATE || _state == RUN) {
		// �߰��� ����Ʈ
		if (_footWalkCount++ >= _footWalkEffectInterval) {
			_footWalkCount = 0;
			POINT ptCenter = { rc.left + (rc.right - rc.left) / 2 + RANDOM->range(-10, 0),
							 rc.bottom - RANDOM->range(-1, -6) };
			float randomScale = RANDOM->range(0.5f, 0.7f);
			EFFECTMANAGER->ShowEffectAlphaSize("Walk1", ptCenter, 0.25f, randomScale, 50, 200, true);
		}
	}
}


//�÷��̾ ���� �ü��� ���콺 ��ġ�� ���� ���� 
void ForagerPlayer::playerLookingDirection()
{
	int forgaerCenter = (rc.left + rc.right) / 2;

	if (_state != STATE::ROTATE) {
		if (forgaerCenter < CAMERA->GetMouseRelativePos(_ptMouse).x) {
			_dir = 1;
			_isLeft = false;
		}
			
		else {
			_dir = 0;
			_isLeft = true;
		}
			
	}
}

void ForagerPlayer::weaponCheck()
{

	string t_imgKey = _quick->GetQuickSlotNumber()->_item.itemKey;

	_handleItem = DATABASE->GetItem(t_imgKey);
	Atk = _handleItem.option;

	if(_handleItem.weaponType == WeaponType::PICKAXE)
		_handleWeapon = IMAGEMANAGER->findImage("Hammer" + (to_string(STATMANAGER->GetHammerUpgradeCount())));
	else if (_handleItem.weaponType == WeaponType::SWORD)
		_handleWeapon = IMAGEMANAGER->findImage("sword" + (to_string(STATMANAGER->GetSwordUpgradeCount())));

	_bow = IMAGEMANAGER->findImage("bowDrop" + (to_string(STATMANAGER->GetBowUpgradeCount())));

}

void ForagerPlayer::hungryBalloon()
{
	if (!inven_open) {
		if (STATMANAGER->GetSpRatio() <= _balloonRatio) {
			if (_cntBalloon-- <= 0) {
				_cntBalloon = _cntBalloonMax;
				vector<string> t_vStr;
				string str;
				int t_random = RANDOM->range(0, 2);
				if (t_random == 0)
					str = "�谡 �������� �����߾�.";
				else if (t_random == 1)
					str = "���� �Ծ�߸� ��.";
				t_vStr.push_back(str);
				DIALOGUE->ShowDialogue(t_vStr, &rc, 10);
			}
		}
		else {
			_cntBalloon = 0;
		}
		if (!_startBalloon) {

			if (_cntDelayStartBalloon++ >= _delayStartBalloon) {
				_startBalloon = true;
				vector<string> t_vStr;
				t_vStr.push_back("�� ������ ���� �������ϱ�??");
				t_vStr.push_back("�켱 �뱤�κ��� ����ڰ�!");
				DIALOGUE->ShowDialogue(t_vStr, &rc, 10);
			}
		}
	}



}

void ForagerPlayer::BlinkProcess()
{
	if (_isGotDamage) {
		if (_powerOverwhelmingTime++ >= 120) {
			_isGotDamage = false;
			_powerOverwhelmingTime = 1000;
		}
	}
	else {
		_powerOverwhelmingTime = 1000;
	}
}

POINT ForagerPlayer::GetBowXY()
{
	int distance = 1150 - ((CAMERA->GetZoom() * 1000));
	float x = CAMERA->GetRelativeX(GetCenterX() + (cosf(_angle * PI / 180.0f) * distance)) * CAMERA->GetZoom();
	float y = CAMERA->GetRelativeY(GetCenterY() - (sinf(_angle * PI / 180.0f) * distance)) * CAMERA->GetZoom();

	POINT t_ClampPos = { x, y };

	return t_ClampPos;
}

void ForagerPlayer::RotateImage(image* img)
{
	if (_spinCount++ >= 12)
		_spinCount = 1;

	Rotate(img, img->getFrameWidth(), img->getFrameHeight(), _spinCount, _isLeft);
}

void ForagerPlayer::Rotate(image* img, int sizeX, int sizeY, int frameX, bool left)
{
	int x, y;
	int orig_x, orig_y;
	int pixel;

	double radian = 0;

	if (left)
		radian = (frameX * 30 * PI / 180.0);
	else
		radian = (frameX * -30 * PI / 180.0);

	double cc = cos(radian), ss = sin(-radian);
	double xcenter = (double)sizeX / 2.0, ycenter = (double)sizeY / 2.0; // (2)
	for (y = 0; y < sizeY; y++)
	{
		for (x = 0; x < sizeX; x++)
		{
			orig_x = (int)(xcenter + ((double)y - ycenter)*ss + ((double)x - xcenter)*cc);
			orig_y = (int)(ycenter + ((double)y - ycenter)*cc - ((double)x - xcenter)*ss);
			pixel = 0; // (3)

			if ((orig_y >= 0 && orig_y < sizeY) && (orig_x >= 0 && orig_x < sizeX)) // (4)
				SetPixel(img->getMemDC(), frameX * sizeX + x, y, GetPixel(img->getMemDC(), orig_x, orig_y));

		}
	}
}


// �÷��̾� Ÿ�� ��ǥ Ž��
int ForagerPlayer::FindPlayerTilePos()
{
	vector<tile> _vTiles = _map->GetTiles();
	POINT _ptPlayerPos = { GetCenterX(), PLAYER_OFFSET_Y };

	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			if (PtInRect(&_vTiles[i*MAPTILEY + j].rc, _ptPlayerPos)) {
				return (i*MAPTILEY + j);
			}
		}
	}
}

// �÷��̾� ������ ���� üũ
bool ForagerPlayer::CanCheckMove(int index)
{
	if (_map->GetTileY(_playerTilePos) == 0 && index < 0) return true;
	if (_map->GetTileY(_playerTilePos) == 83 && index > 0) return true;
	if (_map->GetTileX(_playerTilePos) == 0 && index < 0) return true;
	if (_map->GetTileX(_playerTilePos) == 83 && index > 0) return true;

	tile _tile = _map->GetTile(_playerTilePos + index);

	// ������ �� �ִ� Ÿ���̸� ������ ����
	if (_tile.canPass)
		return false;

	// �̵� �Ұ� Ÿ�Ͽ� ������ �����ϴ� �����ӱ��� ���
	RECT t_bound = RectMakeCenter(GetCenterX(), PLAYER_OFFSET_Y, 20, 20);
	RECT t_temp;
	if (!IntersectRect(&t_temp, &t_bound, &_tile.rc)) {
		return false;
	}

	// �̵� �Ұ�
	return true;
}

// �÷��̾� ���� Ÿ�� �浹 üũ
void ForagerPlayer::CheckPlayerTile()
{
	POINT ptPlayerPos = { GetCenterX(), PLAYER_OFFSET_Y };

	// �÷��̾� ��ǥ ���� �����¿� Ÿ���߿� 
	// ���� ��� �ִ� Ÿ�Ϸ� ��ǥ ����
	if (PtInRect(&_map->GetTileRc(_playerTilePos), ptPlayerPos))
		_playerTilePos = _playerTilePos;


	// �÷��̾� ��ǥ ���� �����¿� Ÿ�� �浹 üũ
	else if (_playerTilePos < _map->GetTiles().size() && PtInRect(&_map->GetTileRc(_playerTilePos + 1), ptPlayerPos))
		_playerTilePos += 1;
	else if (_playerTilePos >= 1 && PtInRect(&_map->GetTileRc(_playerTilePos - 1), ptPlayerPos))
		_playerTilePos -= 1;
	else if (_playerTilePos <= _map->GetTiles().size() - MAPTILEX && PtInRect(&_map->GetTileRc(_playerTilePos + MAPTILEX), ptPlayerPos))
		_playerTilePos += MAPTILEX;
	else if (_playerTilePos >= MAPTILEX && PtInRect(&_map->GetTileRc(_playerTilePos - MAPTILEX), ptPlayerPos))
		_playerTilePos -= MAPTILEX;

	// �÷��̾� ��ǥ ���� �밢�� Ÿ�� �浹 üũ
	else if (_playerTilePos >= MAPTILEX - 1 && PtInRect(&_map->GetTileRc(_playerTilePos - MAPTILEX + 1), ptPlayerPos))
		_playerTilePos += MAPTILEX + 1;
	else if (_playerTilePos >= MAPTILEX + 1 && PtInRect(&_map->GetTileRc(_playerTilePos - MAPTILEX - 1), ptPlayerPos))
		_playerTilePos -= MAPTILEX - 1;
	else if (_playerTilePos < _map->GetTiles().size() - MAPTILEX - 1 && PtInRect(&_map->GetTileRc(_playerTilePos + MAPTILEX + 1), ptPlayerPos))
		_playerTilePos += MAPTILEX + 1;
	else if (_playerTilePos < _map->GetTiles().size() - MAPTILEX + 1 && PtInRect(&_map->GetTileRc(_playerTilePos + MAPTILEX - 1), ptPlayerPos))
		_playerTilePos -= MAPTILEX - 1;

	// �÷��̾��� ��ǥ�� ��߳� ��� �ٽ� �޾ƿ�.
	else
		_playerTilePos = FindPlayerTilePos();
}



// Unit �浹
void ForagerPlayer::CheckCollision()
{
	vector<unit*> t_vUnit = UNITMANAGER->GetUnits();

	for (int i = 0; i < t_vUnit.size(); i++) {

		// ������ �浹
		if (t_vUnit[i]->tag == TAG::ITEM) {
			RECT temp;
			RECT t_bound = RectMakeCenter(GetCenterX(), GetCenterY(), 30, 30);
			if (IntersectRect(&temp, &t_bound, &t_vUnit[i]->rc)) {
				SOUNDMANAGER->play("�������浹");
				
				t_vUnit[i]->collision();
				TEXTMANAGER->AppearItemText(t_vUnit[i]->dropItem.itemKey);
				// �κ��丮�� ������ �߰� (Ű��ex : treeDrop, berryDrop)
				tagItem item = DATABASE->GetItem(t_vUnit[i]->dropItem.itemKey);
				if (item.itemType == ItemType::EQUIPMENT) {
					ITEMMANAGER->vequip_push(t_vUnit[i]->dropItem.itemKey);
					_quick->quick_slot_update();
				}
				else {
					ITEMMANAGER->vItem_push(t_vUnit[i]->dropItem.itemKey);	
					_quick->quick_slot_update();
				}
				_quick->quick_slot_update();
				break;
				
			}
		}
		// ���� ��ȣ�ۿ� ��Ʈ �浹
		else if (t_vUnit[i]->tag == TAG::BUILDING) {

		}
		// ���ʹ� �浹
		else if (t_vUnit[i]->tag == TAG::ENEMY) {

		}
	}
}


void ForagerPlayer::hurt(int damage, bool onlyEffect)
{
	if (onlyEffect)
		return;
	
	// �Ϲ� �ǰ�
	if (damage > 1) {
		if (_powerOverwhelmingTime >= 120) {
			SOUNDMANAGER->play("����Ÿ��");
			STATMANAGER->setRight(damage);
			_powerOverwhelmingTime = 0;

			_isGotDamage = true;
		}
	}
	// �극�� ���� �ǰ� 
	else {
		if (_powerOverwhelmingTime >= 10) {

			_powerOverwhelmingTime = 0;
			STATMANAGER->setRight(damage);

			_isGotDamage = true;
		}
	}

	
}


