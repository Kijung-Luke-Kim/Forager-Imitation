#pragma once

class targetingBox
{
private:
	RECT _rcTargetBox;		// Ÿ���õ� ����� RC
	int _minSize;			// �� �ƿ� �ּ� ������
	int _maxSize;			// �� �� �ִ� ������
	int _currentSize;		// ���� �� ������
	int _count;				// �� ���� ���͹�
	int _currentCount;		// �� ���� ���͹� ī��Ʈ
	int _zoomSpeed;			// �� ���ǵ�

	bool _isTargetting;		// Ÿ���� ������ üũ
	bool _isZoomIn;			// ���� �������� �� �ƿ� �������� ����
	bool _isCursorOn;		// Ŀ���� �ö�� �������� üũ

public:

	HRESULT init();
	void update();
	void render(HDC hdc);

	void SetTarget(RECT rcTarget);
	void CursorOut();
	void RemoveTarget();



};
