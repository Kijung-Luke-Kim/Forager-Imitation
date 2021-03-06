#include "stdafx.h"
#include "demon.h"

HRESULT demon::init()
{
	_state4 = DIDLE;
	demonWaitCount = 0;
	demonBrassCount = 0;
	demonHitCount = 0;
	searchCount = 0;
	demonAttackRange = 350;
	skillFireCount = 0;

	tryAttack = false;
	isattacking = true;

	return S_OK;
}

void demon::update()
{
	demonAnimation();
	demonLookDirection();
	demonAttack();
	demonMove();

}

void demon::render(HDC hdc)
{
	if ((float)currentHp / maxHp <= 0.8f) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(rc.left - 11), CAMERA->GetRelativeY(rc.bottom + 16));
		_hpBar.render(hdc);
	}

	switch (_state4)
	{
	case DWALK:
		IMAGEMANAGER->frameRender("demonWalk", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case DIDLE:
		IMAGEMANAGER->frameRender("demonIdle", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case DYELL:
		IMAGEMANAGER->frameRender("demonYell", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	}
	RECT temp;
	if (IntersectRect(&temp, &CAMERA->GetCameraRect(), &rc)) {
		if (_state4 == DWALK) {
			POINT ptCenter = { rc.left + (rc.right - rc.left) / 2 + RANDOM->range(-10, 0), rc.top + (rc.bottom - rc.top) / 2 - RANDOM->range(-1, -6) };
			// �߰��� ����Ʈ
			if (_count % 10 == 0) {
				float randomScale = RANDOM->range(0.5f, 0.7f);
				EFFECTMANAGER->ShowEffectAlphaSize("Walk1", ptCenter, 0.25f, randomScale, 50, 200, true);
			}
		}
	}
}

void demon::demonMove()
{
	if (_state4 == DIDLE)
	{
		if (!checkDestination)
		{
			searchCount++;
			if (searchCount > 1)
			{
				if (isattacking) {
					
					auto path = ASTAR->pathFinding(_map->GetTiles(), _enemyTilePos, _target->GetPlayerTilePos(), true, true);
					//_vDestTileIndex = path;
					if (path.size() > 0) {
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
			_state4 = DWALK;
			if (_vDestTileIndex.size() > 0)
			{
				POINT tDestination = { _map->GetTile(_vDestTileIndex[_destCount]).rc.left , _map->GetTile(_vDestTileIndex[_destCount]).rc.top };
				if (abs(rc.left - tDestination.x) > enemySpeedX || abs(rc.top - tDestination.y) > enemySpeedY)
				{
					if (tDestination.x < rc.left)
					{
						OffsetRect(&rc, -enemySpeedX, 0);
					}
					else if (tDestination.x > rc.left)
					{
						OffsetRect(&rc, enemySpeedX, 0);
					}
					if (tDestination.y > rc.top)
					{
						OffsetRect(&rc, 0, enemySpeedY);
					}
					else if (tDestination.y < rc.top)
					{
						OffsetRect(&rc, 0, -enemySpeedY);
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

void demon::demonAttack()
{
	if (!tryAttack)
	{
		if (abs(_target->rc.left - rc.left) <= demonAttackRange && abs(_target->rc.top - rc.top) <= 30) {
			tryAttack = true;
			isattacking = true;
		}
		else
			_state4 = DIDLE;
	}
	else
	{
		demonWaitCount++;
		if (demonWaitCount > 23)
		{
			_state4 = DYELL;
			demonBrassFire();
		}
		else
			_state4 = DIDLE;
	}
}

void demon::demonAnimation()
{
	switch (_state4)
	{
	case DWALK:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _index;
		if (_count++ % 10 == 0)
		{
			if (_index++ > 11)
				_index = 0;
		}
		break;
		break;
	case DIDLE:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _index;
		if (_count++ % 10 == 0)
		{
			if (_index++ > 4)
				_index = 0;
		}
		break;
	case DYELL:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _index;
		if (_count++ % 15 == 0)
		{
			if (_index++ > 10)
			{
				_index = 0;
				demonWaitCount = 0;
				demonHitCount = 1;
				tryAttack = false;	


				_attackIndex = 0;
				searchCount = 0;
				checkDestination = false;
				isattacking = true;
				_state4 = DWALK;
			}
		}
		break;
	}
}

void demon::demonLookDirection()
{
	if (_state4 == DIDLE || _state4 == DWALK)
	{
		if (rc.right > _target->rc.right && rc.left > _target->rc.left)
			isLeft = true;
		else
			isLeft = false;
	}
}

void demon::demonBrassFire()
{
	skillFireCount++;
	if (skillFireCount % 200 == 0) {
		SOUNDMANAGER->play("�Ǹ����������Ҹ�");
		_count = 0;
		_index = 0;
		
		for (int i = 0; i < 2; i++)
		{
			if(isLeft)
				UNITMANAGER->GetProjectileMG()->CreateProjectile("demonBrass", GetCenterX() - 320, GetCenterY() - 40, atk, 320, 40, isLeft);
			else
				UNITMANAGER->GetProjectileMG()->CreateProjectile("demonBrass", GetCenterX(), GetCenterY() - 40, atk, 320, 40, isLeft);
		}
		skillFireCount = 0;
	}
}
