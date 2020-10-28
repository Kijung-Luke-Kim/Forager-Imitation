#include "stdafx.h"
#include "ForagerPlayer.h"
#include "quick_slot.h"

HRESULT ForagerPlayer::init()
{
	tileIndex = 0;

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
	Atk = 15;
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
	_bowDelay = 50;				// �� 0.5��
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
	IMAGEMANAGER->addFrameImage("playerRotate", "Images/�̹���/�÷��̾�/player_rotate_frame.bmp", 672, 56, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRotateLeft", "Images/�̹���/�÷��̾�/player_rotate_frame_left.bmp", 672, 56, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerWork", "Images/�̹���/�÷��̾�/player_hammering_frame.bmp", 130, 100, 3, 2, true, RGB(255, 0, 255));

	//�÷��̾� ���� �� 
	IMAGEMANAGER->addFrameImage("playerHurt", "Images/�̹���/�÷��̾�/playerGotDamage.bmp", 480, 112, 12, 2, true, RGB(255, 0, 255));
	
	//��� �̹���
	IMAGEMANAGER->addImage("Hammer", "Images/�̹���/������/���.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("Hammer")->initForRotateImage(false);
	IMAGEMANAGER->addImage("HammerLeft", "Images/�̹���/������/��̿���.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("HammerLeft")->initForRotateImage(false);
	// ����� �̹��� 3x1
	IMAGEMANAGER->addFrameImage("playerHammering", "Images/�̹���/������/������ϱ�3.bmp",255,140, 3, 2, true, RGB(255, 0, 255));
	//��� ȸ�� �̹��� 12x1
	IMAGEMANAGER->addFrameImage("HammerImg", "Images/�̹���/������/���right.bmp", 672, 56, 12, 1,true,RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("HammerImgLeft", "Images/�̹���/������/���left.bmp", 672, 56, 12, 1,true,RGB(255, 0, 255));


	// �̹��� �Ľ�
	_foragerIdle = IMAGEMANAGER->findImage("playerStop");
	_foragerRun = IMAGEMANAGER->findImage("playerRUN");
	_foragerRotate = IMAGEMANAGER->findImage("playerRotate");
	_foragerHammering = IMAGEMANAGER->findImage("playerHammering");
	_playerHammering = IMAGEMANAGER->findImage("playerWork");
	_playerGotHurt = IMAGEMANAGER->findImage("playerHurt");

	_hammer = IMAGEMANAGER->findImage("Hammer");
	_hammerLeft = IMAGEMANAGER->findImage("Hammer");
	_bow = IMAGEMANAGER->findImage("bowDrop");

	//�÷��̾� ȸ�� �̹��� ����
	for(int i = 1 ; i < 12; i++)
	{
		image *left = IMAGEMANAGER->findImage("playerRotateLeft");
		image *right = IMAGEMANAGER->findImage("playerRotate");

		Rotate(left, left->getFrameWidth(), left->getFrameHeight(), i, true);
		Rotate(right, right->getFrameWidth(), right->getFrameHeight(), i, false);
	}

	//��� ȸ�� �̹��� ����
	for (int i = 1; i < 12; i++)
	{
		image *hammerLeft = IMAGEMANAGER->findImage("HammerImgLeft");
		image *hammerRight = IMAGEMANAGER->findImage("HammerImg");
	
		Rotate(hammerLeft, hammerLeft->getFrameWidth(), hammerLeft->getFrameHeight(), i, true);
		Rotate(hammerRight, hammerRight->getFrameWidth(), hammerRight->getFrameHeight(), i, false);
	}

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
	_powerOverwhelmingTime = 100;

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
			IMAGEMANAGER->frameRender("playerStop", hdc, relX, relY, zoomRate);
			break;
		case RUN:
			IMAGEMANAGER->frameRender("playerRUN", hdc, relX, relY, zoomRate);
			break;

		case ROTATE:
			IMAGEMANAGER->findImage("playerRUN")->rotateFrameRender(hdc, relX + 20, relY + 20, IMAGEMANAGER->findImage("playerRUN")->getFrameX(), IMAGEMANAGER->findImage("playerRUN")->getFrameY(), _spinAngle * PI / 180.0f);

			if (_isLeft)
			{
				if (_handleItem.weaponType == WeaponType::PICKAXE) {
					IMAGEMANAGER->findImage("HammerLeft")->rotateRender(hdc, relWeaponX, relWeaponY + 20, _spinAngle * PI / 180.0f);
				}
			}
			else
			{
				if (_handleItem.weaponType == WeaponType::PICKAXE)
					IMAGEMANAGER->findImage("Hammer")->rotateRender(hdc, relWeaponX, relWeaponY + 20, _spinAngle * PI / 180.0f);
			}
			break;


		case HAMMERING:
			IMAGEMANAGER->frameRender("playerWork", hdc, relX, relY, zoomRate);
			if (_handleItem.weaponType == PICKAXE) {
				_foragerHammering->frameRender(hdc, CAMERA->GetRelativeX(rc.left - 16), CAMERA->GetRelativeY(rc.top - 20), zoomRate);
			}
			if (_handleItem.weaponType == SWORD) {
				_foragerHammering->frameRender(hdc, CAMERA->GetRelativeX(rc.left - 30), CAMERA->GetRelativeY(rc.top - 15), zoomRate);
			}
			break;
	}

	if (_state != ROTATE && _state != HAMMERING)
	{
		// ��� �Ϲ� ����
		if (_handleItem.weaponType == PICKAXE) {
			if (_isLeft)
				IMAGEMANAGER->render("Hammer", hdc, relWeaponX, relWeaponY, zoomRate);
			else
				IMAGEMANAGER->render("HammerLeft", hdc, CAMERA->GetRelativeX(_rcHammer.left - 40), relWeaponY, zoomRate);
		}
		// ���� �Ϲ� ����
		else if (_handleItem.weaponType == BOW)
		{
			_bow->rotateRender(hdc, relWeaponX * zoomRate, (relWeaponY + 35) * zoomRate, _angle * PI / 180.0f);
		}
		else if (_handleItem.weaponType == SWORD) {
			if (_isLeft)
				IMAGEMANAGER->render("sword", hdc, relWeaponX, relWeaponY, zoomRate);
			else
				IMAGEMANAGER->render("sword_right", hdc, CAMERA->GetRelativeX(_rcHammer.left - 40), relWeaponY, zoomRate);
		}
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
	if (!_isGotDamage)
	{
		switch (_state)
		{
		case IDLE:
			_foragerIdle->setFrameY((_isLeft) ? 1 : 0);
			_foragerIdle->setFrameX(_index);
			if (_count++ % 10 == 0)
			{
				if (_index++ > 3)
					_index = 0;
			}
			break;
		case RUN:
			_foragerRun->setFrameY( (_isLeft) ? 1 : 0);
			_foragerRun->setFrameX(_index);
			if (_count++ % 5 == 0)
			{
				if (_index++ > 4)
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
				_foragerHammering = IMAGEMANAGER->findImage("playerHammering");
			}
			else {
				_foragerHammering = IMAGEMANAGER->findImage("sword_att");
			}
			
			_foragerHammering->setFrameY((_isLeft) ? 1 : 0);
			_foragerHammering->setFrameX(_index);
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
	else
	{
		if (_state != HAMMERING)
		{
			if (_count++ > 5)
			{
				_count = 0;

				if (_index > 12)
				{
					_index = 0;
					_isGotDamage = false;
					_powerOverwhelmingTime = 100;
				}
				_index++;
				_playerGotHurt->setFrameX(_index);
				if (_isLeft)
					_playerGotHurt->setFrameY(1);
				else
					_playerGotHurt->setFrameY(0);
			}
		}
		
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
	
	//int t_angle = _angle;
	//// �̹��� ������ ������ ����(45������ 0���� ����ؼ� ������ �̹����� ������ ��ġ��Ŵ)
	//t_angle += 45.0f;
	//if (t_angle > 360.0f) {
	//	t_angle = t_angle - 360.0f;
	//}

	//// 22.5�� ������ �̹��� �����Ӱ� �ٲٱ�.
	//float minAngle = -11.25f;
	//float maxAngle = 11.25f;
	//float addAngle = 22.5f;
	//int count = 0;
	//for (int y = 0; y < 4; y++) {
	//	for (int x = 0; x < 4; x++) {
	//		if (minAngle + (count * addAngle) <= t_angle && t_angle <= maxAngle + (count * addAngle)) {
	//			_bow->setFrameX(x);
	//			_bow->setFrameY(y);
	//			return;
	//		}
	//		count++;
	//	}
	//}
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
			//if (_isGotDamage)
			//{
			//	_isGotDamage = false;
			//	_index = 0;
			//	_count = 0;
			//}
			if (_handleItem.weaponType == WeaponType::PICKAXE || _handleItem.weaponType == WeaponType::SWORD) {
				MeleeWeaponClick();
			}
			else if (_handleItem.weaponType == WeaponType::BOW) {
				
				if(_canBowFire)
					BowClick();
			}
		}

		if (INPUT->GetKeyDown(VK_LBUTTON)) {
			if (_handleItem.itemType == ItemType::CONSUMABLE) {
				if (ITEMMANAGER->Item_count_Minus(_handleItem.itemKey, 1)) {
					_quick->Item_Minus(_handleItem.itemKey, 1);
					STATMANAGER->setRight(-5);
					SOUNDMANAGER->play("�������Ҹ�", false);
				}
				else {
					_quick->target(0);
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
				_foragerHammering->setFrameX(_index);
				_playerHammering->setFrameX(_index);
			}
			else if (_handleItem.weaponType == WeaponType::BOW) {
				ArrowFire();
			}
		}
	}
	else {

		_isGotDamage = false;
		_powerOverwhelmingTime = 100;
	}
}

void ForagerPlayer::MeleeWeaponClick()
{
	_powerOverwhelmingTime = 100;
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
					if (_handleItem.weaponType == WeaponType::PICKAXE) {
						Atk = 15;
					}
					else if(_handleItem.weaponType == WeaponType::SWORD) {
						Atk = 25;
					}
					targetUnit->hurt(Atk);

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
	SOUNDMANAGER->play("���Ÿ�����");
	if (_isBowPulling) {
		_canBowFire = false;
		_isBowPulling = false;
		CAMERA->forceZoomIn(0.0f, 0.02f, false);
		int arrowDamage = Atk * _bowPowerGauge;
		EFFECTMANAGER->ShowEffectFrame("DigSmoke", { GetCenterX(), GetCenterY() }, 2, 10, true);
		
		int t_bowUpgrade = STATMANAGER->GetBowUpgradeCount();
		if(t_bowUpgrade == 0)
			UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle, 7.0f, 20, false, false);
		else if (t_bowUpgrade == 1) {
			UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle - 15.0f, 7.0f, 20, false, false);
			UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle + 15.0f, 7.0f, 20, false, false);
		}
		else if (t_bowUpgrade == 2) {
			UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle - 25.0f, 7.0f, 20, false, false);
			UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle, 7.0f, 20, false, false);
			UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle + 25.0f, 7.0f, 20, false, false);
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
			float randomScale = RANDOM->range(0.01f, 0.03f);
			EFFECTMANAGER->ShowEffectAlphaSize("Walk1", ptCenter, 0, randomScale, 50, 150, true);
		}
	}
}


//�÷��̾ ���� �ü��� ���콺 ��ġ�� ���� ���� 
void ForagerPlayer::playerLookingDirection()
{
	int forgaerCenter = (rc.left + rc.right) / 2;

	if (_state != STATE::ROTATE) {
		if (forgaerCenter < CAMERA->GetMouseRelativePos(_ptMouse).x)
			_isLeft = false;
		else
			_isLeft = true;
	}
}

void ForagerPlayer::weaponCheck()
{
	string t_imgKey = _quick->GetQuickSlotNumber()->_item.itemKey;
	_handleItem = DATABASE->GetItem(t_imgKey);
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
				t_vStr.push_back("�켱 �뱤�κ��� ����ڰ�!");
				DIALOGUE->ShowDialogue(t_vStr, &rc, 10);
			}
		}
	}



}

void ForagerPlayer::BlinkProcess()
{
	if (_isGotDamage) {
		if (_powerOverwhelmingTime++ >= 10) {
			_isGotDamage = false;
			_powerOverwhelmingTime = 100;
		}
	}
	else {
		_powerOverwhelmingTime = 10;
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
				if (t_vUnit[i]->dropItem.itemKey == "swordDrop" || t_vUnit[i]->dropItem.itemKey == "bowDrop") {
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


void ForagerPlayer::hurt(int damage)
{
	if (_powerOverwhelmingTime >= 10) {
		
		_powerOverwhelmingTime = 0;
		STATMANAGER->setRight(damage);
		if(damage > 1)
			SOUNDMANAGER->play("����Ÿ��");
		_isGotDamage = true;
		/*_index = 1;
		_count = 0;*/
	}
	
}


