#include "stdafx.h"
#include "startScene.h"


HRESULT startScene::init()
{
	//���̺� ��ư ĭ ��Ʈ
	saveRc = RectMake(100, 100, 100, 100);

	// ���콺 �����
	ShowCursor(false);

	// �̹��� ��� (���� �ε� ������ �Ű��� �͵�)
	IMAGEMANAGER->addImage("Logo", "Images/�̹���/img_Logo.bmp", 300, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BtnCredit", "Images/�̹���/GUI/img_UI_BtnCredit.bmp", 213, 104, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BtnExit", "Images/�̹���/GUI/img_UI_BtnExit.bmp", 213, 104, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BtnSetting", "Images/�̹���/GUI/img_UI_BtnSetting.bmp", 213, 104, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GameSlot", "Images/�̹���/GUI/img_UI_GameSlotBoundary.bmp", 227, 227, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GameSlotInner", "Images/�̹���/GUI/img_UI_GameSlotInner.bmp", 227, 227, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TitleBG", "Images/�̹���/img_Background.bmp", 1960, 1280, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TitleCursor", "Images/�̹���/GUI/Ŀ��.bmp", 15, 15, true, RGB(255, 0, 255));

	
	// Ŀ�� ������ �̹��� ����
	for (int i = 0; i < BUTTON_MAX / 2; i++) {
		RECT slotRC = RectMakeCenter(WINSIZEX / 2 - 400 + i * 400, 360, 227, 227);
		RECT btnRC = RectMakeCenter(WINSIZEX / 2 - 300 + i * 300, WINSIZEY - 120, 213, 104);

		_button[i + BUTTON_MAX / 2].init(slotRC, 18, 4, "GameSlot", "GameSlotInner", 100);
		if (i == 0) _button[i].init(btnRC, 12, 3, "BtnSetting");
		else if (i == 1) _button[i].init(btnRC, 12, 3, "BtnCredit");
		else if (i == 2) _button[i].init(btnRC, 12, 3, "BtnExit");
	}

	// Ÿ���� �ڽ� ����
	_targetingBox = new targetingBox;
	_targetingBox->init();
	
	gameSlotCheck = 0;

	return S_OK;
}

void startScene::release()
{
	// Ÿ���� �ڽ� ����
	SAFE_DELETE(_targetingBox);
}

void startScene::update()
{
	// ���콺 ȣ�� üũ
	CheckCursorOnButton();
	
	// ���콺 Ŭ�� üũ
	CheckButtonClick();


	// �߰��� ����Ʈ �׽�Ʈ��
	if (testWalkEffectCount++ >= testWalkEffectInterval) {
		testWalkEffectCount = 0;
		EFFECTMANAGER->ShowEffectAlphaSize("Walk1", _ptMouse, 0, 0.25f, 0, 150);
	}

	EFFECTMANAGER->update();

	////if (SAVEMANAGER->slotName == "gaem1")
	//{
	//	if (INPUT->GetKeyDown(VK_F1))
	//	{
	//		_saveManager->getSaveTile();
	//	}
	//}

	////if (SAVEMANAGER->slotName == "gaem1")
	//{
	//	if (INPUT->GetKeyDown(VK_F2))
	//	{
	//		_saveManager->getLoadTile();
	//	}
	//}

	
}

void startScene::render()
{

	// �Ķ� ��� ����
	IMAGEMANAGER->findImage("TitleBG")->render(getMemDC(), -300, -300);

	// �ΰ� ����
	IMAGEMANAGER->findImage("Logo")->render(getMemDC(), WINSIZEX / 2 - 150, 0);


	// ���ӽ��� ����
	for (int i = 0; i < BUTTON_MAX; i++) {
		_button[i].render(getMemDC());
	}

	for (int i = 3; i < BUTTON_MAX; i++) {
		int centerX = _button[i].GetRect().left + (_button[i].GetRect().right - _button[i].GetRect().left) / 2;
		int centerY = _button[i].GetRect().top + (_button[i].GetRect().bottom- _button[i].GetRect().top) / 2;
		POINT ptPos = { centerX , centerY - 15 };
		TEXTMANAGER->ShowText(getMemDC(), "������", ptPos, 35, 1, RGB(255,255,255), true, RGB(0,0,0));
	}


	EFFECTMANAGER->render(getMemDC());

	// Ÿ���� �ڽ� ����
	_targetingBox->render(getMemDC());

	// Ŀ�� ����
	IMAGEMANAGER->findImage("TitleCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);


}

void startScene::CheckCursorOnButton()
{
	bool _cursor = false;
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		_button[i].update();

		// ��ư ���� Ŀ��
		if (PtInRect(&_button[i].GetRect(), _ptMouse)) {
			_targetingBox->SetTarget(_button[i].GetRect());
			_button[i].CursorIn();
			_cursor = true;
		}
		else
			_button[i].CursorOut();
	}
	if (!_cursor)
		_targetingBox->CursorOut();

	_targetingBox->update();

}




void startScene::CheckButtonClick()
{
	if (INPUT->GetKeyDown(VK_RBUTTON)) {
		EFFECTMANAGER->ShowEffectFrame("DigSmoke", _ptMouse);
	}

	// ��ư Ŭ��
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < BUTTON_MAX; i++)
		{
			if (PtInRect(&_button[i].GetRect(), _ptMouse))
			{
				switch (i) {
				case BTN::SETTING:	SCENEMANAGER->loadScene("����ȭ��"); break;	// ȯ�漳�� â
				case BTN::CREDIT:	SCENEMANAGER->loadScene("����ȭ��"); break;	// ũ���� â
				case BTN::EXIT:		SCENEMANAGER->loadScene("����ȭ��"); break;	// ���� ����

				case BTN::SLOT1:	
					SCENEMANAGER->loadScene("����ȭ��"); 
					SAVEMANAGER->slotName = "game1.map";
					break;	// ���� ���� 1
				
				case BTN::SLOT2:	SCENEMANAGER->loadScene("����ȭ��"); 
					SAVEMANAGER->slotName = "game2.map";
					break;	// ���� ���� 2
				case BTN::SLOT3:	SCENEMANAGER->loadScene("����ȭ��");
					SAVEMANAGER->slotName = "game3.map";
					break;	// ���� ���� 3
				}
			}
		}
	}
}
