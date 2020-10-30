#pragma once
//=============================================================
//	## progressBar ## (���α׷����� = ü�¹� = �ε��� ���)
//=============================================================

class progressBar 
{
private:
	image* _progressBarFront;		//ü�¹� �� �̹���(��Ʈ�����)
	image* _progressBarBack;		//ü�¹� �� �̹���(�������)
	float _x, _y;					//ü�¹� ��ġ��ǥ
	int _width;					//ü�¹� ���α���
	float _height;					//ü�¹� ���α���

public:
	void init(const char* frontImg, const char* backImg);
	void render(HDC hdc);

	//ü�¹� ������ �����ϱ�
	void setGauge(float maxHp, float currentHp, int x, int y);

};

