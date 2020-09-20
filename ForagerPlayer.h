#pragma once
#include "gameNode.h"

#define PI 3.1415926f

enum STATE
{
	IDLE,
	RUN

};

class ForagerPlayer :public gameNode
{

private:
	image* _foragerIdle;
	image* _foragerRun;

	int _count;
	int _index;

	//�÷��̾� ȸ�� ���� ���� ī��Ʈ 
	int _Acount;
	int _spinCount;


	//�÷��̾� ���°�

	bool _isLeft;		//�����̳�?
	bool _isUp;			//�����̳�?
	bool _isMoveHorizon;//�¿�� �����̴°�?
	bool _isMoveVertical;//�¿�� �����̴°�?
	bool _isRun;		//�ٰ� �ִ°�?
	bool _isGround;		//���� �پ��ִ°�?
	bool _isLookDown;	//�Ʒ��� �����ִ°�?
	bool _isLookLeft;	//������ �����ִ°�?
	bool _isLookRight;	//�������� �����ִ°�?
	bool _isJumpDown;	//�ϴ� �����ΰ�?
	bool _isJump;		//��� �����ΰ�?
	bool _isHang;		//�Ŵ޷ȴ°�?
	STATE _state;		//ĳ���� ����
	float _x, _y;		//�÷��̾� x,y��ǥ
	float _speed;		//�÷��̾� ���ǵ� 
	float _currentSpeed;//�÷��̾� ���� ���ǵ� 
	


	//�÷��̾� ����

	RECT _rcForager;




public: 
	HRESULT init();
	void release();
	void update();
	void render();

	//�÷��̾� �ִϸ��̼�
	void animation();
	void PlayerControll();
	void playerMove();
	void playerLookingDirection();
	//void RotateImage(image* img);
	//void Rotate(image* img, int sizeX, int sizeY, int frameX);
	


};

