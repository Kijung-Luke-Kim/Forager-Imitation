#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	
	/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
	/*�̰����� ������ ������ �߰��ϰ� ������� �����Ѵ�*/

	/*���߰�*/
	SCENEMANAGER->addScene("INI�׽�Ʈ", new iniTestScene);
	//SCENEMANAGER->addScene("����", new soundTestScene);
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);
	SCENEMANAGER->addScene("����ȭ��", new basicmap);
	SCENEMANAGER->addScene("��������ȭ��", new ForagerPlayer);
	SCENEMANAGER->addScene("����ȭ��", new startScene);
	SCENEMANAGER->addScene("�÷��̾��׽�Ʈȭ��", new playerTestScene);
	SCENEMANAGER->addScene("�κ��丮", new inventory);

	/*�����*/
	SCENEMANAGER->loadScene("����ȭ��");

	return S_OK;
}

//=============================================================
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
}

//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	
	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();

	//����Ŵ��� ������Ʈ (�̰� ������ ����Ŵ��� ����� �������� �ʴ´�!!!)
	SOUNDMANAGER->update();
}

//=============================================================
//	## ���� ## render()
//=============================================================
void mainGame::render()
{
	//��� �� ��Ʈ�� (�̰��� ������ �׳� �α�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================
	
	//���ڻ� ��� ���ֱ�
	SetBkMode(getMemDC(), TRANSPARENT);

	//���Ŵ��� ����
	SCENEMANAGER->render();

	//Ÿ�ӸŴ��� ����
	TIME->render(getMemDC());
	
//=============================================================
	//������� ������ ȭ��DC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(getHDC());
}

