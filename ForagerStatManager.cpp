#include "stdafx.h"
#include "ForagerStatManager.h"
#include "ForagerPlayer.h"

HRESULT ForagerStatManager::init()
{
	inven_open = false;
	superMode = false;			//=================����=======================
	for (int i = 0; i < 3; i++)		//��Ʈ��� ü�� 3�� 
	{
		tagForagerHp* _hp = new tagForagerHp;

		_hp->imgName = "��Ʈ���ü��";
		_hp->ForagerHpRc = RectMake(10 + i*40,10,34,30);
		_hp->_isHp = true;
		_foragerHp.push_back(_hp);
	}

	_foragerStamina = new tagStamina;
	_foragerStamina->staminaRc = RectMake(10, 50, 74, 26);

	_foragerExp = new tagExp;
	_foragerExp->expRc = RectMakeCenter(WINSIZEX/ 2, 30, 800, 30);
	_foragerExp->expRc.right = 0;
	levelUp = false;
	
	needExp[0] = 20;

	for (int i = 1; i < 65; i++) {
		needExp[i] = (float)needExp[i - 1] * 2.5f;
	}

	currentExp = 0;
	level = 0;

	IMAGEMANAGER->addImage("��Ʈ���ü��", "Images/�̹���/GUI/��Ʈ���ü��.bmp", 34, 30,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("��Ʈ���ü��(��)", "Images/�̹���/GUI/��Ʈ���ü��(��).bmp", 34, 30, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���׹̳�", "Images/�̹���/GUI/img_UI_StaminaGaugeBar.bmp", 63, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���׹̳�(��)", "Images/�̹���/GUI/img_UI_StaminaGaugeBoard.bmp", 74, 26, true, RGB(255, 0, 255));

	//�÷��̾� ����ġ �� �̹���
	IMAGEMANAGER->addImage("expBar", "Images/�̹���/GUI/img_UI_ExpGaugeBar.bmp", 792, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("expBarBack", "Images/�̹���/GUI/img_UI_ExpGaugeBoard.bmp", 800, 30, true, RGB(255, 0, 255));

	_levelNum[0]=IMAGEMANAGER->addImage("0", "Images/�̹���/GUI/0.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[1]=IMAGEMANAGER->addImage("1", "Images/�̹���/GUI/1.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[2]=IMAGEMANAGER->addImage("2", "Images/�̹���/GUI/2.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[3]=IMAGEMANAGER->addImage("3", "Images/�̹���/GUI/3.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[4]=IMAGEMANAGER->addImage("4", "Images/�̹���/GUI/4.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[5]=IMAGEMANAGER->addImage("5", "Images/�̹���/GUI/5.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[6]=IMAGEMANAGER->addImage("6", "Images/�̹���/GUI/6.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[7]=IMAGEMANAGER->addImage("7", "Images/�̹���/GUI/7.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[8]=IMAGEMANAGER->addImage("8", "Images/�̹���/GUI/8.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[9]=IMAGEMANAGER->addImage("9", "Images/�̹���/GUI/9.bmp", 15, 19, true, RGB(255, 0, 255));

	_staminSizeCurrent = _staminaImgSizeMax = IMAGEMANAGER->findImage("���׹̳�")->getWidth();
	

	_expImgSizeMax = IMAGEMANAGER->findImage("expBar")->getWidth();
	playerStaminaCount = 0;
	staminaLoss = false;


	// ��ȭ ��ġ �ʱ�ȭ
	_hammerUpgradeCount = 1;
	_swordUpgradeCount = 0;
	_bowUpgradeCount = 0;
	_flagUpgradeCount = 0;

	// ��ȭ�� ���� ������ ������
	_enhancingRatio[0] = 1.0f;
	_enhancingRatio[1] = 1.5f;
	_enhancingRatio[2] = 2.0f;


	return S_OK;
}

void ForagerStatManager::release()
{
}

void ForagerStatManager::update()
{
	//�÷��̾��� ���׹̳��� �� ��������, �ٽ� ��������, �Ѵ�. 
	//if (IMAGEMANAGER->findImage("���׹̳�")->getWidth() < 0)
	//{
	//	IMAGEMANAGER->findImage("���׹̳�")->settingWidth(_staminaImgSizeMax);
	//	for (int i = _foragerHp.size()-1; i >= 0; i--)
	//	{
	//		if (!_foragerHp[i]->_isHp)continue;
	//		_foragerHp[i]->_isHp = false;
	//		break;
	//	}
	//}
	if (INPUT->GetKeyDown(VK_F4)) {
		superMode = !superMode;//=================����=======================
	}
	
	if (levelUp == true || _staminSizeCurrent < 0)
	{
		if (levelUp)
		{
			EFFECTMANAGER->ShowEffectFrame("levelUp", { _player->GetCenterX(), _player->GetCenterY() }, 5, true);
			_staminaImgSizeMax += 20;
			levelUp = false;
			_player->Init_PowerOverwhelmingTime();
		}
		else
		{
			if (!superMode) {			//=================����=======================
				int i = _foragerHp.size() - 1;
				for (; i >= 0; i--)
				{

					if (!_foragerHp[i]->_isHp)continue;
					_foragerHp[i]->_isHp = false;
					break;
				}

				if (i == 0) {
					_foragerHp.clear();
					SCENEMANAGER->loadScene("���� ȭ��");
				}
			}

		}
		_staminSizeCurrent = _staminaImgSizeMax;
	}
	
}

void ForagerStatManager::render(HDC hdc)
{
	for (int i = 0; i < _foragerHp.size(); i++)
	{
		if (_foragerHp[i]->_isHp)
			IMAGEMANAGER->render("��Ʈ���ü��", hdc, _foragerHp[i]->ForagerHpRc.left, _foragerHp[i]->ForagerHpRc.top);
		else
			IMAGEMANAGER->render("��Ʈ���ü��(��)", hdc, _foragerHp[i]->ForagerHpRc.left, _foragerHp[i]->ForagerHpRc.top);
	}

	IMAGEMANAGER->stretchRender("���׹̳�(��)", hdc, _foragerStamina->staminaRc.left, _foragerStamina->staminaRc.top,0,0, 
		_staminaImgSizeMax, _foragerStamina->staminaRc.bottom - _foragerStamina->staminaRc.top);

	IMAGEMANAGER->stretchRender("���׹̳�", hdc, _foragerStamina->staminaRc.left+2, _foragerStamina->staminaRc.top+2, 0, 0,
		_staminSizeCurrent -4  , (_foragerStamina->staminaRc.bottom - _foragerStamina->staminaRc.top)-4 );

	if (!inven_open) {
		IMAGEMANAGER->render("expBarBack", hdc, _foragerExp->expRc.left, _foragerExp->expRc.top);

		if (level > 0)
			IMAGEMANAGER->render("expBar", hdc, _foragerExp->expRc.left + 4, _foragerExp->expRc.top + 3, 0, 0,
				_expImgSizeMax * (currentExp - (float)(needExp[level - 1])) / (needExp[level] - (float)(needExp[level - 1])), 22);
		else
			IMAGEMANAGER->render("expBar", hdc, _foragerExp->expRc.left + 4, _foragerExp->expRc.top + 3, 0, 0,
				_expImgSizeMax * (float)(currentExp / (float)needExp[level]), 22);

		string str = "Lv " + to_string(level + 1);
		str.append(" (  " + to_string(currentExp));
		str.append("  /  " + to_string(needExp[level]));
		str.append(" )  ");
		TEXTMANAGER->ShowText(hdc, false, str, { WINSIZEX / 2 , _foragerExp->expRc.top + 3 }, 22, 1, RGB(0,255,0), true, RGB(0,50,0), 2);
	}

	
}

void ForagerStatManager::IncreaseExp(int exp)
{
	if (levelUp == false)
	{
		currentExp += exp;
		if (currentExp > needExp[level])
		{
			level++;
			levelUp = true;
			SOUNDMANAGER->play("������");
		}
	}

}

void ForagerStatManager::setRight(int num)
{

	if (_staminSizeCurrent >= _staminaImgSizeMax-5) {
		_staminSizeCurrent = _staminaImgSizeMax-5;

	}
	_staminSizeCurrent -= num;
}


