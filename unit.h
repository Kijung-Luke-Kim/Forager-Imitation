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
	// �̹��� Ű��
	string objKey;

	// ���°�
	int maxHp;
	int currentHp;
	bool isHit = false;	// �´� ���� Ÿ�� �ִϸ��̼� ���

	// ���
	int exp;
	dropItem dropItem;

	// �ִϸ��̼� ����
	int objFrameX;
	int objFrameY;
	int objMaxFrameX;
	int objMaxFrameY;

	// �ִϸ��̼� ��� �ӵ� ����
	int currentCount;
	int nextCount;

public:
	virtual void update();
	virtual void render(HDC hdc) override;
	
public:
	void hurt(int damage);			// ü�� ����
	virtual void animation();		// �ִϸ��̼� ����
	virtual void collision() { ; };	// �浹�� ���� (�ʵ� ������)
	virtual void dead() { ; };		// ����� ����

public:
	bool isDead();
};

