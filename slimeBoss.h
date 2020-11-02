#pragma once
#include "enemy.h"
//#define MOVEMAX 56*3
//#define JUMPMAX 56*2

#define MOVERANGE 2
#define MOVESPEED 1

struct tagBRect
{
	float left;
	float right;
	float top;
	float bottom;

};

static bool s_allAttack = false;

class slimeBoss :public enemy
{
private :
	POINT originPos;			//�������� �����ϱ� ���� ���� ��ġ.
	POINT currentPos;			//�����ϸ鼭 �̵����� ���� ��ġ
	POINT destPos;				//��ǥ, ���� ��ġ
	POINT midPos;				//�߰� ��ġ 

	tagBRect fRectMakeCenter(float x, float y, float width, float height)
	{
		tagBRect rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
		return rc;
	}
	tagBRect _fRc;

	float currentJumpSpeed;
	int jumpWaitTime;			//���� ���(delay)
	int jumpTime;				//���� Ÿ��
	int shootDelayTime;
	float lerpRatio;
	bool _isJump;
	bool _canJump;
	bool _canSpawn;
	bool _slimeGotDamage;

	int slimeFireCount;
	//====================================================
	bool _canFollow;
	bool isattacking;
	int searchCount;
	int slimeShootCount;
	int _difficultyLevel;
public:
	void setCanSpawn() { _canSpawn = true; };

public:

	HRESULT init(int p_level);
	void update();
	void hurt(int Damage, bool onlyEffect) override;
	void render(HDC hdc) override;


	void slimeBossAnimation();
	void targetDest();
	void slimeFire();



	//====================================================
	void slimeMove();
};

