#include "stdafx.h"
#include "UnitManager.h"

void UnitManager::init()
{
	//�ڿ�
	IMAGEMANAGER->addFrameImage("berry", "Images/�̹���/������Ʈ/resource/img_object_berry.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rock", "Images/�̹���/������Ʈ/resource/img_object_rock.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tree", "Images/�̹���/������Ʈ/resource/img_object_tree.bmp", 280, 168, 5, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("berryDrop", "Images/�̹���/������/berry.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rockDrop", "Images/�̹���/������/��.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("treeDrop", "Images/�̹���/������/wood.bmp", 56, 56, true, RGB(255, 0, 255));
}


void UnitManager::update()
{
	Sorting();
	CheckRemoveUnit();
}


void UnitManager::render(HDC hdc)
{
	//����(�ڿ�, ����) ����
	for (int i = 0; i < _vUnits.size(); i++) {
		RECT temp;
		if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &(*_vUnits[i]).rc)) continue;

		// Resource �����ӷ���
		if ((*_vUnits[i]).tag == TAG::OBJECT) {
			IMAGEMANAGER->frameRender((*_vUnits[i]).objKey, hdc,
				CAMERA->GetRelativeX((*_vUnits[i]).rc.left),
				CAMERA->GetRelativeY((*_vUnits[i]).rc.bottom - IMAGEMANAGER->findImage((*_vUnits[i]).objKey)->getFrameHeight()),
				(*_vUnits[i]).objFrameX, (*_vUnits[i]).objFrameY);
		}
		// fieldItem ����
		else {
			IMAGEMANAGER->render((*_vUnits[i]).objKey, hdc,
				CAMERA->GetRelativeX((*_vUnits[i]).rc.left),
				CAMERA->GetRelativeY((*_vUnits[i]).rc.bottom));
		}

	}
}



bool compare(unit* i, unit* j) {
	return (*i).rc.top < (*j).rc.top;
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

void UnitManager::AddUnits(tile* p_tile)
{
	resource* _res = new resource;
	_res->setRandomRes(p_tile);
	_vUnits.push_back(_res);
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
