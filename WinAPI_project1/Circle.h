#pragma once
#include <Windows.h>
#include "CObject.h"

class Circle : public CObject
{
public:
	Circle(POINT C);
	Circle();
	void virtual SetPosition(int x, int y);
	void virtual Update(RECT& r);
	void virtual Draw(HDC hdc);

	BOOL Collision(HDC hdc);
};