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
class quick_slot;

enum STATE
{
	IDLE,
	RUN,
	ROTATE,
	HAMMERING,
	DAMAGE
};

class ForagerPlayer : public unit
{
private:

	// �⺻
	STATE _state;				// ĳ���� ����
	STATE _priorState;			// ���� ĳ���� ����

	float _speed;				// �÷��̾� ���ǵ� 
	float _currentSpeed;		// �÷��̾� ���� ���ǵ� 
	int Atk;					// ���ݷ�
	int _playerTilePos;			// �÷��̾� Ÿ�� ��ǥ
	float _angle;				// ���콺�� �÷��̾� ������ ����
	float _bowPowerGauge;		// �Ŀ� ������
	int _cntBowDelay;			// ���� ȭ�� ���� ������ ��ġ
	int _bowDelay;				// ȭ�� ���� ���� ������ ��ġ
	bool _canBowFire;			// ȭ�� �߻� ����.
	tagItem _handleItem;		// �տ� ��� �ִ� ������
	quick_slot* _quick;			// ���⸦ �Ծ��� �� ������ �߰�

	//��ġ ����
	RECT _rcHammer;

	//�÷��̾� ���º���
	bool _isLeft;		//�����̳�?
	bool _isUp;			//�����̳�?
	bool _isMoveHorizon;//�¿�� �����̴°�?
	bool _isMoveVertical;//���Ϸ� �����̴°�?
	bool _isMoveRotate;	//ȸ���ϸ鼭 �����̴°�?
	bool _isRun;		//�ٰ� �ִ°�?
	bool _isHammering;	//������ΰ�?
	bool _isBowPulling;	//Ȱ������ ���� �ִ°�?
	bool _isGotDamage;  //������ �޾Ҵ°�?
	int _dir;			//����0, ������ 1.

	// �̹���
	image* _foragerIdle;
	image* _foragerRun;
	image* _foragerRotate;
	image* _foragerAttacking;		
	image* _playerHammering;
	image* _handleWeapon;
	//image* _hammerLeft;
	image* _bow;
	image* _foragerHpBarFront[3];
	image* _foragerHpBarBack[3];
	
	float _spinAngle;	// �÷��̾� ������ ����;

	// �ִϸ��̼� ���ǵ�
	int _hitDelayCount;
	int _count;
	int _index;

	//�÷��̾� �߰��� ����
	int _footWalkCount;
	int _footWalkEffectInterval;

	//�÷��̾� ȸ�� ���� ���� ī��Ʈ 
	int _Acount;
	int _spinCount;
	float _spinSpeed;

	//���� ȸ�� ���� ���� ī��Ʈ
	float _pickaxeNormalSpin;
	float _weaponSpin;
	bool _weaponBack;
	bool _canHit;
	// ��Ÿ
	bool inven_open;		// �κ� ���� �̵� �Ұ���
	float _balloonRatio;	// ������ ������ ���϶� ��ǳ���� ������
	int _cntBalloon;		// ����� �� ������ ��ǳ�� ī��Ʈ
	int _cntBalloonMax;		// ��ǳ�� ��� ī��Ʈ

	int _cntWarning;

	bool _startBalloon;		// ���� ��ǳ��
	int _cntDelayStartBalloon;
	int _delayStartBalloon;

	int _powerOverwhelmingTime;

	// ����
	earth* _map;
	cursor* _cursor;
	inventory* _theInven;
	unit* _unit;

public: 
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc) override;

private:
	void renderPlayer(HDC hdc);
	void PlayerControll();
	
	void MeleeWeaponClick();
	void CalcBowDelay();
	void BowClick();
	void ArrowFire();
	void bowAnimation();
	void animation();
	void playerMove();
	void playerLookingDirection();
	void weaponCheck();
	void hungryBalloon();
	void BlinkProcess();
public:
	float getPlayerMaxHp() { return maxHp; }
	float getPlayerCurrentHp(){ return currentHp; }
	void setCurrentPlayerHp(float _hp) { currentHp -= _hp; }
	void setInvenOpen(bool isOpen) { inven_open = isOpen; };
	void setPMLink(earth* map) { _map = map; };
	void setCursorLink(cursor* cursor) { _cursor = cursor; };
	void setInvenLink(inventory* inven) { _theInven = inven; };
	void setBalloon(bool p_flag) { _startBalloon = p_flag; };


	void getquick_slotInfo(quick_slot* _q) {
		_quick = _q;
	}

	int FindPlayerTilePos();
	bool CanCheckMove(int index);
	void CheckPlayerTile();
	void CheckCollision();
	

public:
	int GetPlayerTilePos() { return _playerTilePos; };
	bool IsBow() { return  _handleItem.weaponType == WeaponType::BOW; };
	POINT GetBowXY();
	void hurt(int damage, bool onlyEffect = false) override;
	void SetIsMoveRotate() { _isMoveRotate = false; };
	void Init_PowerOverwhelmingTime() {
		_powerOverwhelmingTime = 0;
	}
private:
	void RotateImage(image* img);
	void Rotate(image* img, int sizeX, int sizeY, int frameX, bool left = false);
};

