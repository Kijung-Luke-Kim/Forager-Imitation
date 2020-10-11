#include "stdafx.h"
#include "ForagerPlayer.h"
#include "ForagerStatManager.h"

HRESULT ForagerPlayer::init()
{
	tag = TAG::PLAYER;
	layer = LAYER::OBJECT;
	exp = 0;
	
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	rc = RectMakeCenter(x, y, 30, 41);
	_playerTilePos = FindPlayerTilePos();
	inven_open = false;

	_rcHammer = RectMake((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 - 28, 56, 56);

	//�÷��̾� ������ ���� �� ������ �̹��� 3*2
	IMAGEMANAGER->addFrameImage("playerStop", "Images/�̹���/�÷��̾�/player_idle_frame.bmp", 120,112, 3, 2, true, RGB(255, 0, 255));

	//�÷��̾� �ٴٴ� �� ������ �̹��� 4*2
	IMAGEMANAGER->addFrameImage("playerRUN", "Images/�̹���/�÷��̾�/player_run_frame.bmp", 160, 112, 4, 2, true, RGB(255, 0, 255));

	//�÷��̾� �����ٴ� �� ������ �̹��� 12*1 2�� (init���� �ƽθ� �Լ� ȣ�� �ؼ� GetKeyDown���� �ѹ� ����� ����)
	IMAGEMANAGER->addFrameImage("playerRotate", "Images/�̹���/�÷��̾�/player_rotate_frame.bmp", 672, 56, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRotateLeft", "Images/�̹���/�÷��̾�/player_rotate_frame_left.bmp", 672, 56, 12, 1, true, RGB(255, 0, 255));

	//�÷��̾ ���'��'�� �� �÷��̾��� ������ �̹��� 
	IMAGEMANAGER->addFrameImage("playerWork", "Images/�̹���/�÷��̾�/player_hammering_frame.bmp", 130, 100, 3, 2, true, RGB(255, 0, 255));

	//�÷��̾ ���'��'�� �� ����� ������ �̹��� 3*1 
	IMAGEMANAGER->addFrameImage("playerHammering", "Images/�̹���/������/������ϱ�3.bmp",255,140, 3, 2, true, RGB(255, 0, 255));

	//��̰� �÷��̾�� ���� ȸ���� �� ������ �̹��� 12*1 2��
	IMAGEMANAGER->addFrameImage("HammerImg", "Images/�̹���/������/���right.bmp", 672, 56, 12, 1,true,RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("HammerImgLeft", "Images/�̹���/������/���left.bmp", 672, 56, 12, 1,true,RGB(255, 0, 255));

	//�÷��̾ �׳� �̵��� �� ��Ÿ���� �⺻ ��� �̹��� 
	IMAGEMANAGER->addImage("Hammer", "Images/�̹���/������/���.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HammerLeft", "Images/�̹���/������/��̿���.bmp", 56, 56, true, RGB(255, 0, 255));

	//�÷��̾� ü��(��)������ �̹���
	//IMAGEMANAGER->addImage("heart", "img_UI_Heart.bmp", );


	_foragerIdle = IMAGEMANAGER->findImage("playerStop");
	_foragerRun = IMAGEMANAGER->findImage("playerRUN");
	_foragerRotate = IMAGEMANAGER->findImage("playerRotate");
	_foragerHammering = IMAGEMANAGER->findImage("playerHammering");
	_playerHammering = IMAGEMANAGER->findImage("playerWork");
	_state = STATE::IDLE;

	_hammer = IMAGEMANAGER->findImage("Hammer");
	_hammerLeft = IMAGEMANAGER->findImage("Hammer");
	
	_footWalkCount = 0;
	_footWalkEffectInterval = 12;

	//�÷��̾� ȸ��
	for(int i = 1 ; i < 12; i++)
	{
		image *left = IMAGEMANAGER->findImage("playerRotateLeft");
		image *right = IMAGEMANAGER->findImage("playerRotate");

		Rotate(left, left->getFrameWidth(), left->getFrameHeight(), i, true);
		Rotate(right, right->getFrameWidth(), right->getFrameHeight(), i, false);
	}

	//��� ȸ�� 
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
	_foragerHp = new ForagerStatManager;
	_foragerHp->init();

	Atk = 15;
	

	return S_OK;
}

void ForagerPlayer::release()
{

}

void ForagerPlayer::update()
{
	animation();
	if (!inven_open) {
		PlayerControll();
		playerMove();
		playerLookingDirection();
		CheckPlayerTile();
		CheckCollision();
	}
	
	_rcHammer = RectMake((rc.left + rc.right) / 2 , (rc.top + rc.bottom) / 2 - 28, 56, 56);
	CAMERA->targetFollow(rc.left, rc.top);
	
	_foragerHp->update();
	_foragerHp->setinvenopen(inven_open);
}

void ForagerPlayer::render(HDC hdc)
{
	switch (_state)
	{
	case IDLE:
		IMAGEMANAGER->frameRender("playerStop", hdc, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.top), CAMERA->GetZoom());
		break;
	case RUN:
		IMAGEMANAGER->frameRender("playerRUN", hdc, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.top), CAMERA->GetZoom());
		break;
	case ROTATE: 
		if (_isLeft) 
		{
			IMAGEMANAGER->frameRender("playerRotateLeft", hdc, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.top), CAMERA->GetZoom());
			IMAGEMANAGER->frameRender("HammerImgLeft", hdc, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.top), CAMERA->GetZoom());
		}
		else 
		{
			IMAGEMANAGER->frameRender("playerRotate", hdc, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.top), CAMERA->GetZoom());
			IMAGEMANAGER->frameRender("HammerImg", hdc, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.top), CAMERA->GetZoom());
		}

		break;
	case HAMMERING :
		IMAGEMANAGER->frameRender("playerWork", hdc, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.top), CAMERA->GetZoom());
		IMAGEMANAGER->frameRender("playerHammering", hdc, CAMERA->GetRelativeX(rc.left-16) ,CAMERA->GetRelativeY(rc.top-20), CAMERA->GetZoom());
		break;
	}

	if (_state != ROTATE && _state != HAMMERING)
	{
		if (_isLeft)
			IMAGEMANAGER->render("Hammer", hdc, CAMERA->GetRelativeX(_rcHammer.left), CAMERA->GetRelativeY(_rcHammer.top), CAMERA->GetZoom());
		else
			IMAGEMANAGER->render("HammerLeft", hdc, CAMERA->GetRelativeX(_rcHammer.left - 40), CAMERA->GetRelativeY(_rcHammer.top), CAMERA->GetZoom());
	}
	_foragerHp->render(hdc);
}

void ForagerPlayer::animation()
{
	switch (_state)
	{
	case IDLE:
		if (_isLeft)
		{
			_foragerIdle->setFrameY(1);
			_foragerIdle->setFrameX(_index);
			if (_count++ % 5 == 0)
			{
				if (_index-- <= 0)
					_index = 3;
			}
		}
		else
		{
			_foragerIdle->setFrameY(0);
			_foragerIdle->setFrameX(_index);
			if (_count++ % 5 == 0)
			{
				if (_index++ > 3)
					_index = 0;
			}
		}
		break;

	case RUN:
		if (_isLeft)
		{
			_foragerRun->setFrameY(1);
			_foragerRun->setFrameX(_index);
			if (_count++ % 5 == 0)
			{
				if (_index-- <= 0)
					_index = 4;
			}
		}
		else
		{
			_foragerRun->setFrameY(0);
			_foragerRun->setFrameX(_index);
			if (_count++ % 5 == 0)
			{
				if (_index++ > 4)
					_index = 0;
			}
		}
		break;
	case ROTATE:
		if (_isLeft)
		{
			if (_count++ % 1 == 0)
			{
				if (_index++ > 11)
				{
					_index = 0;
					_state = STATE::IDLE;
					_isMoveRotate = false;
				}
				IMAGEMANAGER->findImage("playerRotateLeft")->setFrameX(_index);
				IMAGEMANAGER->findImage("HammerImgLeft")->setFrameX(_index);
			}
		}
		else
		{
			_foragerRotate->setFrameY(0);
			_foragerRotate->setFrameX(_index);
			if (_count++ % 1 == 0)
			{
				if (_index++ >11)
				{
					_index = 0;
					_state = STATE::IDLE;
					_isMoveRotate = false;
				}
				IMAGEMANAGER->findImage("HammerImg")->setFrameX(_index);
			}
		}
		break;
	case HAMMERING :
		image *hammerLeft = IMAGEMANAGER->findImage("HammerImgLeft");
		image *hammerRight = IMAGEMANAGER->findImage("HammerImg");
		if (_isLeft)
		{
			_foragerHammering->setFrameY(1);
			_playerHammering->setFrameY(1);
			_foragerHammering->setFrameX(_index);
			_playerHammering->setFrameX(_index);
			if (_hitDelayCount++ % 10 == 0)
			{
				if (_index-- <= 0) {
					_index = 3;
					_hitDelayCount = 1;
				}
			}
		}
		else
		{
			_foragerHammering->setFrameY(0);
			_playerHammering->setFrameY(0);
			_foragerHammering->setFrameX(_index);
			_playerHammering->setFrameX(_index);
			if (_hitDelayCount++ % 10 == 0)
			{
				if (_index++ >= 3) {
					_hitDelayCount = 1;
					_index = 0;
				}
			}
		}
		break;
	}
}

void ForagerPlayer::PlayerControll()
{
	//_map->setPlayerPosTile();
	if (_state != STATE::ROTATE) {
		//������ �ִ� ����
		if (!INPUT->GetKey(VK_LEFT) || !INPUT->GetKey(VK_RIGHT))
		{
			_state = IDLE;
			_isMoveHorizon = false;
			_isMoveVertical = false;
		}
		//�پ�ٴϴ� ���� (�¿� ������)
		if (INPUT->GetKey('A') || INPUT->GetKey('D'))
		{
			_isMoveHorizon = true;
			_state = RUN;
			_isLeft = (INPUT->GetKey('A')) ? true : false;	//���⼳��
		}
		//�پ�ٴϴ� ���� (���� ������)
		if (INPUT->GetKey('W') || INPUT->GetKey('S'))
		{
			_isMoveVertical = true;
			_state = RUN;
			_isUp = (INPUT->GetKey('W')) ? true : false;	//���� ����
		}

		// ������ ���� ������ �� �ְ�
		if (_state != STATE::IDLE)
		{
			//�����ٴϴ� ���� 
			if (INPUT->GetKeyDown(VK_SPACE))
			{
				_state = ROTATE;
				_isMoveRotate = true;
				IMAGEMANAGER->findImage("���׹̳�")->setWidth(5);
			}
		}
		// ��ġ�� �ϴ� ���� 
		if (INPUT->GetKey(VK_LBUTTON))
		{
			unit* targetUnit = _cursor->GetTargetUnit();
			if (targetUnit != nullptr) 
			{
				if (targetUnit->tag == TAG::OBJECT || targetUnit->tag == TAG::ENEMY || targetUnit->tag == TAG::BUILDING)
				{
					// Ÿ�� ������
					if (_hitDelayCount == 18)
					{
						// Ÿ�ٰ��� �Ÿ��� ������
						if (abs(targetUnit->rc.left - rc.left) <= 100 && abs(targetUnit->rc.top - rc.top) <= 100)
						{
							// Ÿ�� ����
							targetUnit->hurt(Atk);
							
							// ������ �ı��Ǹ�
							if (targetUnit->isDead())
							{
								// ���´ϸ� ����
								IMAGEMANAGER->findImage("���׹̳�")->setWidth(5);

								//�� ������ ����ġ ȹ��.
								int t_exp = targetUnit->exp;
								if (t_exp > 0) {
									t_exp = RANDOM->range(t_exp - 2, t_exp + 3);
									POINT pt = { targetUnit->rc.left, targetUnit->rc.top };
									string str = std::to_string(t_exp);
									str.insert(0, "EXP ");
									TEXTMANAGER->ShowFloatingText(str, pt, RGB(100, 255, 100), RGB(0, 0, 0));
									_foragerHp->IncreaseExp(t_exp);
								}

								// Ÿ�� ���� ����
								CAMERA->forceZoomIn(0.02f, 0.005f);
							}
							else {
								CAMERA->forceZoomIn(0.003f, 0.001f);
							}
						}
					
					}
				}
			}
			_state = HAMMERING;
		}

		if (INPUT->GetKeyUp(VK_LBUTTON)) {
			_hitDelayCount = 1;
			_index = (_isLeft) ? 3 : 0;
			_foragerHammering->setFrameX(_index);
			_playerHammering->setFrameX(_index);
		}
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
				_spinSpeed = applySpeed * 2;
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
				_spinSpeed = applySpeed * 2;
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
	else if (PtInRect(&_map->GetTileRc(_playerTilePos + 1), ptPlayerPos))
		_playerTilePos += 1;
	else if (PtInRect(&_map->GetTileRc(_playerTilePos - 1), ptPlayerPos))
		_playerTilePos -= 1;
	else if (PtInRect(&_map->GetTileRc(_playerTilePos + MAPTILEX), ptPlayerPos))
		_playerTilePos += MAPTILEX;
	else if (PtInRect(&_map->GetTileRc(_playerTilePos - MAPTILEX), ptPlayerPos))
		_playerTilePos -= MAPTILEX;

	// �÷��̾� ��ǥ ���� �밢�� Ÿ�� �浹 üũ
	else if (PtInRect(&_map->GetTileRc(_playerTilePos - MAPTILEX + 1), ptPlayerPos))
		_playerTilePos += MAPTILEX + 1;
	else if (PtInRect(&_map->GetTileRc(_playerTilePos - MAPTILEX - 1), ptPlayerPos))
		_playerTilePos -= MAPTILEX - 1;
	else if (PtInRect(&_map->GetTileRc(_playerTilePos + MAPTILEX + 1), ptPlayerPos))
		_playerTilePos += MAPTILEX + 1;
	else if (PtInRect(&_map->GetTileRc(_playerTilePos + MAPTILEX - 1), ptPlayerPos))
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
				t_vUnit[i]->collision();
				// �κ��丮�� ������ �߰� (Ű��ex : treeDrop, berryDrop)
				ITEMMANAGER->vItem_push(t_vUnit[i]->dropItem.itemKey);		
				//_theInven->AcquireItem(t_vUnit[i]->dropItem.itemKey);
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

