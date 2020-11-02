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

	/*���� �߰�*/
/*�������*/
	SOUNDMANAGER->addSound("�������", "Sound/BGM/FORAGER - FULL OST - COMPLETE SOUNDTRACK.mp3", true, true);

	/*ȿ����*/
	SOUNDMANAGER->addSound("Ŀ����1", "Sound/\SoundEffect/sound_sfx_slotMouseOn1.mp3");
	SOUNDMANAGER->addSound("Ŀ����2", "Sound/\SoundEffect/sound_sfx_slotMouseOn2.mp3");
	SOUNDMANAGER->addSound("�ǹ�Ŀ��", "Sound/\SoundEffect/sound_sfx_buildTabChoice.mp3");
	SOUNDMANAGER->addSound("�ǹ���ȣ�ۿ�", "Sound/\SoundEffect/sound_sfx_itemMadeWindowOpen.mp3");
	SOUNDMANAGER->addSound("Ŭ��", "Sound/\SoundEffect/sound_sfx_ok1.mp3");
	SOUNDMANAGER->addSound("�κ��丮����", "Sound/\SoundEffect/sound_sfx_inventoryShow1.mp3");
	SOUNDMANAGER->addSound("�κ��丮�ݱ�", "Sound/\SoundEffect/sound_sfx_inventoryHide.mp3");
	SOUNDMANAGER->addSound("�Ǽ���Ŭ��", "Sound/\SoundEffect/sound_sfx_buildTabSlotClick.mp3");
	SOUNDMANAGER->addSound("�Ǽ��Ǽ���", "Sound/\SoundEffect/sound_sfx_buildTabChoice.mp3");
	SOUNDMANAGER->addSound("�Ǽ�����", "Sound/\SoundEffect/sound_sfx_buildSuccess.mp3");
	SOUNDMANAGER->addSound("�Ǽ�����", "Sound/\SoundEffect/sound_sfx_buildFail.mp3");
	SOUNDMANAGER->addSound("�Ǽ����", "Sound/\SoundEffect/sound_sfx_buildTabSlotClick.mp3");
	SOUNDMANAGER->addSound("�������", "Sound/\SoundEffect/sound_sfx_itemMadeStart.mp3");
	SOUNDMANAGER->addSound("����Ϸ�", "Sound/\SoundEffect/sound_sfx_itemMadeSuccess.mp3");
	SOUNDMANAGER->addSound("������ź��", "Sound/\SoundEffect/sound_sfx_createObject.mp3");
	SOUNDMANAGER->addSound("�������浹", "Sound/\SoundEffect/sound_sfx_itemGet1.mp3");
	SOUNDMANAGER->addSound("��������", "Sound/\SoundEffect/sound_sfx_weaponSwing1.mp3");
	SOUNDMANAGER->addSound("���Ÿ�����", "Sound/\SoundEffect/sound_sfx_weaponSwing2.mp3");
	SOUNDMANAGER->addSound("����Ÿ��", "Sound/\SoundEffect/sound_sfx_berryHit1.mp3");
	SOUNDMANAGER->addSound("�����ı�", "Sound/\SoundEffect/sound_sfx_berryDestory.mp3");
	SOUNDMANAGER->addSound("����Ÿ��", "Sound/\SoundEffect/sound_sfx_treeHit1.mp3");
	SOUNDMANAGER->addSound("�����ı�", "Sound/\SoundEffect/sound_sfx_treeDestroy.mp3");
	SOUNDMANAGER->addSound("����Ÿ��", "Sound/\SoundEffect/sound_sfx_rockHit1.mp3");
	SOUNDMANAGER->addSound("�����ı�", "Sound/\SoundEffect/sound_sfx_rockDestory.mp3");
	SOUNDMANAGER->addSound("�÷��̾����1", "Sound/\SoundEffect/sound_sfx_footStep1.mp3");
	SOUNDMANAGER->addSound("�÷��̾����2", "Sound/\SoundEffect/sound_sfx_footStep2.mp3");
	SOUNDMANAGER->addSound("������", "Sound/\SoundEffect/sound_sfx_levelUp.mp3");
	SOUNDMANAGER->addSound("�ذ����Ҹ�", "Sound/\SoundEffect/skulldeadSound.mp3");
	SOUNDMANAGER->addSound("Ȳ�һ���Ҹ�", "Sound/\SoundEffect/cowDeadSound.mp3");
	SOUNDMANAGER->addSound("���ɹ���߻�Ҹ�", "Sound/\SoundEffect/wraithShootSound.mp3");
	SOUNDMANAGER->addSound("���ɹ���´¼Ҹ�", "Sound/\SoundEffect/gotHitByWraith.mp3");
	SOUNDMANAGER->addSound("�������Ҹ�", "Sound/\SoundEffect/plusBlooding.mp3");
	SOUNDMANAGER->addSound("���������Ҹ�", "Sound/\SoundEffect/muBossCry.mp3");
	SOUNDMANAGER->addSound("�Ǹ����������Ҹ�", "Sound/\SoundEffect/fireBrass.mp3");
	

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

