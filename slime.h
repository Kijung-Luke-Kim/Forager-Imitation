#pragma once
#include "enemy.h"
#define MOVEMAX 56*3
#define JUMPMAX 56*2

enum SLIMESTATE
{


};

struct tagFRect
{
	float left;
	float right;
	float top;
	float bottom;
	

};
class slime : public enemy
{
private:
	POINT originPos;			//�������� �����ϱ� ���� ���� ��ġ.
	POINT currentPos;			//�����ϸ鼭 �̵����� ���� ��ġ
	POINT destPos;				//��ǥ, ���� ��ġ
	POINT midPos;				//�߰� ��ġ 

	tagFRect fRectMakeCenter(float x, float y, float width, float height)
	{
		tagFRect rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
		return rc;
	}
	
	tagFRect _fRc;
		 
	float currentJumpSpeed;
	int jumpWaitTime;			//���� ���(delay)
	int jumpTime;				//���� Ÿ��
	float lerpRatio;
	bool _isJump;
	bool _canJump;

	int slimeFireCount;


public:
	HRESULT init();
	void update();
	void render(HDC hdc) override;

private:
	void slimeAnimation();
	void slimeJump();

	void jumpUp();
	void jumpDown();
	void jumpStop();
	void targetDest();

	void slimeFire();

	float shootToTarget();



};

