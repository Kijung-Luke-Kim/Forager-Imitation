#pragma once
#include "gameNode.h"
#include "ForagerStatManager.h"

#define PI 3.1415926f

enum STATE
{
	IDLE,
	RUN,
	ROTATE,
	HAMMERING

};

class basicmap;
class ForagerStatManager;

class ForagerPlayer :public gameNode
{
private:
	basicmap* _map;
private:
	image* _foragerIdle;
	image* _foragerRun;
	image* _foragerRotate;
	image* _foragerHammering;		//��̰� ������ �ϴ� �̹���
	image* _playerHammering;
	image* _hammer;
	image* _hammerLeft;
	int _count;
	int _index;

	//�÷��̾� ȸ�� ���� ���� ī��Ʈ 
	int _Acount;
	int _spinCount;
	float _spinSpeed;

	//�÷��̾� ���º���

	bool _isLeft;		//�����̳�?
	bool _isUp;			//�����̳�?
	bool _isMoveHorizon;//�¿�� �����̴°�?
	bool _isMoveVertical;//�¿�� �����̴°�?
	bool _isMoveRotate;	//ȸ���ϸ鼭 �����̴°�?
	bool _isRun;		//�ٰ� �ִ°�?
	bool _isGround;		//���� �پ��ִ°�?
	bool _isLookDown;	//�Ʒ��� �����ִ°�?
	bool _isLookLeft;	//������ �����ִ°�?
	bool _isLookRight;	//�������� �����ִ°�?
	bool _isJumpDown;	//�ϴ� �����ΰ�?
	bool _isJump;		//��� �����ΰ�?
	bool _isHammering;	//������ΰ�?
	bool _upDownCheck;
	STATE _state;		//ĳ���� ����
	float _x, _y;		//�÷��̾� x,y��ǥ
	float _speed;		//�÷��̾� ���ǵ� 
	float _currentSpeed;//�÷��̾� ���� ���ǵ� 

	//�÷��̾� ����
	float _playerMaxHp;	//�÷��̾� �ִ�ü��
	float _currentHp;		//�÷��̾� ����ü�� 
	


	//�÷��̾� ����
	RECT _rcForager;

	//��ġ ����
	RECT _rcHammer;

	//�÷��̾� ü�� ĭ �̹���
	image* _foragerHpBarFront[3];
	image* _foragerHpBarBack[3];

	ForagerStatManager* _foragerHp;



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
	void RotateImage(image* img);
	void Rotate(image* img, int sizeX, int sizeY, int frameX, bool left = false);

	float getPlayerMaxHp() { return _playerMaxHp; }
	float getPlayerCurrentHp(){ return _currentHp; }
	void setCurrentPlayerHp(float _hp) { _currentHp -= _hp; }
	RECT getPlayerRect() { return _rcForager; };


	void setPlayerRect(RECT pos) { _rcForager = pos; };

	void setPMLink(basicmap* map) { _map = map; };
};

