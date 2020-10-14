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
	SCENEMANAGER->addScene("�ε� ȭ��", new loadingScene);
	SCENEMANAGER->addScene("���� ȭ��", new startScene);
	SCENEMANAGER->addScene("���� ȭ��", new gameScene);

	/*���� �߰�*/
	/*�������*/
	SOUNDMANAGER->addSound("�������", "Sound/BGM/FORAGER - FULL OST - COMPLETE SOUNDTRACK.mp3", true, true);
	
	/*ȿ����*/
	SOUNDMANAGER->addSound("Ŀ����1", "Sound/\SoundEffect/sound_sfx_slotMouseOn1.mp3");
	SOUNDMANAGER->addSound("Ŀ����2", "Sound/\SoundEffect/sound_sfx_slotMouseOn2.mp3");
	SOUNDMANAGER->addSound("�ǹ�Ŀ��", "Sound/\SoundEffect/sound_sfx_buildTabChoice.mp3");
	SOUNDMANAGER->addSound("�ǹ���ȣ�ۿ�", "Sound/\SoundEffect/sound_sfx_inventoryShow2.mp3");
	SOUNDMANAGER->addSound("Ŭ��", "Sound/\SoundEffect/sound_sfx_ok1.mp3");

	/*�����*/
	//SCENEMANAGER->loadScene("�ε� ȭ��");
	SCENEMANAGER->loadScene("���� ȭ��");

	RECT rc;
	POINT p1, p2;

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
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//=============================================================
	
	//���ڻ� ��� ���ֱ�
	SetBkMode(getMemDC(), TRANSPARENT);

	//���Ŵ��� ����
	SCENEMANAGER->render();

	//Ÿ�ӸŴ��� ����
	TIME->render(getMemDC());
	
//=============================================================
	//������� ������ ȭ��DC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

