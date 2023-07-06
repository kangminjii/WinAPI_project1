#pragma once
#include <Windows.h>

class CObject
{
protected:
	POINT center;
	int radius;
	POINT direction;//∫§≈Õ∑Œ

public:
	void virtual SetPosition(int x, int y) = 0;
	void virtual Update(RECT& r) = 0;
	void virtual Draw(HDC hdc) = 0;
};