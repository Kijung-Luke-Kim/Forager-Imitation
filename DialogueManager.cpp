#include "stdafx.h"
#include "DialogueManager.h"


void DialogueManager::update()
{
	
	for (auto iter = _vDialogues.begin(); iter != _vDialogues.end(); ) {

		// Ư�� ����� �ؽ�Ʈ�� ���� ��µǸ�
		if (iter->vDialogueText[iter->currentLine] == iter->str) {
			
			// ���� �ð� ��� ��
			if (iter->waitTime++ >= 300) {

				// ��� ��縦 �� ���¶�� �ش� ��ǳ�� ����
				if (iter->vDialogueText.size() - 1 == iter->currentLine) 
					iter = _vDialogues.erase(iter);

				// ���� ��簡 �����ִٸ� ���� ��� ��� �غ�
				else {
					iter->waitTime = 0;
					iter->str = "";
					iter->count = 0;
					iter->currentLine++;
					iter->currentLineTextIndex = 0;
					++iter;
				}
			}
			else
				++iter;
		}
		// Ư�� ����� �ؽ�Ʈ�� ��µǴ� �����̶��
		else{

			// ���� ���ݸ��� �ѱ��ھ� �߰� ���
			if (iter->count++ > TextSpeed) {
				iter->count = 0;
				iter->str = (iter->vDialogueText[iter->currentLine].substr(0, iter->currentLineTextIndex++));
			}
			++iter;
		}
	}
}

void DialogueManager::render(HDC hdc)
{
	for (int i = 0; i < _vDialogues.size(); i++) {
		POINT ptPos = { _vDialogues[i].rc->left, _vDialogues[i].rc->top - 40};
		int balloonWidth = 15 * _vDialogues[i].vDialogueText[_vDialogues[i].currentLine].size();
		IMAGEMANAGER->stretchRender("Balloon", hdc, CAMERA->GetRelativeX(ptPos.x - balloonWidth / 2), CAMERA->GetRelativeY(ptPos.y - 15), 0, 0, 15 * _vDialogues[i].vDialogueText[_vDialogues[i].currentLine].size(), 67, 100);
		TEXTMANAGER->ShowText(hdc, true, _vDialogues[i].str, ptPos,
			30, 1, RGB(255, 255, 255), true, RGB(0, 0, 0), 1);
	}
}

void DialogueManager::ShowDialogue(vector<string> p_str, RECT * p_pRC)
{
	tagDialogue t_dialogue;
	t_dialogue.count = 0;
	t_dialogue.rc = p_pRC;
	t_dialogue.currentLine = 0;
	t_dialogue.currentLineTextIndex = 0;
	t_dialogue.str = " ";
	t_dialogue.vDialogueText = p_str;
	t_dialogue.waitTime = 0;
	_vDialogues.push_back(t_dialogue);
}
