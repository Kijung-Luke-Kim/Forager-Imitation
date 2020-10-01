#pragma once
#include "gameNode.h"
#include "ForagerPlayer.h"
#include "ForagerStatManager.h"
#include "targetingBox.h"
#include "inventory.h"
#include "tile.h"

#define PLAINHP 100
#define NUMOBJECTS 3
#define RESRATIOLIMIT 0.7
#define RESGENTIME 100

class basicmap : public gameNode
{
private:
	image* watertile;
	image* plaintile;
	image* plainedge;
	image* wave;
	image* underwater;
	int _count;
	int _frameCount;
	int wavetick;
private:
	image* steelwork;
private:
	image* berry;
	image* rock;
	image* tree;
private:
	image* treeDrop;
	image* rockDrop;
	image* berryDrop;
	
private:
	vector<tile> _vTiles;
	RECT _rcCam;
	RECT _rcPlayer;
	targetingBox* _targetingBox;
private:
	ForagerPlayer* _player;
	int _playerPos;
	POINT _ptPlayerPos;
	ForagerStatManager* _statManager;
	inGameMenu* _inventory;

private:
	vector<dropItem> _vDropItems;
	bool is_item_check = false;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void mapSetup();
	void setTile();

	/* ī�޶� �Ŵ����� ��ü
	void cameraMove();
	void cameraFocus();
	*/

	//������ Ÿ�Ͽ� �ڿ� ����
	void setRandomTile();
	float getResRatio();

	
	int getPlayerPos();				// �÷��̾��� ���� ��ǥ�� ���ϱ�
	void setPlayerPosTile(); 		// �÷��̾� ��ǥ ����
	bool checkCanMove(int index);	// �÷��̾ �̵��� Ÿ�� �̵� ���� ���� üũ

	void createDropItem(int i, int j, string pitemName, int minDrop, int maxDrop);
	void removeDropItem(int index);
	void dropItemCollision();
	void save();
	void load();
	vector<tile> getTiles() { return _vTiles; };
	void setMapTiles(vector<tile> checkTiles) { _vTiles = checkTiles; }
	void setTiles(vector<tile> _tiles) { _vTiles = _tiles; };
	tile tileMouseTarget();

	void animation();
};


