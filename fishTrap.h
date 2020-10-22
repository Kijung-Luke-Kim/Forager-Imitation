#pragma once
#include "building.h"
#include "cursor.h"

class fishTrap : public building
{
private:

	// Fish ����
	int _cntfishWait;
	int _fishWait;
	bool _isCatch;

	// �ؽ�Ʈ ������ ����
	int sizeMin;
	int sizeCurrent;
	int sizeMax;
	bool sizeUp;

	// Ŀ�� ����
	cursor *_cursor;


public:
	void setFishTrap(string buildingName, tile* _tile, int tileindex);

	void update() override;
	void animation();
	void fish();
	
	void render(HDC hdc) override;

};

