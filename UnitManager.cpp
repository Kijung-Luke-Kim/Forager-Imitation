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
	IMAGEMANAGER->addFrameImage("cowDash", "Images/�̹���/NPC/Ȳ��WALK.bmp", 560, 100, 7, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("wraithAttack", "Images/�̹���/NPC/���̽�2.bmp", 1710, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wraithIdle", "Images/�̹���/NPC/���̽�IDLE2.bmp", 2280, 400, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("wraithBullet", "Images/�̹���/NPC/���̽�����߻�.bmp", 80, 600, 1, 2, true, RGB(255, 0, 255));
	


	// ü�¹�
	IMAGEMANAGER->addImage("hpBarBG", "Images/�̹���/NPC/NPCü��(��).bmp", 50, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hpBar", "Images/�̹���/NPC/NPCü��(��).bmp", 40, 10, true, RGB(255, 0, 255));
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

	for (int i = 0; i < _vUnits.size(); i++) {
		if (_vUnits[i]->tag != TAG::PLAYER ) {
			_vUnits[i]->update();
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
				SAFE_DELETE((*iter));
				iter = _vUnits.erase(iter);
			}
			else
				++iter;
		}
	}
}


void UnitManager::AddUnits(unit* p_unit)
{
	_player = p_unit;
	_vUnits.push_back(p_unit);
}

void UnitManager::AddUnits(skull* p_unit, bool test)
{
	_vUnits.push_back(p_unit);
}

void UnitManager::AddUnits(wraith* p_unit, bool test)
{
	_vUnits.push_back(p_unit);
}

void UnitManager::AddUnits(tile* p_tile)
{
	
	resource* _res = new resource;
	_res->setRandomRes(p_tile);
	_vUnits.push_back(_res);
}

void UnitManager::AddUnits(unit * p_enemy, string p_monsterName)
{
	//�ذ�
	if (p_monsterName == "skull")
	{
		
		
		_vUnits.push_back(p_enemy);
	}
	
	//��
	if (p_monsterName == "cow")
	{
		cow* _cow = new cow;
		_cow->setEnemy(p_monsterName, "milkDrop", _player);
		_cow->init();
		_vUnits.push_back(_cow);
		
	}
	
	//���̽�
	if (p_monsterName == "wraith")
	{
		//wraith* _wraith = new wraith;
		//_wraith->setEnemy(p_monsterN)
		_vUnits.push_back(p_enemy);

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

void UnitManager::AddBuilding(string buildkey, tile * _tile)
{
	building* _building = new building;
	_building->setBuilding(buildkey, _tile);
	_vUnits.push_back(_building);
}

void UnitManager::AddBuilding(string buildkey, vector<tile*> tiles)
{
	building* _building = new building;
	_building->setBuilding(buildkey, tiles);
	_vUnits.push_back(_building);
	PRODUCTIONMANAGER->settion(_building->rc);
	//_production->settion(_building->rc);

}




