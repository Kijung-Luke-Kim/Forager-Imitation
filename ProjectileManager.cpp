#include "stdafx.h"
#include "ProjectileManager.h"

void ProjectileManager::init()
{
	IMAGEMANAGER->addFrameImage("BowArrow", "Images/�̹���/������/img_UI_bowArrow.bmp", 448, 56, 8, 1, true, RGB(255, 0, 255));
	for (int i = 0; i < PROJECTILE_MAX; i++) {
		_projectiles[i].imgKey = "temp";
		_projectiles[i].x = 0;
		_projectiles[i].y = 0;
		_projectiles[i].angle = 0.0f;
		_projectiles[i].damage = 0;
		_projectiles[i].frameX = 0;
		_projectiles[i].frameY = 0;
		_projectiles[i].isAppear = false;
		_projectiles[i].isEnemyProjectTile = false;
		_projectiles[i].isStretch = false;
		_projectiles[i].speed = 0;
	}
}

void ProjectileManager::update()
{
	for (int i = 0; i < PROJECTILE_MAX; i++) {
		if (_projectiles[i].isAppear) {
			_projectiles[i].x += cosf(_projectiles[i].angle * PI / 180.0f) * _projectiles[i].speed;
			_projectiles[i].y -= sinf(_projectiles[i].angle * PI / 180.0f) * _projectiles[i].speed;
		}
	}
}

void ProjectileManager::render(HDC hdc)
{
	for (int i = 0; i < PROJECTILE_MAX; i++) {
		if (_projectiles[i].isAppear) {
			if(!_projectiles[i].isStretch)
				IMAGEMANAGER->frameRender(_projectiles[i].imgKey, hdc, 
									 CAMERA->GetRelativeX(_projectiles[i].x), CAMERA->GetRelativeY(_projectiles[i].y), _projectiles[i].frameX, _projectiles[i].frameY);
		}
	}
}

void ProjectileManager::CreateProjectile(string imgKey, int x, int y, int damage, float angle, float speed, bool isEnemy, bool isStretch)
{
	for (int i = 0; i < PROJECTILE_MAX; i++) {
		if (!_projectiles[i].isAppear) {
			_projectiles[i].imgKey = imgKey;
			_projectiles[i].x = x;
			_projectiles[i].y = y;
			_projectiles[i].damage = damage;
			_projectiles[i].angle = angle;
			_projectiles[i].speed = speed;
			_projectiles[i].isEnemyProjectTile = isEnemy;
			_projectiles[i].isStretch = isStretch;
			_projectiles[i].isAppear = true;


			float minAngle = -20.0f;
			float maxAngle = 20.0f;
			float addAngle = 40.0f;
			int count = 0;
			for (int x = 0; x < 8; x++) {
				if (minAngle + (count * addAngle) <= angle && angle <= maxAngle + (count * addAngle)) {
					_projectiles[i].frameX = x % 8;
					break;
				}
				count++;
			}
			_projectiles[i].frameY = 0;
			break;
		}
	}
}
