#pragma once
#include "unit.h"

#define PI 3.1415926f


enum SKULLSTATE
{
	STAY,	//�ɾ�ٴϴ� �̹����� 
	ATTACK
};

class enemy :public unit
{
private:
	

private : 
	
	SKULLSTATE _state;
	int _index;
	int _count;
	int _enemyMoveCount;
	bool isLeft;
	bool _isUp;			//�����̳�?
	bool _isMoveVertical;
	bool isAngle;

public:
	

	int skullMoveRandomTileCount;

	virtual void setEnemy();
	virtual void render(HDC hdc) override;
	virtual void update() override;
	virtual void dead() override;
	void skullAnimation();
	
	void skullMove();
	float skullToPlayerAngle();

	

};

