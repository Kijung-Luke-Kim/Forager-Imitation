#pragma once
#include "gameObject.h"
#include "progressBar.h"

#define NUMUNIT 5 //���� 2�� + �ڿ� 3��
class dropItem{
public:
	string itemKey;
};

class unit : public gameObject
{

protected:
	progressBar _hpBar;
	

public:
	// �̹��� Ű��
	string objKey;

	// ���°�
	int maxHp;
	int currentHp;
	bool isHit = false;	// �´� ���� Ÿ�� �ִϸ��̼� ���
	
	int atk;
	// ���
	int exp;
	dropItem dropItem;
	int tileIndex; // ���� �ε��

	// �ִϸ��̼� ����
	int objFrameX;
	int objFrameY;
	int objMaxFrameX;
	int objMaxFrameY;

	// �ִϸ��̼� ��� �ӵ� ����
	int currentCount;
	int nextCount;
	int frameX;
	int count;

	bool waveUp;
	

public:
	virtual void update();
	void render(HDC hdc) override;
	
public:
	virtual void hurt(int damage, bool onlyEffect = false);			// ü�� ����
	virtual void animation();		// �ִϸ��̼� ����
	virtual void collision() { ; };	// �浹�� ���� (�ʵ� ������)
	virtual void dead();		// ����� ����
	bool isDead();
};

