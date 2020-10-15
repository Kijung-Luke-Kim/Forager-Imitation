#include "stdafx.h"
#include "gamesetting.h"

HRESULT gamesetting::init()
{
	IMAGEMANAGER->addImage("optionWindowBack", "Images/�̹���/GUI/img_UI_OptionWindowBackground.bmp", 400, 573, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("optionWindowFrame", "Images/�̹���/GUI/img_UI_OptionWindowFrame.bmp", 400, 573, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("optionSelectBar", "Images/�̹���/GUI/img_UI_OptionSelectedBar.bmp", 380, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("optionGaugeFront", "Images/�̹���/GUI/img_UI_OptionGaugeFront.bmp", 101, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("optionGaugeBack", "Images/�̹���/GUI/img_UI_OptionGaugeBack.bmp", 101, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("optionArrowLeft", "Images/�̹���/GUI/img_UI_OptionLeft.bmp", 14, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("optionArrowRight", "Images/�̹���/GUI/img_UI_OptionRight.bmp", 14, 20, true, RGB(255, 0, 255));

	_sfxVolumn = 1.0f;
	_bgmVolumn = 1.0f;
	_lang = 0;
	_choiceOptionNum = -1;
	_camShake = false;
	_peaceMode = false;
	_cursorOn = false;

	_rcWindow = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 50, 400, 573);

	int winCenterX = _rcWindow.left + (_rcWindow.right - _rcWindow.left) / 2;
	for (int i = 0; i < 5; i++) {
		for (int x = 0; x < 2; x++) {
			_rcArrow[(i * 2) + x] = RectMakeCenter(winCenterX + x * 150, _rcWindow.top + 50 + (i * 50), 25, 25);
		}
		_rcOptions[i] = RectMakeCenter(winCenterX, _rcWindow.top + 50 + (i * 50), 380, 44);
	}

	_rcOptions[5] = RectMakeCenter(winCenterX, _rcWindow.bottom - 50, 380, 44);
	_rcSound[SFX] = RectMakeCenter(_rcOptions[3].right - 121, _rcOptions[3].bottom - 25, 101, 21);
	_rcSound[BGM] = RectMakeCenter(_rcOptions[4].right - 121, _rcOptions[4].bottom - 25, 101, 21);
	_rcSoundBack[SFX] = RectMakeCenter(_rcOptions[3].right - 121, _rcOptions[3].bottom - 25, 101, 21);
	_rcSoundBack[BGM] = RectMakeCenter(_rcOptions[4].right - 121, _rcOptions[4].bottom - 25, 101, 21);

	min = _rcSound[SFX].left;
	max = _rcSound[SFX].right;

	return S_OK;
}

void gamesetting::release()
{
}

void gamesetting::update()
{
	CheckCursorOn();
	CheckClick();
}

void gamesetting::render(HDC hdc)
{
	IMAGEMANAGER->alphaRender("inventory_background", hdc, 180);
	IMAGEMANAGER->render("inventory_Kinds", hdc, WINSIZEX / 2 - 240, 15);
	IMAGEMANAGER->render("Q", hdc, 320, 70);
	IMAGEMANAGER->render("E", hdc, 890, 70);
	IMAGEMANAGER->render("game_setting", hdc, 785, 30);


	IMAGEMANAGER->alphaRender("optionWindowBack", hdc, _rcWindow.left, _rcWindow.top, 180);
	IMAGEMANAGER->render("optionWindowFrame", hdc, _rcWindow.left, _rcWindow.top);

	for (int i = 0; i < 10; i++) {
		if(i % 2 == 0)
			IMAGEMANAGER->render("optionArrowLeft", hdc, _rcArrow[i].left, _rcArrow[i].top);
		else
			IMAGEMANAGER->render("optionArrowRight", hdc, _rcArrow[i].left, _rcArrow[i].top);
	}

	IMAGEMANAGER->render("optionGaugeBack", hdc, _rcSound[SFX].left, _rcSound[SFX].top);
	IMAGEMANAGER->stretchRender("optionGaugeFront", hdc, _rcSound[SFX].left, _rcSound[SFX].top, 0, 0, _rcSound[SFX].right - _rcSound[SFX].left, _rcSound[SFX].bottom - _rcSound[SFX].top);
	IMAGEMANAGER->render("optionGaugeBack", hdc, _rcSound[BGM].left, _rcSound[BGM].top);
	IMAGEMANAGER->stretchRender("optionGaugeFront", hdc, _rcSound[BGM].left, _rcSound[BGM].top, 0, 0, _rcSound[BGM].right - _rcSound[BGM].left, _rcSound[BGM].bottom - _rcSound[BGM].top);

	int offsetX = 85;
	int offsetY = 6;
	TEXTMANAGER->ShowText(hdc, false, "��� : ", { _rcOptions[0].left + offsetX, _rcOptions[0].top + offsetY }, 30, 1);
	TEXTMANAGER->ShowText(hdc, false, "��鸲: ", { _rcOptions[1].left + offsetX, _rcOptions[1].top + offsetY }, 30, 1);
	TEXTMANAGER->ShowText(hdc, false, "��ȭ��� : ", { _rcOptions[2].left + offsetX, _rcOptions[2].top + offsetY }, 30, 1);
	TEXTMANAGER->ShowText(hdc, false, "���� ���� : ", { _rcOptions[3].left + offsetX, _rcOptions[3].top + offsetY }, 30, 1);
	TEXTMANAGER->ShowText(hdc, false, "���� ���� : ", { _rcOptions[4].left + offsetX, _rcOptions[4].top + offsetY }, 30, 1);

	offsetX = _rcSound[BGM].left + 50;
	if(_lang == 0)
		TEXTMANAGER->ShowText(hdc, false, "�ѱ���", { offsetX, _rcOptions[0].top + offsetY }, 30, 1);

	if (_camShake)
		TEXTMANAGER->ShowText(hdc, false, "��", { offsetX, _rcOptions[1].top + offsetY }, 30, 1);
	else
		TEXTMANAGER->ShowText(hdc, false, "�ƴϿ�", { offsetX, _rcOptions[1].top + offsetY }, 30, 1);

	if (_peaceMode)
		TEXTMANAGER->ShowText(hdc, false, "��", { offsetX, _rcOptions[2].top + offsetY }, 30, 1);
	else
		TEXTMANAGER->ShowText(hdc, false, "�ƴϿ�", { offsetX, _rcOptions[2].top + offsetY }, 30, 1);

	if (SCENEMANAGER->GetCurrentSceneName() == "���� ȭ��") {
		TEXTMANAGER->ShowText(hdc, false, "���� �� �޴��� ������", { _rcOptions[5].left + (_rcOptions[5].right - _rcOptions[5].left) / 2, _rcOptions[5].top + offsetY }, 30, 1, RGB(250, 150, 0));
	}


	if(_choiceOptionNum != -1)
		IMAGEMANAGER->alphaRender("optionSelectBar", hdc, _rcOptions[_choiceOptionNum].left, _rcOptions[_choiceOptionNum].top, 75);

}

void gamesetting::CheckCursorOn()
{
	for (int i = 0; i < 6; i++) {
		if (SCENEMANAGER->GetCurrentSceneName() != "���� ȭ��") {
			if (i == 5) continue;
		}
		if (PtInRect(&_rcOptions[i], _ptMouse)) {
			_choiceOptionNum = i;

			if (!_cursorOn) {
				_cursorOn = true;
				if (SOUNDMANAGER->isPlaySound("Ŀ����1")) {
					SOUNDMANAGER->play("Ŀ����2");
				}
				else {
					SOUNDMANAGER->play("Ŀ����1");
				}
			}


			return;
		}
	}
	_cursorOn = false;
	_choiceOptionNum - 1;
}

void gamesetting::CheckClick()
{
	if (INPUT->GetKeyDown(VK_LBUTTON)) {
		if (PtInRect(&_rcOptions[5], _ptMouse)) {
			SOUNDMANAGER->play("Ŭ��");
			SAVEMANAGER->save();
			SCENEMANAGER->loadScene("���� ȭ��");
		}

		for (int i = 0; i < 10; i++) {

			if (PtInRect(&_rcArrow[i], _ptMouse)) {


				if (0 <= i && i <= 1) {
					_lang = 0;
				}
				else if (2 <= i && i <= 3) {
					_camShake = !_camShake;
				}
				else if (4 <= i && i <= 5) {
					_peaceMode = !_peaceMode;
				}
				else if (i == 6) {
					_rcSound[SFX].right -= 10;
				}
				else if (i == 7) {
					_rcSound[SFX].right += 10;
				}
				else if (i == 8) {
					_rcSound[BGM].right -= 10;
				}
				else if (i == 9) {
					_rcSound[BGM].right += 10;
				}
				VolumnSetting();
				if (_rcSound[SFX].right <= min)
					_rcSound[SFX].right = min;
				else if (_rcSound[SFX].right >= max)
					_rcSound[SFX].right = max;

				if (_rcSound[BGM].right <= min)
					_rcSound[BGM].right = min;
				else if (_rcSound[BGM].right >= max)
					_rcSound[BGM].right = max;

				SOUNDMANAGER->play("Ŭ��");
				break;
			}
		}
	}


	if (INPUT->GetKey(VK_LBUTTON)) {
		for (int i = 0; i < 2; i++) {
			if (PtInRect(&_rcSoundBack[i], _ptMouse)) {
				_rcSound[i].right = _ptMouse.x;
				VolumnSetting();
			}
		}
	}
}

void gamesetting::VolumnSetting()
{
	float t_maxWidth = _rcSoundBack[SFX].right - _rcSoundBack[SFX].left;
	float sfxVolumn = (_rcSound[SFX].right - _rcSound[SFX].left) / (float)t_maxWidth;
	float bgmVolumn = (_rcSound[BGM].right - _rcSound[BGM].left) / (float)t_maxWidth;

	SOUNDMANAGER->SetSFXVolumn(sfxVolumn);
	SOUNDMANAGER->SetBGMVolumn(bgmVolumn);

}
