#include "stdafx.h"
#include "productionManager.h"



void productionManager::init()
{
	count = 0;
}

void productionManager::relese()
{
}

void productionManager::update()
{
	count_increase();
	cout << _production.size() << endl;;
}

void productionManager::render(HDC hdc)
{
	for (int i = 0; i < _production.size(); i++) {
		if (_production[i]->countStart) {
			IMAGEMANAGER->alphaRender(_production[i]->image_name, hdc, _production[i]->alpha);
		}
	}
}

void productionManager::count_increase()
{
	for (int i = 0; i < _production.size(); i++) {
		if (_production[i]->countStart) {
			if (_production[i]->count > 0) {
				_production[i]->alpha++;
				if (_production[i]->alpha > 255) {
					_production[i]->alpha = 0;
					_production[i]->count--;
				}
			}
			else {
				_production[i]->countStart = false;
				_production[i]->image_name = "";
			}
		}

	}
}

//ī��Ʈ�� ����

void productionManager::settion(RECT rc)
{
	if (isCilck(rc) == -1)
	{
		tagProduction* _pro = new tagProduction;
		_pro->rc = rc;
		_pro->count = 0;
		_pro->alpha = 0;
		_pro->image_name = "";
		_pro->countStart = false;
		_production.push_back(_pro);
	}
}//ó�� e�� �������� ����ġ ����.


int productionManager::isCilck(RECT rc)
{
	for (int i = 0; i < _production.size(); i++) {
		if (_production[i]->rc.left == rc.left && _production[i]->rc.top == rc.top && _production[i]->rc.bottom == rc.bottom&&_production[i]->rc.right == rc.right) {
			return i;
		}
	}
	return -1;
}//���� �ǹ����� �˻�
void productionManager::isCount(RECT rc)
{
	int cilck = isCilck(rc);
	if (cilck == -1) {
		
	}
	else {
		
	}
}

