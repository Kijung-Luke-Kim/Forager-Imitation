#pragma once
#include "singletonBase.h"

#define UPGRADE_MAX 3

struct tagForagerHp
{
	RECT ForagerHpRc;
	string imgName;
	bool _isHp;

};

struct tagStamina
{
	RECT staminaRc;
	string imgName;
	
};
struct tagExp
{
	RECT expRc;
	string imgName;
	
};

class ForagerPlayer;
class ForagerStatManager :public singletonBase< ForagerStatManager>
{
private:
	bool superMode;


	RECT _rcForagerHpBar;				//ü�¹� ��Ʈ
	float _x, _y;					//ü�¹� ��ġ��ǥ
	float _width;					//ü�¹� ���α���
	float _height;					//ü�¹� ���α���
	float _staminaImgSizeMax;		//�ִ� ���׹̳� 
	float _staminSizeCurrent;		//���� ���׹̳� 

	tagStamina* _foragerStamina;
	ForagerPlayer* _player;

	// ����� ����
	tagExp* _foragerExp;
	int needExp[65];
	int currentExp;
	int level;
	bool levelUp;

	float _expImgSizeMax;
	
	// ��ȭ ����
	int _hammerUpgradeCount;
	int _swordUpgradeCount;
	int _bowUpgradeCount;
	int _staffUpgradeCount;
	int _flagUpgradeCount;
	float _enhancingRatio[UPGRADE_MAX];	// ��ȭ ������ ���� ����


	
	image* _levelNum[10];
	
	bool inven_open;

	
public :

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	vector<tagForagerHp*> _foragerHp;
	void ForagerPlayerinfo(ForagerPlayer* _q) {
		_player = _q;
	}
	void setinvenopen(bool open) {
		inven_open = open;
	}
	//�÷��̾� ���׹̳� ���� ī��Ʈ
	int playerStaminaCount;
	bool staminaLoss;

	//ü�¹� ��ġ �����ϱ�
	void setPos(float x, float y) { _x = x; _y = y; }

	//����ġ�� ����ȭ
	void IncreaseExp(int exp);
	void RecoverHp(int hp);
	void setRight(int num);

	int GetCurrentExp() { return currentExp; };
	int GetLevel() { return level; };
	int GetStamina() { return _staminSizeCurrent; };
	int GetStaminaMax() { return _staminaImgSizeMax; };
	float GetSpRatio() { return _staminSizeCurrent / _staminaImgSizeMax; };

	void SetLinkPlayer(ForagerPlayer* p_player) { _player = p_player; };
	void SetCurrentExp(int exp) { currentExp = exp; };
	void SetLevel(int lev) { level = lev; };
	void SetStamina(int stam) { _staminSizeCurrent = stam; };
	void SetStaminaMax(int stamBack) { _staminaImgSizeMax = stamBack; };
	bool GetSuperMode() {return superMode;	};

	// ��ȭ get set
	float GetEnhanceRatio(int p_num) { return _enhancingRatio[p_num]; };
	int GetHammerUpgradeCount() { return _hammerUpgradeCount; };
	int GetSwordUpgradeCount() { return _swordUpgradeCount; };
	int GetBowUpgradeCount() { return _bowUpgradeCount; };
	int GetFlagUpgradeCount() { return _flagUpgradeCount; };

	void SetHammerUpgradeCount(int p_num) { _hammerUpgradeCount = p_num; };
	void SetSwordUpgradeCount(int p_num) { _swordUpgradeCount = p_num; };
	void SetBowUpgradeCount(int p_num) { _bowUpgradeCount = p_num; };
	void SetFlagUpgradeCount(int p_num) { _flagUpgradeCount = p_num; };
};

