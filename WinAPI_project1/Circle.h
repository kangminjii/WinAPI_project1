#pragma once
#include <Windows.h>
class Circle
{
private:
	POINT center;
	int radius;
	POINT direction;//∫§≈Õ∑Œ

public:
	Circle(POINT C);
	Circle();
	void SetPosition(int x, int y);
	void Update(RECT& r);
	void Draw(HDC hdc);

	BOOL Collision(HDC hdc);
};