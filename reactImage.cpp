#include "stdafx.h"
#include "reactImage.h"

HRESULT reactImage::init(RECT rc, int zoomSize, int zoomSpeed, string imgKey1, string imgKey2, BYTE alpha)
{
	// �̹��� Ű��
	_imgKey1 = imgKey1;
	_imgKey2 = imgKey2;

	// ��Ʈ
	_rc = rc;

	// ��
	_currentSize = 0;
	_zoomSize = zoomSize;
	_zoomSpeed = zoomSpeed;

	// OnCursor
	_isCursorOn = false;

	_alpha = alpha;

	// �̹��� �ʺ� ����
	_width = IMAGEMANAGER->findImage(_imgKey1)->getWidth();
	_height = IMAGEMANAGER->findImage(_imgKey1)->getHeight();

	return E_NOTIMPL;
}

void reactImage::update()
{
	// OnCursor �����̸� Ȯ��
	if (_isCursorOn) {
		if (_currentSize <= _zoomSize) {
			_currentSize += 4;
		}
	}
	// �ƴϸ� �������
	else {
		_currentSize = 0;
	}
}

void reactImage::render(HDC hdc)
{
	if (_imgKey2 != "")
		IMAGEMANAGER->stretchRender(_imgKey2, hdc, _rc.left - _currentSize * 0.5f, _rc.top - _currentSize * 0.5f, 0, 0, _width + _currentSize, _height + _currentSize, _alpha);
	IMAGEMANAGER->stretchRender(_imgKey1, hdc, _rc.left - _currentSize * 0.5f, _rc.top - _currentSize * 0.5f, 0, 0, _width + _currentSize, _height + _currentSize);
}

void reactImage::CursorIn()
{
	_isCursorOn = true;
}

void reactImage::CursorOut()
{
	_isCursorOn = false;
}
