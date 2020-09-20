#include "stdafx.h"
#include "ForagerPlayer.h"

HRESULT ForagerPlayer::init()
{
	_rcForager = RectMakeCenter(100, 615, 30, 41);
	
	IMAGEMANAGER->addFrameImage("playerStop", "Images/이미지/플레이어/player_idle_frame.bmp", 120,112, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRUN", "Images/이미지/플레이어/player_run_frame.bmp", 160, 112, 4, 2, true, RGB(255, 0, 255));

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
	//가만히 있는 상태
	if (!INPUT->GetKey(VK_LEFT) || !INPUT->GetKey(VK_RIGHT))
	{
		_state = IDLE;
		_isMoveHorizon = false;
		_isMoveVertical = false;
	}
	//뛰어다니는 상태 (좌우 움직임)
	if (INPUT->GetKey(VK_LEFT) || INPUT->GetKey(VK_RIGHT))
	{
		_isMoveHorizon = true;
		_state = RUN;
		_isLeft = (INPUT->GetKey(VK_LEFT)) ? true : false;	//방향설정
	}
	//뛰어다니는 상태 (상하 움직임)
	if (INPUT->GetKey(VK_UP) || INPUT->GetKey(VK_DOWN))
	{
		_isMoveVertical = true;
		_state = RUN;
		_isUp = (INPUT->GetKey(VK_UP)) ? true : false;	//방향 설정
	}
}

void ForagerPlayer::playerMove()
{
	//플레이어 좌우 움직임 처리 
	if (_isMoveHorizon)
	{
		int applySpeed = (_isLeft) ? -3 : 3;

		//int applySpeed = (_isUp) ? -3 : 3;
		
		
		if (_rcForager.left >= 0)
		{
			OffsetRect(&_rcForager, applySpeed, 0);
		}
		//플레이어가 화면 왼쪽으로 안나가게끔 처리 
		else
		{
			_rcForager.left = 0;
			_rcForager.right = 80;
		}
		//플레이어가 화면 오른쪽으로 안나가게끔 처리 
		if (_rcForager.right >= 1300)
		{
			_rcForager.right = 1300;
			_rcForager.left = 1260;
		}
	}

	//플레이어 상하 움직임 처리 
	if (_isMoveVertical)
	{
		int applySpeed = (_isUp) ? -3 : 3;

		if (_rcForager.top >= 0)
		{
			OffsetRect(&_rcForager, 0, applySpeed);
		}
		//플레이어가 화면 위쪽으로 안나가게끔 처리 
		else
		{
			_rcForager.top = 0;
			_rcForager.bottom = 40;
		}
		//플레이어가 화면 아래쪽으로 안나가게끔 처리
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
