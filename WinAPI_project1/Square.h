#pragma once
#include <Windows.h>
class Square
{
private:
	POINT center;
	int radius;
	POINT direction;//���ͷ�

public:
	Square(POINT R);
	Square();
	void SetPosition(int x, int y);
	void Update(RECT& r);
	void Draw(HDC hdc);
};