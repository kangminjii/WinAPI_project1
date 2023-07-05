#pragma once
#include <Windows.h>
class Star
{
private:
	POINT center;
	int radius;
	POINT direction;// ���ͷ�

public:
	Star(POINT R);
	Star();
	void SetPosition(int x, int y);
	void Update(RECT& r);
	void Draw(HDC hdc);
};