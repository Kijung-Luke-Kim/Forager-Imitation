#include "stdafx.h"
#include "EffectManager.h"

void EffectManager::init()
{
	IMAGEMANAGER->addImage(walkEff, "Images/�̹���/Effects/img_effect_walk1.bmp", 29, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("damageBoundary", "Images/�̹���/Effects/img_effect_damageBoundary.bmp", 112, 112, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage(smokeEff, "Images/�̹���/Effects/img_effect_digSmoke.bmp", 1080, 120, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("treasure", "Images/�̹���/Effects/img_effect_treasureBoxOpen.bmp", 1280, 128, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("levelUp", "Images/�̹���/Effects/img_effect_levelUp.bmp", 2816, 256, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage(explodeEff, "Images/�̹���/NPC/bossSlime_explode_effect.bmp", 736, 92, 8, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("pickEff4", "Images/�̹���/Effects/img_effect_pick4.bmp", 228, 76, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("swordEff4", "Images/�̹���/Effects/img_effect_sword4.bmp", 3496, 76, 46, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bowEff4", "Images/�̹���/Effects/img_effect_bow4.bmp", 3120, 120, 26, 1, true, RGB(255, 0, 255));


	for (int i = 0; i < MAX_EFFECT; i++) {
		_effects[i] = new tagEffect;
		_effects[i]->imgKey = "temp";
		_effects[i]->count = 0;
		_effects[i]->isAppear = false;
		_effects[i]->isFrameImage = false;
		_effects[i]->isReset = false;
		_effects[i]->isRelative = false;
		_effects[i]->isPingPong = false;
		_effects[i]->isAlpha = false;
		_effects[i]->isStretch = false;
		_effects[i]->currentAlpha = 0;
		_effects[i]->toAlpha = 0;
		_effects[i]->destSize = 1.0f;
		_effects[i]->currentSize = 1.0f;
		_effects[i]->frameX = 0;
		_effects[i]->maxFrameX = 0;
		_effects[i]->width = 0;
		_effects[i]->height = 0;
		_effects[i]->interval = 0;
		
		_effects[i]->ptPos = { 0, 0 };
	}
}

void EffectManager::release()
{
	for (int i = 0; i < MAX_EFFECT; i++) {
		SAFE_DELETE(_effects[i]);
	}

	_listEffectBack.clear();
	_listEffectFront.clear();

}

void EffectManager::update()
{
	
	// ����Ʈ�� ����Ʈ�� ������ŭ�� �ݺ� ����
	if (!_listEffectFront.empty()) {
		for (iter = _listEffectFront.begin(); iter != _listEffectFront.end(); ++iter) {
			
			// ������ �̹����� ���, ������ ����
			if ((*iter)->isFrameImage) {

				if ((*iter)->count++ >= (*iter)->interval) {
					(*iter)->count = 0;

					// ��� �������� �� ���� ����Ʈ ����.
					if ((*iter)->frameX++ >= (*iter)->maxFrameX) {
						(*iter)->isAppear = false;
						_listEffectFront.erase(iter);
						return;
					}
					
				}
			}

			// �Ϲ� �̹����� ���, ���İ��� Ȯ�� ��� ����
			else {
				// �̹��� ���� ����
				if (!(*iter)->isReset) {

					// Ȯ��
					if ((*iter)->isStretch) {
						if ((*iter)->currentSize < (*iter)->destSize)
							(*iter)->currentSize += 0.02f;
					}

					// ����
					if ((*iter)->isAlpha) {
						if ((*iter)->currentAlpha < (*iter)->toAlpha)
							(*iter)->currentAlpha += (*iter)->alphaSpeed;
					}

					// Ȯ�밡 �ִ�ġ�� �����ϸ�
					if ((*iter)->isStretch && (*iter)->currentSize >= (*iter)->destSize){
						// ��쿡 ���� �ణ�� ������ �� ��������� ����
						if ((*iter)->count++ >= (*iter)->interval) {
							
							// �� ���� ���Ͱ� �ʿ���� ��� �ٷ� ����
							if (!(*iter)->isPingPong)
							{
								(*iter)->isAppear = false;
								_listEffectFront.erase(iter);
								return;
							}
							// �ʱ� ���·� ������ ���-
							else
								(*iter)->isReset = true;
						}
					}
					// ���İ� ����� �ִ�ġ�� �����ϸ�
					if ((*iter)->isAlpha && (*iter)->currentAlpha >= (*iter)->toAlpha) {
						(*iter)->currentAlpha = 255;
						// ��쿡 ���� �ణ�� ������ �� ��������� ����
						if ((*iter)->count++ >= (*iter)->interval) {

							// �� ���� ���Ͱ� �ʿ���� ��� �ٷ� ����
							if (!(*iter)->isPingPong)
							{
								// ������ ��� ����Ʈ�� �Բ� ����ü ����
								//EFFECTMANAGER->ShowEffectFrame(smokeEff, (*iter)->ptPos, true);
								EFFECTMANAGER->ShowEffectFrame(explodeEff, (*iter)->ptPos, 5, true);
								UNITMANAGER->GetProjectileMG()->CreateProjectile((*iter)->ptPos.x-40, (*iter)->ptPos.y-40, 20, 112, 112);

								(*iter)->isAppear = false;
								_listEffectFront.erase(iter);
								return;
							}
							// �ʱ� ���·� ������ ���-
							else
								(*iter)->isReset = true;
						}
					}

				}
				// ���İ� �϶�
				else if((*iter)->isReset && (*iter)->isPingPong) {
					if ((*iter)->currentAlpha > 0)
						(*iter)->currentAlpha -= 10;
					else {
						(*iter)->isAppear = false;
						_listEffectFront.erase(iter);
						return;
					}
				}
			}
		}
	}

	// ����Ʈ�� ����Ʈ�� ������ŭ�� �ݺ� ����
	if (!_listEffectBack.empty()) {
		for (iter = _listEffectBack.begin(); iter != _listEffectBack.end(); ++iter) {

			// ������ �̹����� ���, ������ ����
			if ((*iter)->isFrameImage) {

				if ((*iter)->count++ >= (*iter)->interval) {
					(*iter)->count = 0;

					// ��� �������� �� ���� ����Ʈ ����.
					if ((*iter)->frameX++ >= (*iter)->maxFrameX) {
						(*iter)->isAppear = false;
						_listEffectBack.erase(iter);
						return;
					}

				}
			}

			// �Ϲ� �̹����� ���, ���İ��� Ȯ�� ��� ����
			else {
				// �̹��� ���� ����
				if (!(*iter)->isReset) {

					// Ȯ��
					if ((*iter)->isStretch) {
						if ((*iter)->currentSize < (*iter)->destSize)
							(*iter)->currentSize += 0.02f;
					}

					// ����
					if ((*iter)->isAlpha) {
						if ((*iter)->currentAlpha < (*iter)->toAlpha)
							(*iter)->currentAlpha += (*iter)->alphaSpeed;
					}

					// Ȯ�밡 �ִ�ġ�� �����ϸ�
					if ((*iter)->isStretch && (*iter)->currentSize >= (*iter)->destSize) {
						// ��쿡 ���� �ణ�� ������ �� ��������� ����
						if ((*iter)->count++ >= (*iter)->interval) {

							// �� ���� ���Ͱ� �ʿ���� ��� �ٷ� ����
							if (!(*iter)->isPingPong)
							{
								(*iter)->isAppear = false;
								_listEffectBack.erase(iter);
								return;
							}
							// �ʱ� ���·� ������ ���-
							else
								(*iter)->isReset = true;
						}
					}
					// ���İ� ����� �ִ�ġ�� �����ϸ�
					if ((*iter)->isAlpha && (*iter)->currentAlpha >= (*iter)->toAlpha) {
						(*iter)->currentAlpha = 255;
						// ��쿡 ���� �ణ�� ������ �� ��������� ����
						if ((*iter)->count++ >= (*iter)->interval) {

							// �� ���� ���Ͱ� �ʿ���� ��� �ٷ� ����
							if (!(*iter)->isPingPong)
							{
								// ������ ��� ����Ʈ�� �Բ� ����ü ����
								//EFFECTMANAGER->ShowEffectFrame(smokeEff, (*iter)->ptPos, true);
								EFFECTMANAGER->ShowEffectFrame(explodeEff, (*iter)->ptPos, 5, true);
								UNITMANAGER->GetProjectileMG()->CreateProjectile((*iter)->ptPos.x - 40, (*iter)->ptPos.y - 40, 20, 112, 112);

								(*iter)->isAppear = false;
								_listEffectBack.erase(iter);
								return;
							}
							// �ʱ� ���·� ������ ���-
							else
								(*iter)->isReset = true;
						}
					}

				}
				// ���İ� �϶�
				else if ((*iter)->isReset && (*iter)->isPingPong) {
					if ((*iter)->currentAlpha > 0)
						(*iter)->currentAlpha -= 10;
					else {
						(*iter)->isAppear = false;
						_listEffectBack.erase(iter);
						return;
					}
				}
			}
		}
	}
}

void EffectManager::renderBack(HDC hdc)
{
	if (!_listEffectBack.empty()) {
		for (iter = _listEffectBack.begin(); iter != _listEffectBack.end(); ++iter) {
			if ((*iter)->isAppear) {
				if ((*iter)->isFrameImage)
				{
					if (!(*iter)->isRelative)
						IMAGEMANAGER->frameRender((*iter)->imgKey, hdc, (*iter)->ptPos.x - ((*iter)->width * 0.5f), (*iter)->ptPos.y - ((*iter)->height * 0.5f), (*iter)->frameX, 0);
					else
						IMAGEMANAGER->frameRender((*iter)->imgKey, hdc, CAMERA->GetRelativeX((*iter)->ptPos.x - ((*iter)->width * 0.5f)), CAMERA->GetRelativeY((*iter)->ptPos.y - ((*iter)->height * 0.5f)), (*iter)->frameX, 0, CAMERA->GetZoom());
				}
				else if ((*iter)->isStretch) {
					if (!(*iter)->isRelative)
						IMAGEMANAGER->stretchRender((*iter)->imgKey, hdc, (*iter)->ptPos.x - ((*iter)->width * (*iter)->currentSize * 0.5f), (*iter)->ptPos.y - ((*iter)->height * (*iter)->currentSize * 0.5f), 0, 0, (*iter)->width + (*iter)->width * (*iter)->currentSize, (*iter)->height + (*iter)->height * (*iter)->currentSize, (*iter)->currentAlpha);
					else
						IMAGEMANAGER->stretchRender((*iter)->imgKey, hdc, CAMERA->GetRelativeX((*iter)->ptPos.x - ((*iter)->width * (*iter)->currentSize * 0.5f)), CAMERA->GetRelativeY((*iter)->ptPos.y - ((*iter)->height * (*iter)->currentSize * 0.5f)), 0, 0, (*iter)->width + (*iter)->width * (*iter)->currentSize, (*iter)->height + (*iter)->height * (*iter)->currentSize, (*iter)->currentAlpha, CAMERA->GetZoom());
				}
				else if ((*iter)->isAlpha) {
					if (!(*iter)->isRelative)
						IMAGEMANAGER->alphaRender((*iter)->imgKey, hdc, (*iter)->ptPos.x - ((*iter)->width * 0.5f), (*iter)->ptPos.y - ((*iter)->height * 0.5f), (*iter)->currentAlpha, CAMERA->GetZoom());
					else
						IMAGEMANAGER->alphaRender((*iter)->imgKey, hdc, CAMERA->GetRelativeX((*iter)->ptPos.x - ((*iter)->width * 0.5f)), CAMERA->GetRelativeY((*iter)->ptPos.y - ((*iter)->height * 0.5f)), (*iter)->currentAlpha, CAMERA->GetZoom());
				}
			}
		}
	}

}
void EffectManager::renderFront(HDC hdc)
{
	if (!_listEffectFront.empty()) {
		for (iter = _listEffectFront.begin(); iter != _listEffectFront.end(); ++iter) {
			if ((*iter)->isAppear) {
				if ((*iter)->isFrameImage)
				{
					if (!(*iter)->isRelative)
						IMAGEMANAGER->frameRender((*iter)->imgKey, hdc, (*iter)->ptPos.x - ((*iter)->width * 0.5f), (*iter)->ptPos.y - ((*iter)->height * 0.5f), (*iter)->frameX, 0);
					else
						IMAGEMANAGER->frameRender((*iter)->imgKey, hdc, CAMERA->GetRelativeX((*iter)->ptPos.x - ((*iter)->width * 0.5f)), CAMERA->GetRelativeY((*iter)->ptPos.y - ((*iter)->height * 0.5f)), (*iter)->frameX, 0, CAMERA->GetZoom());
				}
				else if ((*iter)->isStretch) {
					if (!(*iter)->isRelative)
						IMAGEMANAGER->stretchRender((*iter)->imgKey, hdc, (*iter)->ptPos.x - ((*iter)->width * (*iter)->currentSize * 0.5f), (*iter)->ptPos.y - ((*iter)->height * (*iter)->currentSize * 0.5f), 0, 0, (*iter)->width + (*iter)->width * (*iter)->currentSize, (*iter)->height + (*iter)->height * (*iter)->currentSize, (*iter)->currentAlpha);
					else
						IMAGEMANAGER->stretchRender((*iter)->imgKey, hdc, CAMERA->GetRelativeX((*iter)->ptPos.x - ((*iter)->width * (*iter)->currentSize * 0.5f)), CAMERA->GetRelativeY((*iter)->ptPos.y - ((*iter)->height * (*iter)->currentSize * 0.5f)), 0, 0, (*iter)->width + (*iter)->width * (*iter)->currentSize, (*iter)->height + (*iter)->height * (*iter)->currentSize, (*iter)->currentAlpha, CAMERA->GetZoom());
				}
				else if ((*iter)->isAlpha) {
					if (!(*iter)->isRelative)
						IMAGEMANAGER->alphaRender((*iter)->imgKey, hdc, (*iter)->ptPos.x - ((*iter)->width * 0.5f), (*iter)->ptPos.y - ((*iter)->height * 0.5f), (*iter)->currentAlpha, CAMERA->GetZoom());
					else
						IMAGEMANAGER->alphaRender((*iter)->imgKey, hdc, CAMERA->GetRelativeX((*iter)->ptPos.x - ((*iter)->width * 0.5f)), CAMERA->GetRelativeY((*iter)->ptPos.y - ((*iter)->height * 0.5f)), (*iter)->currentAlpha, CAMERA->GetZoom());
				}
			}
		}
	}

}

void EffectManager::ShowEffectFrame(string _imgKey, POINT ptPos, bool isRelative)
{
	for (int i = 0; i < MAX_EFFECT; i++) {
		if (!_effects[i]->isAppear) {
			_effects[i]->isAppear = true;
			_effects[i]->isFrameImage = true;
			_effects[i]->isReset = false;
			_effects[i]->isPingPong = false;
			_effects[i]->isStretch = false;
			_effects[i]->isAlpha = false;
			_effects[i]->isRelative = isRelative;
			_effects[i]->count = 0;
			_effects[i]->alphaSpeed = 10;
			_effects[i]->interval = 0;
			_effects[i]->currentAlpha = 255;
			_effects[i]->toAlpha = 255;
			_effects[i]->currentSize = 1.0f;
			_effects[i]->destSize = 1.0f;
			_effects[i]->imgKey = _imgKey;
			_effects[i]->ptPos = ptPos;
			_effects[i]->frameX = 0;
			image *temp = IMAGEMANAGER->findImage(_imgKey);
			_effects[i]->maxFrameX = temp ->getMaxFrameX();
			_effects[i]->width = temp->getFrameWidth();
			_effects[i]->height = temp->getFrameHeight();

			_listEffectFront.push_back(_effects[i]);
			break;
		}
	}
}

void EffectManager::ShowEffectFrame(string _imgKey, POINT ptPos, int frameInterval, bool isRelative)
{
	for (int i = 0; i < MAX_EFFECT; i++) {
		if (!_effects[i]->isAppear) {
			_effects[i]->imgKey = _imgKey;
			
			_effects[i]->isAppear = true;
			_effects[i]->isFrameImage = true;
			_effects[i]->isReset = false;
			_effects[i]->isPingPong = false;
			_effects[i]->isStretch = false;
			_effects[i]->isAlpha = false;
			_effects[i]->isRelative = isRelative;
			_effects[i]->count = 0;
			_effects[i]->alphaSpeed = 10;
			_effects[i]->interval = frameInterval;
			_effects[i]->currentAlpha = 255;
			_effects[i]->toAlpha = 255;
			_effects[i]->currentSize = 1.0f;
			_effects[i]->destSize = 1.0f;
			_effects[i]->ptPos = ptPos;
			_effects[i]->frameX = 0;
			_effects[i]->maxFrameX = IMAGEMANAGER->findImage(_imgKey)->getMaxFrameX();
			_effects[i]->width = IMAGEMANAGER->findImage(_imgKey)->getFrameWidth();
			_effects[i]->height = IMAGEMANAGER->findImage(_imgKey)->getFrameHeight();
			_listEffectFront.push_back(_effects[i]);
			break;
		}
	}

}

void EffectManager::ShowEffectFrame(string _imgKey, POINT ptPos, int frameInterval, float size, bool isRelative)
{
	for (int i = 0; i < MAX_EFFECT; i++) {
		if (!_effects[i]->isAppear) {

			_effects[i]->isAppear = true;
			_effects[i]->isFrameImage = true;
			_effects[i]->isReset = false;
			_effects[i]->isPingPong = false;
			_effects[i]->isStretch = false;
			_effects[i]->isAlpha = false;
			_effects[i]->isRelative = isRelative;
			_effects[i]->count = 0;
			_effects[i]->alphaSpeed = 10;
			_effects[i]->interval = frameInterval;
			_effects[i]->currentAlpha = 255;
			_effects[i]->toAlpha = 255;
			_effects[i]->currentSize = size;
			_effects[i]->destSize = size;
			_effects[i]->imgKey = _imgKey;
			_effects[i]->ptPos = ptPos;
			_effects[i]->frameX = 0;
			image *temp = IMAGEMANAGER->findImage(_imgKey);
			_effects[i]->maxFrameX = temp->getMaxFrameX();
			_effects[i]->width = temp->getFrameWidth();
			_effects[i]->height = temp->getFrameHeight();
			_listEffectFront.push_back(_effects[i]);
			break;
		}
	}
}

void EffectManager::ShowEffectAlphaSize(string _imgKey, POINT ptPos, float fromSizeA, float toSizeB, int fromAlphaA, int toAlphaB, bool isRelative)
{

	for (int i = 0; i < MAX_EFFECT; i++) {
		if (!_effects[i]->isAppear) {

			_effects[i]->isAppear = true;
			_effects[i]->isFrameImage = false;
			_effects[i]->isReset = false;
			_effects[i]->isPingPong = false;
			_effects[i]->isStretch = true;
			_effects[i]->isAlpha = true;
			_effects[i]->isRelative = isRelative;
			_effects[i]->alphaSpeed = 10;
			_effects[i]->count = 0;
			_effects[i]->interval = 0;
			_effects[i]->currentAlpha = fromAlphaA;
			_effects[i]->toAlpha = toAlphaB;
			_effects[i]->currentSize = fromSizeA;
			_effects[i]->destSize = toSizeB;
			_effects[i]->imgKey = _imgKey;
			_effects[i]->ptPos = ptPos;
			_effects[i]->frameX = 0;
			_effects[i]->maxFrameX = 0;
			image *temp = IMAGEMANAGER->findImage(_imgKey);
			_effects[i]->width = temp->getWidth();
			_effects[i]->height = temp->getHeight();
			_listEffectBack.push_back(_effects[i]);
			break;
		}
	}
}

void EffectManager::ShowEffectAlphaSize(string _imgKey, POINT ptPos, float fromSizeA, float toSizeB, int fromAlphaA, int toAlphaB, int waitCount, bool isRelative)
{
	for (int i = 0; i < MAX_EFFECT; i++) {
		if (!_effects[i]->isAppear) {

			_effects[i]->isAppear = true;
			_effects[i]->isFrameImage = false;
			_effects[i]->isReset = false;
			_effects[i]->isStretch = true;
			_effects[i]->isPingPong = false;
			_effects[i]->isAlpha = true;
			_effects[i]->isRelative = isRelative;
			_effects[i]->alphaSpeed = 10;
			_effects[i]->count = 0;
			_effects[i]->interval = waitCount;
			_effects[i]->currentAlpha = fromAlphaA;
			_effects[i]->toAlpha = toAlphaB;
			_effects[i]->currentSize = fromSizeA;
			_effects[i]->destSize = toSizeB;
			_effects[i]->imgKey = _imgKey;
			_effects[i]->ptPos = ptPos;
			_effects[i]->frameX = 0;
			_effects[i]->maxFrameX = 0;
			image *temp = IMAGEMANAGER->findImage(_imgKey);
			_effects[i]->width = temp->getWidth();
			_effects[i]->height = temp->getHeight();
			_listEffectFront.push_back(_effects[i]);
			break;
		}
	}
}

void EffectManager::ShowEffectAlpha(string _imgKey, POINT ptPos, int fromAlphaA, int toAlphaB, int alphaSpeed, int waitCount, bool isRelative, bool isPingPong)
{
	for (int i = 0; i < MAX_EFFECT; i++) {
		if (!_effects[i]->isAppear) {

			_effects[i]->isAppear = true;
			_effects[i]->isFrameImage = false;
			_effects[i]->isReset = false;
			_effects[i]->isStretch = false;
			_effects[i]->isAlpha = true;
			_effects[i]->isPingPong = isPingPong;
			_effects[i]->isRelative = isRelative;
			_effects[i]->count = 0;
			_effects[i]->alphaSpeed = alphaSpeed;
			_effects[i]->interval = waitCount;
			_effects[i]->currentAlpha = fromAlphaA;
			_effects[i]->toAlpha = toAlphaB;
			_effects[i]->currentSize = 1.0f;
			_effects[i]->destSize = 1.0f;
			_effects[i]->imgKey = _imgKey;
			_effects[i]->ptPos = ptPos;
			_effects[i]->frameX = 0;
			_effects[i]->maxFrameX = 0;
			image *temp = IMAGEMANAGER->findImage(_imgKey);
			_effects[i]->width = temp->getWidth();
			_effects[i]->height = temp->getHeight();
			_listEffectBack.push_back(_effects[i]);
			break;
		}
	}
}
