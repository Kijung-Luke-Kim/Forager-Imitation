#include "stdafx.h"
#include "startScene.h"


HRESULT startScene::init()
{
	IMAGEMANAGER->addImage("img_Logo", "Images/�̹���/img_Logo.bmp.bmp", 400, 300, true, RGB(255, 0, 255));
	//��Ʈ ��ġ �ʱ�ȭ
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 200, 400, 300);

	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rc, _ptMouse))
		{
			SCENEMANAGER->loadScene("����ȭ��");
		}
	}

}

void startScene::render()
{
	IMAGEMANAGER->findImage("img_Logo")->render(getMemDC(), WINSIZEX / 2, WINSIZEY / 2 - 200);
}
