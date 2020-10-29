#pragma once
#include "enemy.h"
#define MOVEMAX 56*3
#define JUMPMAX 56*2

struct tagBRect
{
	float left;
	float right;
	float top;
	float bottom;

};
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

	bool _slimeGotDamage;

	int slimeFireCount;

private:

public:

	HRESULT init();
	void update();
	void render(HDC hdc) override;


	void slimeBossAnimation();
	void slimeJump();
	void jumpUp();
	void jumpDown();
	void jumpStop();
	void targetDest();
	void slimeFire();
	void slimeFollow();
};

