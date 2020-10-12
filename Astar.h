#pragma once
#include "gameNode.h"
#include "earth.h"

#define MAX_X MAPTILEX
#define MAX_Y MAPTILEY


class earth;
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


class Astar : public gameNode
{
private:
	vector<tile> _vTiles;
private:
	node* _totalNode[MAX_X][MAX_Y];		//��ü��� 25��(������ ����)
	node* _startNode;					//���۳��
	node* _endNode;						//������
	node* _curNode;						//������

	vector<node*> _openList;			//���¸���Ʈ (ž���� ������ ��Ƶ� ����)
	vector<node*> _closeList;			//���� ã�� ������ ��Ƶ� ����
	vector<node*> _finalList;			//Ŭ�����Ʈ�� ����ִ� ������ ���������Ѽ� ��Ƶ� ����

	int _count;							//���۳��, �����带 �ѹ����� �����ϱ� ���� ����
	bool _isFind;						//�� ã�ҳ�?

public:
	HRESULT init(vector<tile> vTile);
	void release();
	void update();
	void render();

	/*�߿��Լ�*/
	//��ã�� �Լ�
	void pathFinding();
	void pathFinding(int startidx, int endidx, bool checkwall, bool checkdiagonal = true);
	//���¸���Ʈ �߰�
	void addOpenList(int idx, int idy);
	//���¸���Ʈ ����
	void delOpenList(int index);

	//���Ǹ� ���� �Լ�
	void setNodeColor(node* node, COLORREF color);

};

