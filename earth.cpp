#include "stdafx.h"
#include "earth.h"

HRESULT earth::init()
{
	//����
	IMAGEMANAGER->addImage("watertile", "Images/�̹���/Ÿ��/img_tile_water.bmp", TILESIZE, TILESIZE);
	IMAGEMANAGER->addFrameImage("plaintile", "Images/�̹���/Ÿ��/img_tile_plain.bmp", 224, 56, 4, 1);
	IMAGEMANAGER->addFrameImage("plainedge", "Images/�̹���/Ÿ��/img_tile_plainEdge.bmp", 224, 112, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wave", "Images/�̹���/Ÿ��/img_tile_wave.bmp", 56, 56);
	IMAGEMANAGER->addImage("underwater", "Images/�̹���/Ÿ��/img_tile_bottomGround.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TitleBG", "Images/�̹���/img_Background.bmp", 2000, 1300);
	_count = wavetick = _frameCount = 0;
	waveUp = true;


	//Ư�� �ǹ� �̹���
	IMAGEMANAGER->addFrameImage("goddess", "Images/�̹���/������Ʈ/img_object_goddess.bmp", 56 * 2*7, 56 * 3, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("goddessdesign", "Images/�̹���/������Ʈ/img_object_goddess_design.bmp", 56*2, 56 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("goddesswell", "Images/�̹���/������Ʈ/img_object_goddesswell.bmp", 56 * 4, 56 * 7, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("goddesswelldesign", "Images/�̹���/������Ʈ/img_object_goddesswell.bmp", 56 * 4, 56 * 7, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("elventree", "Images/�̹���/������Ʈ/img_object_elventree.bmp", 56 * 4, 56 * 6, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elventreedesign", "Images/�̹���/������Ʈ/img_object_elventree.bmp", 56 * 4, 56 * 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("elvenstatue", "Images/�̹���/������Ʈ/img_object_elvenstatue.bmp", 56 * 2, 56 * 3, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elvenstatuedesign", "Images/�̹���/������Ʈ/img_object_elvenstatue.bmp", 56 * 2, 56 * 3, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("tombCenter", "Images/�̹���/������Ʈ/tombstone1.bmp", 56 * 2, 56 * 4, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tombCenterdesign", "Images/�̹���/������Ʈ/tombstone1.bmp", 56 * 2, 56 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tombLeft", "Images/�̹���/������Ʈ/tombstone1.bmp", 56 * 2, 56 * 3, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tombLeftdesign", "Images/�̹���/������Ʈ/tombstone1.bmp", 56 * 2, 56 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tombRight", "Images/�̹���/������Ʈ/tombstone1.bmp", 56 * 2, 56 * 3, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tombRightdesign", "Images/�̹���/������Ʈ/tombstone1.bmp", 56 * 2, 56 * 3, true, RGB(255, 0, 255));
	//����� �ʱ�ȭ
	this->mapSetup();
	hasDestiny = false;

	UNITMANAGER->init();				//���ָŴ��� �ʱ�ȭ

	return S_OK;
}

void earth::release()
{
	// ���ָŴ��� ����
	UNITMANAGER->release();
	UNITMANAGER->releaseSingleton();
}


void earth::update()
{
	if (!hasDestiny) {
		hasDestiny = true;
		this->SetDestiny();
	}
	if (CAMERA->movelimit) {
		_count++;
		if (_count % RESGENTIME == 0) {
			//this->setRandomObject();
		}
		if (_count % 10 == 0) {
			wavetick += waveUp ? 1 : -1;

			if (wavetick > 10 || wavetick < 0) {
				waveUp = !waveUp;
			}
		}

		//���ָŴ��� ������Ʈ
		UNITMANAGER->update();
	}
}

void earth::render(HDC hdc)
{
	//<�ؽ��� �Ŵ��� ���� ������ ���>
	// ����� ����
	IMAGEMANAGER->findImage("TitleBG")->render(hdc, -500, -400);

	//<�ؽ��� �Ŵ��� ���� ������ ���>
	//���� ����
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			RECT temp;

			// ī�޶� ������ ����
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &_vTile[i*MAPTILEY + j].rc)) continue;

			// ���� ����
			if (_vTile[i*MAPTILEY + j].terrKey != "watertile") {

				_vTile[i*MAPTILEY + j].render(hdc);

				if (CAMERA->movelimit) {
					//���� ������
					if (j - 1 >= 0 && _vTile[(i)*MAPTILEY + (j - 1)].terrKey == "watertile") {
						IMAGEMANAGER->frameRender("plainedge", hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 0, 1, CAMERA->GetZoom());
					}
					//���� ������
					if (i - 1 >= 0 && j + 1 < MAPTILEX && _vTile[(i - 1)*MAPTILEY + (j + 1)].terrKey == "watertile") {
						IMAGEMANAGER->frameRender("plainedge", hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 1, 1, CAMERA->GetZoom());
					}
					//���� ������
					if (i + 1 < MAPTILEY && j + 1 < MAPTILEX && _vTile[(i + 1)*MAPTILEY + (j + 1)].terrKey == "watertile") {
						IMAGEMANAGER->frameRender("plainedge", hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 2, 1, CAMERA->GetZoom());
					}
					//���� ������
					if (i + 1 < MAPTILEY && j - 1 >= 0 && _vTile[(i + 1)*MAPTILEY + (j - 1)].terrKey == "watertile") {
						IMAGEMANAGER->frameRender("plainedge", hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 3, 1, CAMERA->GetZoom());
					}
				}
				
				//��
				if (j - 1 >= 0 && _vTile[i*MAPTILEY + (j - 1)].terrKey == "watertile") {
					IMAGEMANAGER->frameRender("plainedge", hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 0, 0, CAMERA->GetZoom());
				}
				//��
				if (j + 1 < MAPTILEX && _vTile[i*MAPTILEY + (j + 1)].terrKey == "watertile") {
					IMAGEMANAGER->frameRender("plainedge", hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 1, 0, CAMERA->GetZoom());
				}
				//��
				if (i - 1 >= 0 && _vTile[(i - 1)*MAPTILEY + j].terrKey == "watertile") {
					IMAGEMANAGER->frameRender("plainedge", hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 2, 0, CAMERA->GetZoom());
				}
				//��
				if (i + 1 < MAPTILEY && _vTile[(i + 1)*MAPTILEY + j].terrKey == "watertile") {
					IMAGEMANAGER->frameRender("plainedge", hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 3, 0, CAMERA->GetZoom());
					IMAGEMANAGER->render("underwater", hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.bottom), CAMERA->GetZoom());
					if (CAMERA->movelimit) 
						IMAGEMANAGER->alphaRender("wave", hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.bottom + 20 + wavetick), 100, CAMERA->GetZoom());
				}
			}
		}
	}
	
	// ���� ����
	UNITMANAGER->render(hdc);
}

void earth::mapSetup()
{
	//�ٴ��ʱ�ȭ
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			tile _tile;
			_tile.rc = RectMake(WINSIZEX / 2 - (MAPTILEX*TILESIZE / 2.0f) + j * TILESIZE, WINSIZEY / 2 - (MAPTILEY*TILESIZE / 2.0f) + i * TILESIZE, TILESIZE, TILESIZE);
			_tile.tag = TAG::TERRAIN;
			_tile.layer = LAYER::TERRAIN;
			_tile.terrKey = "watertile";
			//_tile.img = plaintile;
			_tile.terrainFrameX = 0;
			_tile.terrainFrameY = 0;
			_tile.hasUnit = false;
			_tile.canPass = false;
			_vTile.push_back(_tile);
		}
	}
	this->setIsland(3, 3);
}

void earth::setRandomObject()
{
	if (this->getResRatio() > RESRATIOLIMIT) return;
	int loopcount = 0;
	while (loopcount < 7056) {
		loopcount++;
		int i = RANDOM->range(TILEY*MAPY);
		int j = RANDOM->range(MAPTILEX);

		//���� �÷��̾ ���ִ� Ÿ���� ��ŵ
		if (i + j == _player->GetPlayerTilePos()) continue;

		if (!_vTile[i*MAPTILEY + j].hasUnit &&
			_vTile[i*MAPTILEY + j].terrKey == "plaintile") {
			_vTile[i*MAPTILEY + j].hasUnit = true;
			_vTile[i*MAPTILEY + j].canPass = false;

			// ���� �Ŵ����� �߰�
			UNITMANAGER->AddResource(&_vTile[i*MAPTILEY + j], i*MAPTILEY + j);
			break;
		}	
	}
}

float earth::getResRatio()
{
	float nResTile = 0;
	float nPlainTile = 0;
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			if (_vTile[i*MAPTILEY + j].terrKey == "plaintile" &&
				_vTile[i*MAPTILEY + j].canPass) {
				nPlainTile++;
			}
			else if (_vTile[i*MAPTILEY + j].terrKey == "plaintile" &&
				!_vTile[i*MAPTILEY + j].canPass) {
				nResTile++;
			}
		}
	}
	return nResTile / float(nPlainTile);
}

int earth::GetTileX(int index)
{
	index = index < 0 ? 0 : index;
	index = index > 7055 ? 7055 : index;
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			if (i*MAPTILEY + j == index) {
				return i;
			}
		}
	}
}

int earth::GetTileY(int index)
{
	index = index < 0 ? 0 : index;
	index = index > 7055 ? 7055 : index;
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			if (i*MAPTILEY + j == index) {
				return j;
			}
		}
	}
}

void earth::setIsland(int x, int y)
{
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			if (_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].hasUnit) {
				continue;
			}
			if (j == 0 || j == TILEX - 1 || i == 0 || i == TILEY -1 ) {
				switch (RANDOM->range(2)) {
				case 0:
					_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrKey = "plaintile";
					_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrainFrameX = RANDOM->range(4);
					_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].canPass = true;
					break;
				case 1:
					break;
				}
			}
			else {
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrKey = "plaintile";
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrainFrameX = RANDOM->range(4);
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].canPass = true;
			}
		}
	}
	if (x == 2 && y == 2) {
		SetGoddessWell(x, y);
	}
	else if (x == 2 && y == 3) {
		SetElfTree(x, y);
	}
	else if (x == 4 && y == 4) {
		SetTomb(x, y);
	}
	else if (GetIslandCount() > 5) {
		SetMonster(x, y);
	}
}

int earth::GetIslandX(int index)
{
	index = index < 0 ? 0 : index;
	index = index > 7055 ? 7055 : index;
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			if (i*MAPTILEY + j == index) {
				return j / TILEX;
			}
		}
	}
}

int earth::GetIslandY(int index)
{
	index = index < 0 ? 0 : index;
	index = index > 7055 ? 7055 : index;
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			if (i*MAPTILEY + j == index) {
				return i / TILEY;
			}
		}
	}
}

RECT earth::GetIslandRc(int x, int y)
{
	return { _vTile[(y * MAPTILEY*TILEY) + x * TILEX].rc.left,
	_vTile[(y * MAPTILEY*TILEY) + x * TILEX].rc.top,
	_vTile[(y * MAPTILEY*TILEY + (TILEY - 1) * MAPTILEY) + x * TILEX + (TILEX - 1)].rc.right,
	_vTile[(y * MAPTILEY*TILEY + (TILEY - 1) * MAPTILEY) + x * TILEX + (TILEX - 1)].rc.bottom };
	
}

bool earth::HasIsland(int x, int y)
{
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			if (_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrKey == "plaintile") {
				return true;
			}
		}
	}
	return false;
}

int earth::GetIslandCount()
{
	int count = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (HasIsland(i, j)) {
				count++;
			}
		}
	}
	return count;
}

int earth::GetTileIndex(POINT pt)
{
	for (int i = 0; i < _vTile.size(); i++) {
		if (PtInRect(&_vTile[i].rc, pt)) {
			return i;
		}
	}
}

void earth::SetGoddessWell(int x, int y)
{
	vector<tile*> vWellTiles;
	vector<tile*> vStoneTiles;
	int wellTileIndex = (y * MAPTILEY*TILEY + 3 * MAPTILEY) + x * TILEX + 4;
	int stoneTileIndex = (y * MAPTILEY*TILEY + 5 * MAPTILEY) + x * TILEX + 8;
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			if (_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrKey == "plaintile") {
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].hasUnit = true;
			}
			if (j > 3 && j < 8 && i > 2 && i < 9) {
				vWellTiles.push_back(&_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j]);
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].canPass = false;
			}
			if (j > 7 && j < 10 && i > 5 && i < 9) {
				vStoneTiles.push_back(&_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j]);
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].canPass = false;
			}
		}
	}
	UNITMANAGER->AddSpecialBuilding("goddesswell", vWellTiles, wellTileIndex);
	UNITMANAGER->AddSpecialBuilding("goddess", vStoneTiles, stoneTileIndex);
}

void earth::SetElfTree(int x, int y)
{
	vector<tile*> vTreeTiles;
	vector<tile*> vStoneTiles;
	int treeTileIndex = (y * MAPTILEY*TILEY + 3 * MAPTILEY) + x * TILEX + 4;
	int stoneTileIndex = (y * MAPTILEY*TILEY + 5 * MAPTILEY) + x * TILEX + 8;
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			if (_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrKey == "plaintile") {
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].hasUnit = true;
			}
			if (j > 3 && j < 8 && i > 2 && i < 9) {
				vTreeTiles.push_back(&_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j]);
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].canPass = false;
			}
			if (j > 7 && j < 10 && i > 5 && i < 9) {
				vStoneTiles.push_back(&_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j]);
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].canPass = false;
			}
		}
	}
	UNITMANAGER->AddSpecialBuilding("elventree", vTreeTiles, treeTileIndex);
	UNITMANAGER->AddSpecialBuilding("elvenstatue", vStoneTiles, stoneTileIndex);
}

void earth::SetTomb(int x, int y)
{
	vector<tile*> vTombLeft;
	vector<tile*> vTombRight;
	vector<tile*> vTombCenter;

	int tombLeftTileIndex = (y * MAPTILEY*TILEY + 3 * MAPTILEY) + x * TILEX + 2;
	int tombRightTileIndex = (y * MAPTILEY*TILEY + 3 * MAPTILEY) + x * TILEX + 8;
	int tombCenterTileIndex = (y * MAPTILEY*TILEY + 5 * MAPTILEY) + x * TILEX + 5;

	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			if (_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrKey == "plaintile") {
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].hasUnit = true;
			}
			if (j > 1 && j < 4 && i > 2 && i < 5) {
				vTombLeft.push_back(&_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j]);
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].canPass = false;
			}
			if (j > 7 && j < 10 && i > 2 && i < 5) {
				vTombRight.push_back(&_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j]);
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].canPass = false;
			}
			if (j > 4 && j < 7 && i > 4 && i < 8) {
				vTombCenter.push_back(&_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j]);
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].canPass = false;
			}
		}
	}
	UNITMANAGER->AddSpecialBuilding("tombCenter", vTombCenter, tombCenterTileIndex);
	UNITMANAGER->AddSpecialBuilding("tombLeft", vTombLeft, tombLeftTileIndex);
	UNITMANAGER->AddSpecialBuilding("tombRight", vTombRight, tombRightTileIndex);
}

void earth::SetMonster(int x, int y)
{
	int bossSpawnProabability = RANDOM->range(6);
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			if (bossSpawnProabability != 5 && _vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrKey == "plaintile") {
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].hasUnit = true;
			}
			if (GetIslandCount() > 1 && i == 5 && j == 5) {
				
				if (bossSpawnProabability == 0) {
					SPAWNMANAGER->SpawnPatternOne("muBoss", 1, (y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j);
				}
				else if (bossSpawnProabability == 1) {
					SPAWNMANAGER->SpawnPatternOne("wraithIdle", 1, (y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j);
				}
				else if (bossSpawnProabability == 2) {
					SPAWNMANAGER->SpawnPatternOne("slimeBoss", 1, (y * MAPTILEY*TILEY + 1 * MAPTILEY) + x * TILEX + 1);
					SPAWNMANAGER->SpawnPatternOne("slimeBoss", 1, (y * MAPTILEY*TILEY + 1 * MAPTILEY) + x * TILEX + 10);
					SPAWNMANAGER->SpawnPatternOne("slimeBoss", 1, (y * MAPTILEY*TILEY + 10 * MAPTILEY) + x * TILEX + 1);
					SPAWNMANAGER->SpawnPatternOne("slimeBoss", 1, (y * MAPTILEY*TILEY + 10 * MAPTILEY) + x * TILEX + 10);
				}
				else if (bossSpawnProabability == 3) {
					SPAWNMANAGER->SpawnPatternOne("wraithIdle", 1, (y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j);
				}
				else if (bossSpawnProabability == 4) {
					SPAWNMANAGER->SpawnPatternOne("wraithIdle", 1, (y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j);
				}
				else {

				}
			}
		}
	}
}

void earth::SetEmpty(int x, int y)
{
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			if (_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrKey == "plaintile") {
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].hasUnit = true;
			}
		}
	}
}

void earth::SetDestiny()
{
	int first = RANDOM->range(1, 5);
	int second = RANDOM->range(1, 5);
	int third = RANDOM->range(1, 5);
	int fourth = RANDOM->range(1, 5);
	setIsland(0, first);
	SetEmpty(0, first);
	setIsland(6, second);
	SetEmpty(6, second);
	setIsland(third, 0);
	SetEmpty(third, 0);
	setIsland(fourth, 6);
	SetEmpty(fourth, 6);
}

void earth::SetConquer(int x, int y)
{
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			if (_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrKey == "plaintile") {
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].hasUnit = false;
			}
		}
	}
}

tile* earth::tileMouseTarget()
{
	for (int i = 0; i < _vTile.size(); i++) {
		if (PtInRect(&CAMERA->GetRelativeRc(_vTile[i].rc), CAMERA->GetMouseRelativePos(_ptMouse))) {
			return &_vTile[i];
		}
	}
}

int earth::tileMouseTargetIndex()
{
	for (int i = 0; i < _vTile.size(); i++) {
		if (PtInRect(&CAMERA->GetRelativeRc(_vTile[i].rc), CAMERA->GetMouseRelativePos(_ptMouse))) {
			return i;
		}
	}
}

int earth::tileColMouseTargetIndex()
{
	for (int i = 0; i < _vTile.size(); i++) {
		if (PtInRect(&CAMERA->GetRelativeRc(_vTile[i].rc), _ptMouse)) {
			return i;
		}
	}
}
