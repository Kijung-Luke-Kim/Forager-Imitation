#pragma once
#include "earth.h"

#define MAX_X MAPTILEX
#define MAX_Y MAPTILEY

//������
enum NODESTATE
{
	NODE_START,
	NODE_END,
	NODE_WALL,
	NODE_EMPTY
};

//��� Ŭ����
class node
{
public:
	RECT rc;				//��Ʈ
	int idx, idy;			//�ε���
	int F, G, H;			//F = G + H, G => ���� to ����, H = ���� to ����
	node* parentNode;		//�θ� ����ų ���(���� ���)
	NODESTATE nodeState;	//������ (����, ����, ��, ����)

	//��� ������
	node() {}
	//��� ������ (������ �����ε�)
	node(int _idx, int _idy)
	{
		idx = _idx;
		idy = _idy;
		F = G = H = 0;
		nodeState = NODE_EMPTY;
		parentNode = NULL;
	}
};


class Astar
{
private:
	vector<tile> _vTiles;
private:
	node* _totalNode[MAPTILEX][MAPTILEY];		//��ü��� 25��(������ ����)
	node* _startNode;					//���۳��
	node* _endNode;						//������
	node* _curNode;						//������

	vector<node*> _openList;			//���¸���Ʈ (ž���� ������ ��Ƶ� ����)
	vector<node*> _closeList;			//���� ã�� ������ ��Ƶ� ����
	//vector<node*> _finalList;			//Ŭ�����Ʈ�� ����ִ� ������ ���������Ѽ� ��Ƶ� ����
	vector<int> _finalList;			//Ŭ�����Ʈ�� ����ִ� ������ ���������Ѽ� ��Ƶ� ����

public:
	void init(vector<tile> vTile);

	/*�߿��Լ�*/
	//��ã�� �Լ�
	vector<int> pathFinding(vector<tile> vTile, int startidx, int endidx, bool checkwall=true, bool checkdiagonal=true);
	//���¸���Ʈ �߰�
	void addOpenList(int idx, int idy);
	//���¸���Ʈ ����
	void delOpenList(int index);
};

