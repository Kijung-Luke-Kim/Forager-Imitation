#include "stdafx.h"
#include "ForagerPlayer.h"

HRESULT ForagerPlayer::init()
{
	_rcForager = RectMakeCenter(100, 615, 30, 41);
	
	IMAGEMANAGER->addFrameImage("playerStop", "Images/�̹���/�÷��̾�/player_idle_frame.bmp", 120,112, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRUN", "Images/�̹���/�÷��̾�/player_run_frame.bmp", 160, 112, 4, 2, true, RGB(255, 0, 255));

	_foragerIdle = IMAGEMANAGER->findImage("playerStop");
	_foragerRun = IMAGEMANAGER->findImage("playerRUN");

	_count = 0;
	_index = 0;

	_isLeft = false;
	_isUp = false;
	_isMoveHorizon = false;
	_isMoveVertical = false;
	_isRun = false;


	return S_OK;
}

void ForagerPlayer::release()
{

}

void ForagerPlayer::update()
{
	animation();
	PlayerControll();
	playerMove();
	playerLookingDirection();
}

void ForagerPlayer::render()
{
	switch (_state)
	{
	case IDLE:
		IMAGEMANAGER->frameRender("playerStop", getMemDC(), _rcForager.left, _rcForager.top);
		break;
	case RUN:
		IMAGEMANAGER->frameRender("playerRUN", getMemDC(), _rcForager.left, _rcForager.top);
		break;
	}
	
}

void ForagerPlayer::animation()
{
	switch (_state)
	{
	case IDLE:
		if (_isLeft)
		{
			_foragerIdle->setFrameY(1);
			_foragerIdle->setFrameX(2);
		}
		else
		{
			_foragerIdle->setFrameY(0);
			_foragerIdle->setFrameX(0);
		}
		break;
	case RUN:
		if (_isLeft)
		{
			_count++;
			_foragerRun->setFrameY(1);
			if (_count % 5 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 3;
				}
				_foragerRun->setFrameX(_index);
			}
		}
		else
		{
			_count++;
			_foragerRun->setFrameY(0);
			if (_count % 5 == 0)
			{
				_index++;
				if (_index > 3)
				{
					_index = 0;
				}
				_foragerRun->setFrameX(_index);
			}
		}
		break;
	}
}

void ForagerPlayer::PlayerControll()
{
	//������ �ִ� ����
	if (!INPUT->GetKey(VK_LEFT) || !INPUT->GetKey(VK_RIGHT))
	{
		_state = IDLE;
		_isMoveHorizon = false;
		_isMoveVertical = false;
	}
	//�پ�ٴϴ� ���� (�¿� ������)
	if (INPUT->GetKey(VK_LEFT) || INPUT->GetKey(VK_RIGHT))
	{
		_isMoveHorizon = true;
		_state = RUN;
		_isLeft = (INPUT->GetKey(VK_LEFT)) ? true : false;	//���⼳��
	}
	//�پ�ٴϴ� ���� (���� ������)
	if (INPUT->GetKey(VK_UP) || INPUT->GetKey(VK_DOWN))
	{
		_isMoveVertical = true;
		_state = RUN;
		_isUp = (INPUT->GetKey(VK_UP)) ? true : false;	//���� ����
	}
}

void ForagerPlayer::playerMove()
{
	//�÷��̾� �¿� ������ ó�� 
	if (_isMoveHorizon)
	{
		int applySpeed = (_isLeft) ? -3 : 3;

		//int applySpeed = (_isUp) ? -3 : 3;
		
		
		if (_rcForager.left >= 0)
		{
			OffsetRect(&_rcForager, applySpeed, 0);
		}
		//�÷��̾ ȭ�� �������� �ȳ����Բ� ó�� 
		else
		{
			_rcForager.left = 0;
			_rcForager.right = 80;
		}
		//�÷��̾ ȭ�� ���������� �ȳ����Բ� ó�� 
		if (_rcForager.right >= 1300)
		{
			_rcForager.right = 1300;
			_rcForager.left = 1260;
		}
	}

	//�÷��̾� ���� ������ ó�� 
	if (_isMoveVertical)
	{
		int applySpeed = (_isUp) ? -3 : 3;

		if (_rcForager.top >= 0)
		{
			OffsetRect(&_rcForager, 0, applySpeed);
		}
		//�÷��̾ ȭ�� �������� �ȳ����Բ� ó�� 
		else
		{
			_rcForager.top = 0;
			_rcForager.bottom = 40;
		}
		//�÷��̾ ȭ�� �Ʒ������� �ȳ����Բ� ó��
		if (_rcForager.bottom >= 640)
		{
			_rcForager.top = 600;
			_rcForager.bottom = 640;
		}
	}
}

void ForagerPlayer::playerLookingDirection()
{
	int forgaerCenter = (_rcForager.left + _rcForager.right) / 2;

	if (forgaerCenter < _ptMouse.x)
	{
		_isLeft = false;
	}
	else
	{
		_isLeft = true;
	}
}
