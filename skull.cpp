#include "stdafx.h"
#include "skull.h"


HRESULT skull::init()
{
	skullMoveCount = 0;
	skullIdleCount = 0;
	searchCount = 0;
	skullHitCount = 0;
	skullHitWaitCount = 0;
	skullAttackRange = 80;
	_attackIndex = 0;
	hitPlayer = false;
	tryAttack = false;

	isattacking = false;

	Atk = 15;
	
	return S_OK;
}

void skull::update()
{
	cout << isattacking << endl;
	skullAnimation();
	skullMove();
	if (_state != APPEAR ) {
		canAttackCheck();
	}
	skullLookDirection();
}

void skull::render(HDC hdc)
{
	if (0 < currentHp && currentHp < maxHp) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.bottom + 16));
		_hpBar.render(hdc);
	}
	switch (_state)
	{
	case STAY:
		IMAGEMANAGER->frameRender("skull", hdc, CAMERA->GetRelativeX(rc.left - 13 ),
			CAMERA->GetRelativeY(rc.top - 10) , objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case ATTACK:
		IMAGEMANAGER->frameRender("skullAttack", hdc, CAMERA->GetRelativeX(rc.left -53),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case APPEAR:
		IMAGEMANAGER->frameRender("skullAppear", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case IDLE2:
		IMAGEMANAGER->frameRender("skullIdle", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	}
}

//1Ÿ�Ͼ� �����¿� ���������̴µ�, �� 5�� 
void skull::skullMove()
{
	if (_state == STAY) {
		if (!checkDestination)
		{
			searchCount++;
			if (searchCount > 50)
			{
				if (isattacking) {
					Astar astar;
					auto path = astar.pathFinding(_map->GetTiles(), _enemyTilePos, _target->GetPlayerTilePos(), true, false);
					//_vDestTileIndex = path;
					_vDestTileIndex.push_back(path[0]);
					_enemyTilePos = path[0];
					checkDestination = true;
					_destCount = 0;
				}
				else {
					vector<int> vPossibleDestination;
					//��
					if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1 &&
						!_map->GetTile(_enemyTilePos + 1).hasUnit &&
						_map->GetTile(_enemyTilePos + 1).terrKey == "plaintile") {
						vPossibleDestination.push_back(_enemyTilePos + 1);
					}
					//��
					if (_map->GetTileX(_enemyTilePos) > 0 &&
						!_map->GetTile(_enemyTilePos - 1).hasUnit &&
						_map->GetTile(_enemyTilePos - 1).terrKey == "plaintile") {
						vPossibleDestination.push_back(_enemyTilePos - 1);
					}
					//��
					if (_map->GetTileY(_enemyTilePos) < MAPTILEY - 1 &&
						!_map->GetTile(_enemyTilePos + MAPTILEX).hasUnit &&
						_map->GetTile(_enemyTilePos + MAPTILEX).terrKey == "plaintile") {
						vPossibleDestination.push_back(_enemyTilePos + MAPTILEX);
					}
					//��
					if (_map->GetTileX(_enemyTilePos) > 0 &&
						!_map->GetTile(_enemyTilePos - MAPTILEX).hasUnit &&
						_map->GetTile(_enemyTilePos - MAPTILEX).terrKey == "plaintile") {
						vPossibleDestination.push_back(_enemyTilePos - MAPTILEX);
					}
					if (vPossibleDestination.size() > 0) {
						int randDestInd = RANDOM->range(int(vPossibleDestination.size()));
						if (vPossibleDestination[randDestInd] > _enemyTilePos) {
							isLeft = false;
						}
						else if (vPossibleDestination[randDestInd] <= _enemyTilePos) {
							isLeft = true;
						}
						_vDestTileIndex.push_back(vPossibleDestination[randDestInd]);
						_enemyTilePos = vPossibleDestination[randDestInd];
					}
					checkDestination = true;
					_destCount = 0;
				}

			}
		}
		else
		{
			if (_vDestTileIndex.size() > 0)
			{
				POINT tDestination = { _map->GetTile(_vDestTileIndex[_destCount]).rc.left , _map->GetTile(_vDestTileIndex[_destCount]).rc.top };
				if (abs(rc.left - tDestination.x) > MOVESPEED || abs(rc.top - tDestination.y) > MOVESPEED)
				{
					if (tDestination.x < rc.left)
					{
						OffsetRect(&rc, -MOVESPEED, 0);
					}
					else if (tDestination.x > rc.left)
					{
						OffsetRect(&rc, MOVESPEED, 0);
					}
					if (tDestination.y > rc.top)
					{
						OffsetRect(&rc, 0, MOVESPEED);
					}
					else if (tDestination.y < rc.top)
					{
						OffsetRect(&rc, 0, -MOVESPEED);
					}

				}
				else
				{
					_destCount++;
					if (_vDestTileIndex.size() <= _destCount)
					{
						checkDestination = false;
						searchCount = 0;
						_vDestTileIndex.clear();
					}
				}
			}
		}
	}
}

void skull::canAttackCheck()
{
	if (!tryAttack)
	{
		if (abs(_target->rc.left - rc.left) <= skullAttackRange && abs(_target->rc.top - rc.top) <= skullAttackRange)
		{
			tryAttack = true;
			isattacking = true;
		}
		else
			_state = STAY;
	}
	else
	{

		if (skullHitWaitCount > 120)
		{
			//if (skullHitCount == 17) {
			//	if (abs(_target->rc.left - rc.left) <= skullAttackRange && abs(_target->rc.top - rc.top) <= skullAttackRange)
			//		//IMAGEMANAGER->findImage("���׹̳�")->setWidth(15);
			//		_target->hurt(Atk);

			//}
			_state = ATTACK;
		}
		else {
			skullHitWaitCount++;
			_state = IDLE2;
		}
	}
}

void skull::skullAnimation()
{
	switch (_state)
	{
		//�ذ� �ٴ��
	case STAY:
		if (isLeft)
		{
			objFrameY = 1;
			objFrameX = _index;
			if (_count++ % 10 == 0)
			{
				if (_index-- <= 0)
					_index = 4;
			}
		}
		else
		{
			objFrameY = 0;
			objFrameX = _index;
			if (_count++ % 10 == 0)
			{
				if (_index++ > 5)
					_index = 0;
			}
		}
		break;
		//�ذ� ������ ����.
	case APPEAR:
		objFrameY = 0;
		objFrameX = _index;
		if (_count++ % 30 == 0)
		{
			if (_index++ > 4)
			{
				_index = 0;
				_state = STAY;
			}
		}
		break;

	case IDLE2:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _index;
		if (_count++ % 10 == 0)
		{
			if (_index++ > 5)
				_index = 0;
		}
		break;
		//�ذ� ����
	case ATTACK:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _attackIndex;

		skullHitCount++;
		if (skullHitCount < 5) _attackIndex = 0;
		else if (skullHitCount == 10) _attackIndex = 1;
		else if (skullHitCount == 15) _attackIndex = 2;
		else if (skullHitCount == 20) _attackIndex = 1;
		else if (skullHitCount >= 25) {
			_attackIndex = 0;
			skullHitCount = 1;
			skullHitWaitCount = 0;
			tryAttack = false;
		}
		break;
	}
}

void skull::skullLookDirection()
{
	if ( _state == ATTACK || isattacking)
	{
		if (rc.right > _target->rc.right && rc.left > _target->rc.left)
			isLeft = true;
		else
			isLeft = false;
	}
}

