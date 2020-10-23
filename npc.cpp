#include "stdafx.h"
#include "npc.h"


void npc::setNpc(string p_imgKey, POINT p_ptPos, RECT* p_rcPlayer)
{
	tileIndex = 0;

	// Ű ����
	objKey = p_imgKey;
	_img = IMAGEMANAGER->findImage("David");

	// Object ���� ����
	tag = TAG::NPC;
	layer = LAYER::OBJECT;
	x = p_ptPos.x;
	y = p_ptPos.y;
	rc = RectMakeCenter(x, y, 56, 56);

	// �������ͽ� ����
	maxHp = 9999;
	currentHp = maxHp;

	// �÷��̾� �Ľ�.
	_rcPlayer = p_rcPlayer;

	// NPC ����
	_isNearPlayer = false;
	_isQuestReceive = false;
	_isQuestComplete = false;
	_canDialogue = true;

	_vDialogueNormal.push_back("���� ���� ���� ��� �׷���...");
	_vDialogueNormal.push_back("���� ���� 10���� ������ �ָ� �� �ɱ�?");
	_vDialogueQuestGive.push_back("���� ���� 10���� ������ ��");
	_vDialogueQuestComplete.push_back("�޿� ���п� ��Ҿ�.");

	// ����Ʈ ���� ������ (NPC �߰��� �ڽ� Ŭ��������)
	_QuestRewardItem = "slot_Bow";
	_QuestItem = "berryDrop";
	_questNeedItemNum = 10;

	// �ִϸ��̼� ����
	objFrameX = 0;
	objFrameY = 0;
	objMaxFrameX = 4;
	objMaxFrameY = 1;

	currentCount = 0;
	nextCount = 5;

	_currentWaitCount = 0;
	_waitCount = 400;
}

void npc::update()
{
	animation();		// �ִϸ��̼�
	checkNearPlayer();	// �÷��̾� �ֺ� üũ
	showDialogue();		// ��ǳ�� ���
	countTimer();		// �ߺ� ���� ���̾�α� Ÿ�̸� 
}

void npc::render(HDC hdc)
{
	int relX = CAMERA->GetRelativeX(rc.left - 25);
	int relY = CAMERA->GetRelativeY(rc.top - 25);
	_img->frameRender(hdc, relX, relY, objFrameX, objFrameY, CAMERA->GetZoom());

	if (_isNearPlayer && _canDialogue) {
		POINT t_ptRelMouse = CAMERA->GetMouseRelativePos(_ptMouse);
		if (abs(GetCenterX() - t_ptRelMouse.x) <= 30 && abs(GetCenterY() - t_ptRelMouse.y) <= 30)
		{
			IMAGEMANAGER->render("E", hdc, relX + 40, relY - 20, CAMERA->GetZoom());
		}
	}
}

void npc::hurt(int damage)
{
	vector<string> str;
	str.push_back("��... ����...");
	DIALOGUE->ShowDialogue(str, &rc);
}


void npc::animation()
{
	if (currentCount++ > nextCount) {
		currentCount = 0;
		if (objFrameX++ >= objMaxFrameX)
			objFrameX = 0;
	}
}

void npc::checkNearPlayer()
{
	if (abs(_rcPlayer->left - rc.left) <= 80 && abs(_rcPlayer->top - rc.top) <= 80)
		_isNearPlayer = true;
	else
		_isNearPlayer = false;
}

void npc::showDialogue()
{
	if (_isNearPlayer && _canDialogue) {

		if (INPUT->GetKeyDown('E')) {


			// ����Ʈ �ޱ� ��
			if (!_isQuestReceive) {
				DIALOGUE->ShowDialogue(_vDialogueNormal, &rc);
				_isQuestReceive = true;
			}
			// ����Ʈ ���� ��
			else if (!_isQuestComplete) {

				// ����Ʈ �ϼ�
				if (ITEMMANAGER->Item_count_Minus(_QuestItem, 5)) {
					_isQuestComplete = true;
					DIALOGUE->ShowDialogue(_vDialogueQuestComplete, &rc);

					UNITMANAGER->AddProduction(_QuestRewardItem, { rc.left - 50, rc.bottom + 50 });
				}

				// ����Ʈ ������
				else 
					DIALOGUE->ShowDialogue(_vDialogueQuestGive, &rc);
			}
			// ����Ʈ Ŭ���� ��
			else 
				DIALOGUE->ShowDialogue(_vDialogueQuestComplete, &rc);
			
			_canDialogue = false; // �ߺ� ��ȭ ����
		}
	}
}

void npc::countTimer()
{
	if (!_canDialogue) {
		if (_currentWaitCount++ > _waitCount) {
			_canDialogue = true;
			_currentWaitCount = 0;
		}
	}
}
