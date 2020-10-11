#pragma once
#include "singletonBase.h"

#define FLOATINGTEXT_MAX 10

class TextManager : public singletonBase<TextManager>
{
private:
	struct tagFloatingText {
		int x, y;
		string str;
		int count;
		COLORREF color;
		COLORREF bgColor;
		bool isAppear;
	};

private:
	int _count;
	int _timer;
	int _size;
	tagFloatingText _floatingTexts[FLOATINGTEXT_MAX];

public:
	void init();
	void release();
	void update();
	void render(HDC hdc);

	// str : ����� �ؽ�Ʈ  (����Ʈ Test)
	// ptPos : ����� ��ġ	(����Ʈ 10, 10)
	// size : ��Ʈ ������	(������ 15)
	// align = 0 : ���� ����, 1 : ��� ����, 2 : ������ ���� (����Ʈ 0)
	// color : ��Ʈ ���� (����Ʈ ���)
	// isBoundary : �ؽ�Ʈ �׸��� Ȱ��ȭ (���� ����) (����Ʈ ����)
	// colorBoundary : �׸��� ���� (����Ʈ ������)
	void ShowText(HDC hdc, string str = "Test", POINT ptPos = { 10, 10 }, int size = 15, int align = 0, COLORREF color = RGB(255, 255, 255), bool isBoundary = false, COLORREF colorBoundary = RGB(0, 0, 0), int interval = 3);

	void ShowFloatingText(string str, POINT ptPos, COLORREF color = RGB(255, 255, 255), COLORREF bgColor = RGB(0,0,0));
};

