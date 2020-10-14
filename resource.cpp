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
	SOUNDMANAGER->play("������ź��");
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

	_hpBar.init("hpBar", "hpBarBG");

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

	if (this->objKey == "berry") {
		SOUNDMANAGER->play("�����ı�");
	}
	if (this->objKey == "tree") {
		SOUNDMANAGER->play("�����ı�");
	}
	if (this->objKey == "rock") {
		SOUNDMANAGER->play("�����ı�");
	}
}

void resource::render(HDC hdc)
{
	if (0 < currentHp && currentHp < maxHp) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.bottom));
		_hpBar.render(hdc);
	}

	IMAGEMANAGER->frameRender(objKey, hdc,
		CAMERA->GetRelativeX(rc.left),
		CAMERA->GetRelativeY(rc.bottom - IMAGEMANAGER->findImage(objKey)->getFrameHeight()),
		objFrameX, objFrameY, CAMERA->GetZoom());
}

void resource::hurt(int damage)
{
	currentHp -= damage;

	if (currentHp <= 0)
		dead();

	else
		isHit = true;

	if (this->objKey == "berry") {
		SOUNDMANAGER->play("����Ÿ��");
	}
	if (this->objKey == "tree") {
		SOUNDMANAGER->play("����Ÿ��");
	}
	if (this->objKey == "rock") {
		SOUNDMANAGER->play("����Ÿ��");
	}
}


