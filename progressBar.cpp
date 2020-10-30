#include "stdafx.h"
#include "progressBar.h"

void progressBar::init(const char * frontImg, const char * backImg)
{
	//ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = IMAGEMANAGER->findImage(frontImg);
	_progressBarBack = IMAGEMANAGER->findImage(backImg);
	_width = 0;
}


void progressBar::render(HDC hdc)
{
	if (CAMERA->movelimit) {
		//������ �Ǵ� ������ ���ؼ� ������ �Ǵϱ� ������� ���� ��Ų��
		_progressBarBack->render(hdc, (_x) * CAMERA->GetZoom(), _y * CAMERA->GetZoom());
		//�տ� �������� ü�¹� �̹���
		_progressBarFront->render(hdc, (_x + 4) * CAMERA->GetZoom(), (_y + 5) * CAMERA->GetZoom(), 0, 0, _width, 10);
	}
}

//ü�¹� ������ �����ϱ�
void progressBar::setGauge(float maxHp, float currentHp, int x, int y)
{
	_width = (currentHp / maxHp) * (float)_progressBarBack->getWidth();
	_x = x + 3;
	_y = y;
}
