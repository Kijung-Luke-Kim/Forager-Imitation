#include "stdafx.h"
#include "earth.h"

HRESULT earth::init()
{
	//����
	watertile = IMAGEMANAGER->addImage("watertile", "Images/�̹���/Ÿ��/img_tile_water.bmp", TILESIZE, TILESIZE);
	plaintile = IMAGEMANAGER->addFrameImage("plaintile", "Images/�̹���/Ÿ��/img_tile_plain.bmp", 224, 56, 4, 1);
	plainedge = IMAGEMANAGER->addFrameImage("plainedge", "Images/�̹���/Ÿ��/img_tile_plainEdge.bmp", 224, 112, 4, 2, true, RGB(255, 0, 255));
	wave = IMAGEMANAGER->addImage("wave", "Images/�̹���/Ÿ��/img_tile_wave.bmp", 56, 56);
	underwater = IMAGEMANAGER->addImage("underwater", "Images/�̹���/Ÿ��/img_tile_bottomGround.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TitleBG", "Images/�̹���/img_Background.bmp", 2000, 1300, true, RGB(255, 0, 255));
	_count = wavetick = _frameCount = 0;

	//�ڿ�
	IMAGEMANAGER->addFrameImage("berry", "Images/�̹���/������Ʈ/resource/img_object_berry.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rock", "Images/�̹���/������Ʈ/resource/img_object_rock.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tree", "Images/�̹���/������Ʈ/resource/img_object_tree.bmp", 280, 168, 5, 1, true, RGB(255, 0, 255));

	//����� �ʱ�ȭ
	this->mapSetup();

	return S_OK;
}

void earth::release()
{
}

bool compare(unit i, unit j) {
	return i.rc.top < j.rc.top;
}

void earth::update()
{
	_count++;
	if (_count % RESGENTIME == 0) {
		this->setRandomObject();
	}
	if (_count % 10 == 0) {
		wavetick++;
	}
	if (wavetick > 10) {
		wavetick = 0;
	}
	sort(_vUnit.begin(), _vUnit.end(), compare);
}

void earth::render(HDC hdc)
{
	// ����� ����
	IMAGEMANAGER->findImage("TitleBG")->render(hdc, -500, -400);
	//���� ����
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			RECT temp;

			// ī�޶� ������ ����
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &_vTile[i*MAPTILEY + j].rc)) continue;

			// ���� ����
			if (_vTile[i*MAPTILEY + j].terrKey != "watertile") {
				IMAGEMANAGER->frameRender(_vTile[i*MAPTILEY + j].terrKey, hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), _vTile[i*MAPTILEY + j].terrainFrameX, _vTile[i*MAPTILEY + j].terrainFrameY);
				//���� ������
				if (j - 1 >= 0 && _vTile[(i)*MAPTILEY + (j - 1)].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 0, 1);
				}
				//���� ������
				if (i - 1 >= 0 && j + 1 < MAPTILEX && _vTile[(i - 1)*MAPTILEY + (j + 1)].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 1, 1);
				}
				//���� ������
				if (i + 1 < MAPTILEY && j + 1 < MAPTILEX && _vTile[(i + 1)*MAPTILEY + (j + 1)].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 2, 1);
				}
				//���� ������
				if (i + 1 < MAPTILEY && j - 1 >= 0 && _vTile[(i + 1)*MAPTILEY + (j - 1)].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 3, 1);
				}
				//��
				if (j - 1 >= 0 && _vTile[i*MAPTILEY + (j - 1)].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 0, 0);
				}
				//��
				if (j + 1 < MAPTILEX && _vTile[i*MAPTILEY + (j + 1)].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 1, 0);
				}
				//��
				if (i - 1 >= 0 && _vTile[(i - 1)*MAPTILEY + j].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 2, 0);
				}
				//��
				if (i + 1 < MAPTILEY && _vTile[(i + 1)*MAPTILEY + j].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 3, 0);
					underwater->render(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.bottom));
					wave->alphaRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.bottom + 20 + wavetick), 100);

				}
			}
		}
	}
	//����(�ڿ�, ����) ����
	for (int i = 0; i < _vUnit.size();  i++) {
		RECT temp;
		if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &_vUnit[i].rc)) continue;
		IMAGEMANAGER->frameRender(_vUnit[i].objKey, hdc, 
								  CAMERA->GetRelativeX(_vUnit[i].rc.left), 
								  CAMERA->GetRelativeY(_vUnit[i].rc.bottom - IMAGEMANAGER->findImage(_vUnit[i].objKey)->getFrameHeight()), 
								  _vUnit[i].objFrameX, _vUnit[i].objFrameY);
	}
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
			_tile.terrainFrameX = 0;
			_tile.terrainFrameY = 0;
			_tile.hasUnit = false;
			_vTile.push_back(_tile);
		}
	}
	this->setIsland(3, 3);
}

void earth::setRandomObject()
{
	if (this->getResRatio() > RESRATIOLIMIT) return;
	while (true) {
		int i = RANDOM->range(TILEY*MAPY);
		int j = RANDOM->range(MAPTILEX);
		//���� �÷��̾ ���ִ� Ÿ���� ��ŵ
		if (i + j == getPlayerPos()) continue;
		if (!_vTile[i*MAPTILEY + j].hasUnit &&
			_vTile[i*MAPTILEY + j].terrKey == "plaintile") {
			_vTile[i*MAPTILEY + j].hasUnit = true;
			resource _res;
			_res.setRandomRes(_vTile[i*MAPTILEY + j].rc);
			_vUnit.push_back(_res);
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
				!_vTile[i*MAPTILEY + j].hasUnit) {
				nPlainTile++;
			}
			else if (_vTile[i*MAPTILEY + j].terrKey == "plaintile" &&
				_vTile[i*MAPTILEY + j].hasUnit) {
				nResTile++;
			}
		}
	}
	return nResTile / float(nPlainTile);
}

int earth::getPlayerPos()
{
	//int playerCenterX = _player->rc.left + (_player->rc.right - _player->rc.left) / 2;
	//int playerCenterY = _player->rc.bottom;
	//POINT _ptPlayerPos = { playerCenterX, playerCenterY };


	//for (int i = 0; i < MAPTILEY; i++) {
	//	for (int j = 0; j < MAPTILEX; j++) {
	//		if (PtInRect(&_vTile[i*MAPTILEY + j].rc, _ptPlayerPos)) {
	//			return (i*MAPTILEY + j);
	//		}
	//	}
	//}
	return 0;
}

void earth::setIsland(int x, int y)
{
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			if (j == 0 || j == TILEX - 1 || i == 0 || i == TILEY -1 ) {
				switch (RANDOM->range(2)) {
				case 0:
					_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrKey = "plaintile";
					_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrainFrameX = RANDOM->range(4);
					break;
				case 1:
					break;
				}
			}
			else {
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrKey = "plaintile";
				_vTile[(y * MAPTILEY*TILEY + i * MAPTILEY) + x * TILEX + j].terrainFrameX = RANDOM->range(4);
			}
		}
	}
}
