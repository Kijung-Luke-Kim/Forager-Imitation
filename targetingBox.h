#pragma once

class targetingBox
{
private:
	int _targetID;			// Ÿ���õ� �༮�� ���̵�.
	RECT _rcTargetBox;		// Ÿ���õ� ����� RC
	int _minSize;			// �� �ƿ� �ּ� ������
	int _maxSize;			// �� �� �ִ� ������
	int _currentSize;		// ���� �� ������
	int _count;				// �� ���� ���͹�
	int _currentCount;		// �� ���� ���͹� ī��Ʈ
	int _zoomSpeed;			// �� ���ǵ�

	bool _isRelative;		// �����ǥ�� �ʿ�����
	bool _isTargetting;		// Ÿ���� ������ üũ
	bool _isZoomIn;			// ���� �������� �� �ƿ� �������� ����
	bool _isCursorOn;		// Ŀ���� �ö�� �������� üũ

public:

	HRESULT init();
	void update();
	void render(HDC hdc);

	void SetTarget(RECT rcTarget, int moveDistance, int id = 0, int narrow = 0, bool isRelative = false);
	void CursorOut();
	void RemoveTarget();



};
