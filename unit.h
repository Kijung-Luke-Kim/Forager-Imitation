#pragma once
#include "gameObject.h"
#define NUMUNIT 5 //���� 2�� + �ڿ� 3��
class dropItem{
public:
	string itemKey;
};

class unit : public gameObject
{
public:
	int hp;
	int currentHp;
	int exp;
	dropItem dropItem;
	string objKey;
	int objFrameX;
	int objFrameY;
public:

	void hurt(int damage);
	virtual void collision() { ; };
	virtual void dead() { ; };
	virtual void render(HDC hdc) override;

	bool isDead();
};

