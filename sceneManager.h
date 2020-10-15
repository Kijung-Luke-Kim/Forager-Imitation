#pragma once
#include "singletonBase.h"
//#include "gameNode.h"
//=============================================================
//	## sceneManager ## (���Ŵ���)
//=============================================================

//�̱����� ��ӹ��� ���̵��� static���� ����� ���⶧����
//�Ϲ�Ŭ������ ���ӳ�带 ����Ϸ��� �ϸ� ������

//���ӳ�� Ŭ���� ���漱��
class gameNode;

class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:	
	//map<string, gameNode*> _mSceneList;			//������ ��(ȭ��)���� ��Ƶ� ��
	mSceneList _mSceneList;			//������ ��(ȭ��)���� ��Ƶ� ��
	gameNode* _currentScene;		//�����

	bool ischeck;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	//���߰�
	gameNode* addScene(string sceneName, gameNode* scene);
	//������
	HRESULT loadScene(string sceneName);
	void deleteScene(string sceneName);
	bool get_ischeck() {
		return ischeck;
	}
	void set_ischeck(bool s) {
		ischeck = s;
	}
	string GetCurrentSceneName() { 
		for (auto it = _mSceneList.begin(); it != _mSceneList.end(); ++it) {
			if (it->second == _currentScene) {
				return it->first;
			}
		}
	}
	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};

