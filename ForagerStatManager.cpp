#include "stdafx.h"
#include "ForagerStatManager.h"
#include "ForagerPlayer.h"

HRESULT ForagerStatManager::init()
{
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

	

	IMAGEMANAGER->addImage("��Ʈ���ü��", "Images/�̹���/GUI/��Ʈ���ü��.bmp", 34, 30,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("��Ʈ���ü��(��)", "Images/�̹���/GUI/��Ʈ���ü��(��).bmp", 34, 30, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���׹̳�", "Images/�̹���/GUI/img_UI_StaminaGaugeBar.bmp", 63, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���׹̳�(��)", "Images/�̹���/GUI/img_UI_StaminaGaugeBoard.bmp", 74, 26, true, RGB(255, 0, 255));

	_staminaImgSizeMax = IMAGEMANAGER->findImage("���׹̳�")->getWidth();
	playerStaminaCount = 0;
	staminaLoss = false;
	

	return S_OK;
}

void ForagerStatManager::release()
{
}

void ForagerStatManager::update()
{
	//�÷��̾��� ���׹̳��� �� ��������, �ٽ� ��������, �Ѵ�. 
	if (IMAGEMANAGER->findImage("���׹̳�")->getWidth() < 0)
	{
		IMAGEMANAGER->findImage("���׹̳�")->settingWidth(_staminaImgSizeMax);
		for (int i = _foragerHp.size()-1; i >= 0; i--)
		{
			if (!_foragerHp[i]->_isHp)continue;
			_foragerHp[i]->_isHp = false;
			break;
		}
	}
	



}

void ForagerStatManager::render()
{
	for (int i = 0; i < _foragerHp.size(); i++)
	{
		if (_foragerHp[i]->_isHp)
		{
			IMAGEMANAGER->render("��Ʈ���ü��", getMemDC(), _foragerHp[i]->ForagerHpRc.left, _foragerHp[i]->ForagerHpRc.top);
		}
		else
		{
			IMAGEMANAGER->render("��Ʈ���ü��(��)", getMemDC(), _foragerHp[i]->ForagerHpRc.left, _foragerHp[i]->ForagerHpRc.top);
		}
		
		
	}

	IMAGEMANAGER->render("���׹̳�(��)", getMemDC(), _foragerStamina->staminaRc.left, _foragerStamina->staminaRc.top);
	IMAGEMANAGER->render("���׹̳�", getMemDC(), _foragerStamina->staminaRc.left+6, _foragerStamina->staminaRc.top+4);

	
	

}

void ForagerStatManager::setGauge(float maxHp, float currentHp)
{
	
}
