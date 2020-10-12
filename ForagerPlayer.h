#pragma once
#include "ForagerStatManager.h"
#include "unit.h"
#include "earth.h"
#include "cursor.h"
#include "inventory.h"

#define PI 3.1415926f
#define PLAYER_OFFSET_Y rc.bottom + 12

class inventory;
class earth;
class cursor;

enum STATE
{
	IDLE,
	RUN,
	ROTATE,
	HAMMERING
};

enum EQUIPWEAPON {
	PICKAXE,
	BOW,
};

class ForagerStatManager;

class ForagerPlayer : public unit
{
private:

	// �̹���
	image* _foragerIdle;
	image* _foragerRun;
	image* _foragerRotate;
	image* _foragerHammering;		
	image* _playerHammering;
	image* _hammer;
	image* _hammerLeft;
	image* _bow;

	// ������ ���ǵ�
	int _hitDelayCount;
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
	bool _isBowPulling;	//Ȱ������ ���� �ִ°�?
	// ���� ����
	EQUIPWEAPON _equipWeapon;

	bool inven_open;	// �κ� ���� �̵� �Ұ���

	STATE _state;		//ĳ���� ����
	float _speed;		//�÷��̾� ���ǵ� 
	float _currentSpeed;//�÷��̾� ���� ���ǵ� 
	int Atk;
	int _playerTilePos;		// �÷��̾� Ÿ�� ��ǥ
	float _angle;		// ���콺�� �÷��̾� ������ ����
	//�÷��̾� �߰��� ����
	int _footWalkCount;
	int _footWalkEffectInterval;


	//��ġ ����
	RECT _rcHammer;

	//�÷��̾� ü�� ĭ �̹���
	image* _foragerHpBarFront[3];
	image* _foragerHpBarBack[3];

	// ����
	ForagerStatManager* _foragerHp;
	earth* _map;
	cursor* _cursor;
	inventory* _theInven;
	//enemy* _enemy;
	unit* _unit;



public: 
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc) override;


private:

	void PlayerControll();

	void MeleeWeaponClick();
	void BowClick();
	void ArrowFire();
	void bowAnimation();
	void animation();
	void playerMove();
	void playerLookingDirection();

public:
	float getPlayerMaxHp() { return maxHp; }
	float getPlayerCurrentHp(){ return currentHp; }
	void setCurrentPlayerHp(float _hp) { currentHp -= _hp; }
	void setInvenOpen(bool isOpen) { inven_open = isOpen; };
	void setPMLink(earth* map) { _map = map; };
	void setCursorLink(cursor* cursor) { _cursor = cursor; };
	void setInvenLink(inventory* inven) { _theInven = inven; };


	int FindPlayerTilePos();
	bool CanCheckMove(int index);
	void CheckPlayerTile();
	void CheckCollision();

public:
	int GetPlayerTilePos() { return _playerTilePos; };
	bool IsBow() { return _equipWeapon == EQUIPWEAPON::BOW; };
	POINT GetBowXY();

private:
	void RotateImage(image* img);
	void Rotate(image* img, int sizeX, int sizeY, int frameX, bool left = false);

};

