#include"singletonBase.h"

#pragma once
class cameraManager : public singletonBase<cameraManager>
{

private:
	int _posX, _posY;				// ���� ���� ī�޶��� ��ġ
	int _targetX, _targetY;			// ���� ���� Ÿ�� ��ġ (�÷��̾�)
	float _anchorX, _anchorY;		// ī�޶� �߽� ��Ŀ (���� ȭ�� �߽�)
	int _cameraWidth, _cameraHeight;// ī�޶� ���� ���� ������ (���� ����)
	int _minX, _minY, _maxX, _maxY;	// ī�޶� �̵� ���� ����
	RECT _rcCamBound;				// �÷��̾� �߽� ������ ��Ʈ
	RECT _rcCamRealBound;			// ī�޶� �̵� ��Ʈ
public:
	// �ʱ�ȭ
	void init(int posX, int posY, int targetX, int targetY, float anchorX, float anchorY, int width, int height, int minX, int minY, int maxX, int maxY);
	
	// Ÿ�� ����
	void targetFollow(int targetX, int targetY);
	// ���콺 Ŀ���� ����
	void camFocusCursor(POINT ptMouse);

	// �׽�Ʈ�� ������ ������ ���� (�׽�Ʈ ������ ������ ��)
	void render(HDC hdc);

	// �����ǥ
	int GetRelativeX(int posX);
	int GetRelativeY(int posY);
	
	// ���콺 �����ǥ (���콺�� ���� ��ǥ�� ȭ�鿡 �׷�����, Ŭ���� ���� �����ǥ�� ���ͼ� Ÿ�ϰ� �浹���� �Ǵ�)
	POINT GetMouseRelativePos(POINT ptMouse);

	// ī�޶� ���� ���� ��Ʈ ������.
	RECT GetCameraRect() { return _rcCamBound; }
};

