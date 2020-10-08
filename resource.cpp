#include "stdafx.h"
#include "resource.h"

void resource::setRandomRes(tile* tile)
{
	_tile = tile;
	this->rc = _tile->rc;
	this->layer = LAYER::OBJECT;
	this->tag = TAG::OBJECT;
	this->objFrameX = 0;
	this->objFrameY = 0;
	this->objMaxFrameY = 0;
	this->currentCount = 0;
	this->nextCount = 2;
	switch (RANDOM->range(NUMRES)) {
	case 0:
		this->objKey = "berry";
		this->dropItem.itemKey = "berryDrop";
		this->maxHp = BERRYHP;
		this->exp = 7;
		this->objMaxFrameX = 1;
		break;
	case 1:
		this->objKey = "rock";
		this->dropItem.itemKey = "rockDrop";
		this->exp = 7;
		this->maxHp = ROCKHP;
		this->objMaxFrameX = 1;
		break;
	case 2:
		this->objKey = "tree";
		this->dropItem.itemKey = "treeDrop";
		this->exp = 7;
		this->maxHp = TREEHP;
		this->objMaxFrameX = 4;
		break;
	}
	currentHp = maxHp;
}

void resource::dead()
{
	POINT ptCenterPos = { GetCenterX(), GetCenterY() - 10 };

	// �ı��Ǹ� �ʵ������ ����
	UNITMANAGER->AddUnits(dropItem.itemKey, ptCenterPos);

	// ���� ����Ʈ
	EFFECTMANAGER->ShowEffectFrame(EFFECTMANAGER->smokeEff, ptCenterPos, 4, true);

	if (_tile != nullptr)
	{
		_tile->hasUnit = false;
		_tile->canPass = true;
	}
		
}

void resource::render(HDC hdc)
{
	IMAGEMANAGER->frameRender(objKey, hdc,
		CAMERA->GetRelativeX(rc.left),
		CAMERA->GetRelativeY(rc.bottom - IMAGEMANAGER->findImage(objKey)->getFrameHeight()),
		objFrameX, objFrameY, CAMERA->GetZoom());
}


