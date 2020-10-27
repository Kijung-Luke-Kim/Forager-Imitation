#include "stdafx.h"
#include "Astar.h"

void Astar::init(vector<tile> vTile, bool checkwall)
{
	//��� �ʱ�ȭ
	_startNode = NULL;
	_endNode = NULL;
	_curNode = NULL;
	_vTiles = vTile;
	idleCount = 0;
	//��ü��� �ʱ�ȭ
	for (int y = 0; y < MAPTILEY; y++)
	{
		for (int x = 0; x < MAPTILEX; x++)
		{
			//���ο� ���� ��Ʈ��ġ ����
			SAFE_DELETE(_totalNode[x][y]);
		}
	}
	for (int y = 0; y < MAPTILEY; y++)
	{
		for (int x = 0; x < MAPTILEX; x++)
		{
			//���ο� ���� ��Ʈ��ġ ����
			_totalNode[x][y] = new node(x, y);
			_totalNode[x][y]->rc = _vTiles[y*MAPTILEY + x].rc;
			if (checkwall) {
				if (_vTiles[y*MAPTILEY + x].canPass || _vTiles[y*MAPTILEY + x].terrKey == "watertile") {
					_totalNode[x][y]->nodeState = NODE_WALL;
				}
			}
		}
	}
	
	//����ŸƮ��
	_openList.clear();
	_closeList.clear();
	_finalList.clear();
}

vector<int> Astar::pathFinding(vector<tile> vTile, int startidx, int endidx, bool checkwall, bool checkdiagonal)
{

	this->init(vTile, checkwall);
	earth _map;
	_startNode = _totalNode[_map.GetTileY(startidx)][_map.GetTileX(startidx)];
	_endNode = _totalNode[_map.GetTileY(endidx)][_map.GetTileX(endidx)];

	//��ã�⸦ �غ���
	//�˻��� �Ϸ��� ������ ���¸���Ʈ�� ��´�
	//F�� H�� ���� ���� ���� ã�Ƽ� �׳��� ������� �����Ѵ�
	//���¸���Ʈ���� ������� �����ϰ�
	//������� Ŭ�����Ʈ�� ��Ƶд�
	//���� �� ã�Ҵٸ� Ŭ�����Ʈ ���������� ���̳� ����Ʈ�� �ű��

	//1. ���۳�尡 �־�� ����� �����ϴ�
	//���۳�带 ���¸���Ʈ�� �߰��� ����� �Ѵ�
	_openList.push_back(_startNode);

	//2. ���¸���Ʈ�ȿ� ��� �ִ� ���͸� �˻��ؼ�
	//�����忡 �����Ҷ����� ���� ����
	while (_openList.size() > 0)
	{
		_curNode = _openList[0];
		node* _prevNode = _curNode;

		//���¸���Ʈ�� F�� ���� �۰ų� F�� ���ٸ�
		//H�� ���� �� ������� �ϰ�
		//�����带 ���¸���Ʈ���� Ŭ���� ����Ʈ�� �ű��
		//�񱳸� �Ϸ��� �ϸ� �ּ� ���۳�忡�� �ֺ��� Ž���� ����
		//��ã�Ⱑ ���۵ȴ�

		for (int i = 1; i < _openList.size(); i++)
		{
			if (_openList[i]->F <= _curNode->F && _openList[i]->H < _curNode->H)
			{
				_curNode = _openList[i];
			}
		}

		//Ŭ���� ����Ʈ�� �־�д�
		for (int i = 0; i < _openList.size(); i++)
		{
			if (_curNode == _openList[i])
			{
				this->delOpenList(i);
				_closeList.push_back(_curNode);
			}
		}
		
		//�����尡 �������� ����? (���������� ��ΰ� ����)
		if (_curNode == _prevNode) {
			idleCount++;
			if (idleCount > 10) {
				return _finalList;
			}
		}
		//�����尡 ������ ���� ����? (��ã�Ҵ�)
		if (_curNode == _endNode)
		{
			node* endNode = _endNode;
			vector<node*> tempNode;
			//������ ���κ��� ���۳����� �θ��带 ���Ϳ� ��´�
			while (endNode != _startNode)
			{
				tempNode.push_back(endNode);
				endNode = endNode->parentNode;
			}

			for (int i = tempNode.size() - 1; i > 0; i--)
			{
				int tileIndex = tempNode[i]->idy*MAPTILEX + tempNode[i]->idx;
				_finalList.push_back(tileIndex);
			}

			//�����ϰ� ���� ���´�
			return _finalList;
		}

		//�����¿� (������ ������� - ��¥�� �ֺ� 4���� ��带 ��� ���¸���Ʈ�� ��Ƽ� �˻��� ������)
		addOpenList(_curNode->idx, _curNode->idy - 1);	//��
		addOpenList(_curNode->idx, _curNode->idy + 1);	//��
		addOpenList(_curNode->idx - 1, _curNode->idy);	//��
		addOpenList(_curNode->idx + 1, _curNode->idy);	//��

		if (checkdiagonal) {
			//���, �»�, ����, ����
			addOpenList(_curNode->idx + 1, _curNode->idy - 1);	//���
			addOpenList(_curNode->idx - 1, _curNode->idy - 1);	//�»�
			addOpenList(_curNode->idx + 1, _curNode->idy + 1);	//����
			addOpenList(_curNode->idx - 1, _curNode->idy + 1);	//����
		}
	}
}

void Astar::addOpenList(int idx, int idy)
{
	//����ó�� �ε��� �����ȿ��� �߰��� �� �־�� �Ѵ�
	if (idx < 0 || idx >= MAX_X || idy < 0 || idy >= MAX_Y) return;

	//���� ���¸���Ʈ�� ���� �� ����
	if (_totalNode[idx][idy]->nodeState == NODE_WALL) return;

	//Ŭ�����Ʈ(�����±�)�� �ִٸ� ���¸���Ʈ�� ������ �ȵȴ�
	for (int i = 0; i < _closeList.size(); i++)
	{
		if (_totalNode[idx][idy] == _closeList[i]) return;
	}

	//������� ������ ������ ������ ���� ���¸���Ʈ�� �߰��� ����
	//�������� 4���� ��带 �̿������ �ϰ� ����10, �밢�� 14����� �߰��Ѵ�
	node* neighborNode = _totalNode[idx][idy];
	int moveCost = _curNode->G + ((_curNode->idx - idx == 0 || _curNode->idy - idy == 0) ? 10 : 14);

	//���¸���Ʈ�ȿ� �̿���尡 ������ �ȵȴ�
	for (int i = 0; i < _openList.size(); i++)
	{
		if (_openList[i] == neighborNode) return;
	}

	//���������� ���¸���Ʈ���� ���°��
	//G, H, ParentNode ������ ���¸���Ʈ�� �߰�
	//F = G + H
	//G = ���ۿ��� ����
	//H = ���翡�� ����
	neighborNode->G = moveCost;
	neighborNode->H = (abs(neighborNode->idx - _endNode->idx) + abs(neighborNode->idy - _endNode->idy)) * 10;
	neighborNode->F = neighborNode->G + neighborNode->H;
	neighborNode->parentNode = _curNode;
	_openList.push_back(neighborNode);
}

void Astar::delOpenList(int index)
{
	_openList.erase(_openList.begin() + index);
}