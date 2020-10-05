#pragma once
#include "ForagerStatManager.h"
#include "unit.h"

#define PI 3.1415926f

enum STATE
{
	IDLE,
	RUN,
	ROTATE,
	HAMMERING

};
class ForagerStatManager;

class ForagerPlayer :public unit
{
private:
	//basicmap* _map;
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
	bool _isMoveVertical;//���Ϸ� �����̴°�?
	bool _isMoveRotate;	//ȸ���ϸ鼭 �����̴°�?
	bool _isRun;		//�ٰ� �ִ°�?
	bool _isHammering;	//������ΰ�?
	STATE _state;		//ĳ���� ����
	float _speed;		//�÷��̾� ���ǵ� 
	float _currentSpeed;//�÷��̾� ���� ���ǵ� 
	

	//�÷��̾� �߰��� ����
	int _footWalkCount;
	int _footWalkEffectInterval;

	//�÷��̾� ����
	RECT _rcForager;

	//��ġ ����
	RECT _rcHammer;

	//�÷��̾� ü�� ĭ �̹���
	image* _foragerHpBarFront[3];
	image* _foragerHpBarBack[3];

	ForagerStatManager* _foragerHp;


	bool inven_open;
public: 
	HRESULT init();
	void release();
	void update() override;
	void render(HDC hdc) override;

	//�÷��̾� �ִϸ��̼�
	void animation();
	void PlayerControll();
	void playerMove();
	void playerLookingDirection();
	void RotateImage(image* img);
	void Rotate(image* img, int sizeX, int sizeY, int frameX, bool left = false);

	float getPlayerMaxHp() { return hp; }
	float getPlayerCurrentHp(){ return currentHp; }
	void setCurrentPlayerHp(float _hp) { currentHp -= _hp; }
	RECT getPlayerRect() { return _rcForager; };

	
	void setPlayerRect(RECT pos) { _rcForager = pos; };
	void setInvenOpen(bool isOpen) { inven_open = isOpen; };
//	void setPMLink(basicmap* map) { _map = map; };
};

