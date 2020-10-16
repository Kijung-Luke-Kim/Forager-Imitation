#include "stdafx.h"
#include "UnitManager.h"
#include "productionManager.h"
void UnitManager::init()
{
	//�ڿ� 1 (����, ��, ����)
	IMAGEMANAGER->addFrameImage("berry", "Images/�̹���/������Ʈ/resource/img_object_berry.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rock", "Images/�̹���/������Ʈ/resource/img_object_rock.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tree", "Images/�̹���/������Ʈ/resource/img_object_tree.bmp", 280, 168, 5, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("berryDrop", "Images/�̹���/������/berry.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rockDrop", "Images/�̹���/������/��.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("treeDrop", "Images/�̹���/������/wood.bmp", 56, 56, true, RGB(255, 0, 255));
	
	//�ڿ� 2 ('�ذ�, ��'�� ���������)
	IMAGEMANAGER->addImage("skullHeadDrop", "Images/�̹���/������/skullHead.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("milkDrop", "Images/�̹���/������/milk.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pooDrop", "Images/�̹���/������/poo.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("letherDrop", "Images/�̹���/������/lether.bmp", 56, 56, true, RGB(255, 0, 255));


	
	//���ʹ� - (�ذ�, ��, ���̽�)
	IMAGEMANAGER->addFrameImage("skull", "Images/�̹���/NPC/�ذ�idle.bmp", 280, 112, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skullAppear", "Images/�̹���/NPC/�ذ�Appear.bmp", 224, 56, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skullAttack", "Images/�̹���/NPC/�ذ�attack.bmp", 393, 112, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skullIdle", "Images/�̹���/NPC/�ذ�stay.bmp",224 ,112 , 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("cow", "Images/�̹���/NPC/Ȳ��IDLE.bmp", 400, 100, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cowWalk", "Images/�̹���/NPC/Ȳ��WALK.bmp", 560, 100, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cowDash", "Images/�̹���/NPC/cowDash.bmp", 320, 100, 4, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("wraithAttack", "Images/�̹���/NPC/���̽�2.bmp", 1710, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wraithIdle", "Images/�̹���/NPC/���̽�IDLE2.bmp", 2280, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wraithBullet", "Images/�̹���/NPC/���̽�����߻�.bmp", 80, 600, 1, 2, true, RGB(255, 0, 255));
	
	// NPC
	IMAGEMANAGER->addFrameImage("David", "Images/�̹���/NPC/img_npc_David.bmp", 444, 88, 4, 1, true, RGB(255, 0, 255));


	// ü�¹�
	IMAGEMANAGER->addImage("hpBarBG", "Images/�̹���/NPC/NPCü��(��).bmp", 50, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hpBar", "Images/�̹���/NPC/NPCü��(��).bmp", 40, 10, true, RGB(255, 0, 255));

	// ����ü �Ŵ��� ����
	_projectileManager = new ProjectileManager;
	_projectileManager->init();
	_pProjectiles = _projectileManager->GetProjectile();

	// ���� �Ŵ��� ����
	//_spawnManager = new SpawnManager;
	//_spawnManager->init();
	SPAWNMANAGER->init();
}

void UnitManager::release()
{
	for(int i = 0 ; i < _vUnits.size(); i++)
		SAFE_DELETE(_vUnits[i]);
	_vUnits.clear();
}


void UnitManager::update()
{
	Sorting();
	CheckRemoveUnit();

	// ���� ������Ʈ
	for (int i = 0; i < _vUnits.size(); i++) {
		if (_vUnits[i]->tag != TAG::PLAYER ) {
			_vUnits[i]->update();
		}

		// ī�޶� �ܰ��� NPC, �ʵ� �������� �浹ó�� ����
		RECT temp;
		if (_vUnits[i]->tag == TAG::ITEM) continue;
		if (_vUnits[i]->tag == TAG::NPC) continue;
		if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &_vUnits[i]->rc)) continue;

		// ����ü�� ���ְ��� �浹ó��
		checkCollision(_vUnits[i]);
	}

	//_spawnManager->update();
	SPAWNMANAGER->update();
	_projectileManager->update();
}

void UnitManager::checkCollision(unit * p_unit)
{
	for (int k = 0; k < PROJECTILE_MAX; k++) {

		RECT temp;
		if (!_pProjectiles[k].isAppear) continue; 	// �߻� �� �� ����ü�� ����

		// ���ְ� �浹�� ����ü�� �ִٸ�
		if (IntersectRect(&temp, &p_unit->rc, &RectMakeCenter(_pProjectiles[k].x, _pProjectiles[k].y, 20, 20)))
		{
			// Enemy ����ü�� �÷��̾�Ը� ������ ����
			if (_pProjectiles[k].isEnemyProjectTile)
			{
				if (p_unit->tag == TAG::PLAYER)
				{
					//SOUNDMANAGER->play("���ɹ���´¼Ҹ�", 0.4f);
					IMAGEMANAGER->findImage("���׹̳�")->setWidth(5);
				}
					
				if (p_unit->tag != TAG::ENEMY)
					_pProjectiles[k].isAppear = false;
				
			}
			// Player ����ü�� ��� ���ֿ��� ������ ����
			else {
				if (p_unit->tag != TAG::PLAYER) {
					p_unit->hurt(_pProjectiles[k].damage);
					_pProjectiles[k].isAppear = false;
				}
			}
		}
	}
}


void UnitManager::render(HDC hdc)
{
	// ���̾� : Terrain
	for (int i = 0; i < _vUnits.size(); i++) {
		if ((*_vUnits[i]).layer == LAYER::TERRAIN) {
			RECT temp;
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &(*_vUnits[i]).rc)) continue;
			(*_vUnits[i]).render(hdc);
		}
	}

	// ���̾� : Object
	for (int i = 0; i < _vUnits.size(); i++) {
		if ((*_vUnits[i]).layer == LAYER::OBJECT) {
			RECT temp;
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &(*_vUnits[i]).rc)) continue;
			(*_vUnits[i]).render(hdc);
		}
	}

	_projectileManager->render(hdc);
}



bool compare(unit* i, unit* j) {
	return (*i).GetCenterY() < (*j).GetCenterY();
}


// y�� ����
void UnitManager::Sorting()
{
	sort(_vUnits.begin(), _vUnits.end(), compare);
}

// �װų� �����ؾߵ� ��ü�� ����
void UnitManager::CheckRemoveUnit()
{
	if (_vUnits.size() > 0) {
		for (auto iter = _vUnits.begin(); iter != _vUnits.end();) {
			if ((*iter)->isDead()) {
				if ((*iter)->tag == TAG::BUILDING) {
					PRODUCTIONMANAGER->removeBuildingRc((*iter)->rc);
				}
				SAFE_DELETE((*iter));
				
				iter = _vUnits.erase(iter);
			}
			else
				++iter;
		}
	}
}


void UnitManager::AddUnits(ForagerPlayer* p_unit)
{
	_player = p_unit;
	_vUnits.push_back(p_unit);

	// NPC ����
	AddUnits("David", { WINSIZEX / 2 + 100, WINSIZEY / 2 + 100 }, false);
}

void UnitManager::AddUnits(skull* p_unit, bool test)
{
	_vUnits.push_back(p_unit);
}

void UnitManager::AddUnits(wraith* p_unit, bool test)
{
	_vUnits.push_back(p_unit);
}

void UnitManager::AddUnits(cow * p_unit, bool test)
{
	_vUnits.push_back(p_unit);
}


void UnitManager::AddUnits(string p_unitName, POINT p_pos, bool enemyCheck)
{
	if (_vEnemy.size() >= MAXENEMYUNIT) return;
	// ���ʹ� ����
	if (enemyCheck) {
		//�ذ�
		if (p_unitName == "skull")
		{
			skull* _skull = new skull;
			_skull->setLinkMap(_map);
			_skull->setEnemy(p_unitName, "skullHeadDrop", _player, p_pos);
			_skull->init();

			_vUnits.push_back(_skull);
			_vEnemy.push_back(_skull);
		}

		//��
		if (p_unitName == "cow")
		{
			cow* _cow = new cow;
			_cow->setLinkMap(_map);
			_cow->setEnemy(p_unitName, "milkDrop", _player, p_pos);
			_cow->init();
			_vUnits.push_back(_cow);
			_vEnemy.push_back(_cow);
		}

		//���̽�
		if (p_unitName == "wraithIdle")
		{
			wraith* _wraith = new wraith;
			_wraith->setLinkMap(_map);
			_wraith->setEnemy(p_unitName, "letherDrop", _player, p_pos);
			_wraith->init();
			_vUnits.push_back(_wraith);
			_vEnemy.push_back(_wraith);
		}
	}
	
	// NPC ����
	else {
		if (p_unitName == "David")
		{
			npc* t_npc = new npc;
			t_npc->setNpc(p_unitName, p_pos, &_player->rc);
			_vUnits.push_back(t_npc);
		}
	}
}

// ���� �߰�
void UnitManager::AddUnits(string p_itemKey, POINT p_pos)
{
	for (int i = 0; i < 3; i++) {
		fieldItem* t_fieldItem = new fieldItem;
		t_fieldItem->setFieldItem(p_pos, p_itemKey);
		_vUnits.push_back(t_fieldItem);
	}
}

void UnitManager::AddProduction(string p_itemKey, POINT p_pos)
{
	fieldItem* t_fieldItem = new fieldItem;

	t_fieldItem->setFieldItem(p_pos, p_itemKey);
	_vUnits.push_back(t_fieldItem);
}



int UnitManager::GetMonsterCount()
{
	int t_monsterCount = 0;
	for (int i = 0; i < _vUnits.size(); i++) {
		if (_vUnits[i]->tag == TAG::ENEMY) {
			t_monsterCount++;
		}
	}
	return t_monsterCount;
}

void UnitManager::setLinkMap(earth * p_map)
{
	_map = p_map;
	//_spawnManager->setLinkMap(_map);
	SPAWNMANAGER->setLinkMap(_map);
}


void UnitManager::AddBuilding(string buildkey, tile * _tile, int tileindex)
{
	building* _building = new building;
	_building->setBuilding(buildkey, _tile, tileindex);
	_vUnits.push_back(_building);
}

void UnitManager::AddBuilding(string buildkey, vector<tile*> tiles, int tileindex)
{
	building* _building = new building;
	_building->setBuilding(buildkey, tiles, tileindex);
	_vUnits.push_back(_building);
	PRODUCTIONMANAGER->settion(_building->rc);
	//_production->settion(_building->rc);��
}

void UnitManager::AddResource(tile* p_tile, int p_tileIndex)
{
	inGameResource* _res = new inGameResource;
	_res->setRandomRes(p_tile, p_tileIndex);
	_vUnits.push_back(_res);
}

void UnitManager::AddResource(string key, tile * _tile, int p_tileIndex)
{
	inGameResource* _res = new inGameResource;
	_res->setResource(key, _tile, p_tileIndex);
	_vUnits.push_back(_res);
}





