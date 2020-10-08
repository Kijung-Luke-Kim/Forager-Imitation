#include "stdafx.h"
#include "EffectManager.h"

void EffectManager::init()
{
	IMAGEMANAGER->addImage(walkEff, "Images/�̹���/Effects/img_effect_walk1.bmp", 29, 29, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage(smokeEff, "Images/�̹���/Effects/img_effect_digSmoke.bmp", 1080, 120, 9, 1, true, RGB(255, 0, 255));

	for (int i = 0; i < MAX_EFFECT; i++) {
		_effects[i] = new tagEffect;
		_effects[i]->imgKey = "temp";
		_effects[i]->isAppear = false;
		_effects[i]->isFrameImage = false;
		_effects[i]->isReset = false;
		_effects[i]->isRelative = false;
		_effects[i]->ptPos = { 0, 0 };
	}
}

void EffectManager::release()
{
	for (int i = 0; i < MAX_EFFECT; i++) {
		SAFE_DELETE(_effects[i]);
	}

	_listEffect.clear();

}

void EffectManager::update()
{
	
	// ����Ʈ�� ����Ʈ�� ������ŭ�� �ݺ� ����
	if (!_listEffect.empty()) {
		for (iter = _listEffect.begin(); iter != _listEffect.end(); ++iter) {
			
			// ������ �̹����� ���, ������ ����
			if ((*iter)->isFrameImage) {

				if ((*iter)->count++ >= (*iter)->interval) {
					(*iter)->count = 0;

					// ��� �������� �� ���� ����Ʈ ����.
					if ((*iter)->frameX++ >= (*iter)->maxFrameX) {
						(*iter)->isAppear = false;
						_listEffect.erase(iter);
						return;
					}
					
				}
			}

			// �Ϲ� �̹����� ���, ���İ��� Ȯ�� ��� ����
			else {
				// Ȯ��� ���İ� ���
				if (!(*iter)->isReset) {
					if ((*iter)->currentSize < (*iter)->destSize)
						(*iter)->currentSize += 0.02f;
					if ((*iter)->currentAlpha < (*iter)->toAlpha)
						(*iter)->currentAlpha += 10;

					// Ȯ��� ���İ� ����� �ִ�ġ�� �����ϸ�
					if ((*iter)->currentSize >= (*iter)->destSize && (*iter)->currentAlpha >= (*iter)->toAlpha) {

						// ��쿡 ���� �ణ�� ������ �� ��������� ����
						if ((*iter)->count++ >= (*iter)->interval)
							(*iter)->isReset = true;
					}
				}
				// ���İ� �϶�
				else {
					if ((*iter)->currentAlpha > 0)
						(*iter)->currentAlpha -= 10;
					else {
						(*iter)->isAppear = false;
						_listEffect.erase(iter);
						return;
					}
				}
			}
		}
	}

}

void EffectManager::render(HDC hdc)
{
	if (!_listEffect.empty()) {
		for (iter = _listEffect.begin(); iter != _listEffect.end(); ++iter) {
			if ((*iter)->isAppear) {
				if ((*iter)->isFrameImage)
				{
					if (!(*iter)->isRelative)
						IMAGEMANAGER->frameRender((*iter)->imgKey, hdc, (*iter)->ptPos.x - ((*iter)->width * 0.5f), (*iter)->ptPos.y - ((*iter)->height * 0.5f), (*iter)->frameX, 0);
					else
						IMAGEMANAGER->frameRender((*iter)->imgKey, hdc, CAMERA->GetRelativeX((*iter)->ptPos.x - ((*iter)->width * 0.5f)), CAMERA->GetRelativeY((*iter)->ptPos.y - ((*iter)->height * 0.5f)), (*iter)->frameX, 0, CAMERA->GetZoom());
				}
				else {
					if(!(*iter)->isRelative)
						IMAGEMANAGER->stretchRender((*iter)->imgKey, hdc, (*iter)->ptPos.x - ((*iter)->width * (*iter)->currentSize * 0.5f), (*iter)->ptPos.y - ((*iter)->height * (*iter)->currentSize * 0.5f), 0, 0, (*iter)->width + (*iter)->width * (*iter)->currentSize, (*iter)->height + (*iter)->height * (*iter)->currentSize, (*iter)->currentAlpha);
					else
						IMAGEMANAGER->stretchRender((*iter)->imgKey, hdc, CAMERA->GetRelativeX((*iter)->ptPos.x - ((*iter)->width * (*iter)->currentSize * 0.5f)), CAMERA->GetRelativeY((*iter)->ptPos.y - ((*iter)->height * (*iter)->currentSize * 0.5f)), 0, 0, (*iter)->width + (*iter)->width * (*iter)->currentSize, (*iter)->height + (*iter)->height * (*iter)->currentSize, (*iter)->currentAlpha, CAMERA->GetZoom());
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
			_effects[i]->isRelative = isRelative;
			_effects[i]->count = 0;
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

			_listEffect.push_back(_effects[i]);
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
			_effects[i]->isRelative = isRelative;
			_effects[i]->count = 0;
			_effects[i]->interval = frameInterval;
			_effects[i]->currentAlpha = 255;
			_effects[i]->toAlpha = 255;
			_effects[i]->currentSize = 1.0f;
			_effects[i]->destSize = 1.0f;
			_effects[i]->ptPos = ptPos;
			_effects[i]->frameX = 0;
			image* temp = IMAGEMANAGER->findImage(_imgKey);
			_effects[i]->maxFrameX = temp->getMaxFrameX();
			_effects[i]->width = temp->getFrameWidth();
			_effects[i]->height = temp->getFrameHeight();
			_listEffect.push_back(_effects[i]);
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
			_effects[i]->isRelative = isRelative;
			_effects[i]->count = 0;
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
			_listEffect.push_back(_effects[i]);
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
			_effects[i]->isRelative = isRelative;
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
			_listEffect.push_back(_effects[i]);
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
			_effects[i]->isRelative = isRelative;
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
			_listEffect.push_back(_effects[i]);
			break;
		}
	}
}
