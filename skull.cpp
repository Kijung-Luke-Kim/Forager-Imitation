#include "stdafx.h"
#include "skull.h"


HRESULT skull::init()
{
	
	skullMoveCount = 0;
	skullIdleCount = 0;
	skullAttackRange = 100;
	return S_OK;
}

void skull::update()
{
	skullAnimation();
	
	switch (_state)
	{
	case STAY:
		skullMove();
		break;
	case ATTACK:
		break;
	case APPEAR:
		break;
	}
	if (_state != APPEAR) {
		canAttackCheck();
	}
	skullLookDirection();

}

void skull::render(HDC hdc)
{
	if (0 < currentHp && currentHp < maxHp) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.bottom + 16));
		_hpBar.render(hdc);
	}
	switch (_state)
	{
	case STAY:
		IMAGEMANAGER->frameRender("skull", hdc, CAMERA->GetRelativeX(rc.left - 13 ),
			CAMERA->GetRelativeY(rc.top - 10) , objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case ATTACK:
		IMAGEMANAGER->frameRender("skullAttack", hdc, CAMERA->GetRelativeX(rc.left -53),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case APPEAR:
		IMAGEMANAGER->frameRender("skullAppear", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	}
}

//�͸����� �������̷� ������
void skull::skullMove()
{
	if (!isAngle)
	{
		_angle = RANDOM->range(0.0f, 360.0f);
		enemyMoving = true;
		isAngle = true;
		skullMoveCount = 0;
	}

	if (skullIdleCount < 50 && enemyMoving == false && isAngle)
		skullIdleCount++;
		
	else if (skullIdleCount>= 50 && enemyMoving == false && isAngle){
		isAngle = false;
		skullIdleCount = 0;
	}

	if (enemyMoving)
	{
		if (skullMoveCount < 50)
		{
			skullMoveCount++;
			x += cosf(_angle*(PI / 180))*enemySpeedX;
			y += -sinf(_angle*(PI / 180))*enemySpeedY;
			rc = RectMakeCenter(x, y, 25, 25);
		}
		else
		{
			enemyMoving = false;
			skullIdleCount = 0;
		}
	}
}

void skull::canAttackCheck()
{
	if (abs(_target->rc.left - rc.left) <= skullAttackRange && abs(_target->rc.top - rc.top) <= skullAttackRange)
		_state = ATTACK;
	else
		_state = STAY;
}

void skull::skullAnimation()
{
	switch (_state)
	{
		//�ذ� �ٴ��
	case STAY:
		if (isLeft)
		{
			objFrameY = 1;
			objFrameX = _index;
			if (_count++ % 10 == 0)
			{
				if (_index-- <= 0)
					_index = 4;
			}
		}
		else
		{
			objFrameY = 0;
			objFrameX = _index;
			if (_count++ % 10 == 0)
			{
				if (_index++ > 5)
					_index = 0;
			}
		}
		break;
		//�ذ� ������ ����.
	case APPEAR:
		objFrameY = 0;
		objFrameX = _index;
		if (_count++ % 30 == 0)
		{
			if (_index++ > 4)
			{
				_index = 0;
				_state = STAY;
			}
		}
		break;
		//�ذ� ����
	case ATTACK:
		if (isLeft)
		{
			objFrameY = 1;
			objFrameX = _index;
			if (_count++ % 10 == 0)
			{
				if (_index-- <= 0)
					_index = 4;		//���� 2�ؾߵǴµ� 2���� ���� �ø����� ������ ������;;
			}
		}
		else
		{
			objFrameY = 0;
			objFrameX = _index;
			if (_count++ % 10 == 0)
			{
				if (_index++ > 4)
				{
					_index = 0;
				}

			}
		}
		break;
	}
}

void skull::skullLookDirection()
{
	if (_state == STAY || _state == ATTACK)
	{
		if (rc.right > _target->rc.right && rc.left > _target->rc.left)
			isLeft = true;
		else
			isLeft = false;
	}
}

