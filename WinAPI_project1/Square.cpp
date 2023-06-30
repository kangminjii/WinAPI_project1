#include "Square.h"

Square::Square(POINT R)
{
	center = { R.x, R.y };
	width = 100;
	height = 100;
	direction = { 10, 10 };
}

Square::Square()
{
	center = { 0, 0 };
	width = 10;
	height = 10;
	direction = { 10, 10 };
}

void Square::SetPosition(int x, int y)
{
	center = { x, y };
}

void Square::Update(RECT& r)
{
	if (center.x + width / 2 >= r.right || center.x - width / 2 <= r.left)
		direction.x *= -1;
	if (center.y + height / 2 >= r.bottom || center.y - height / 2 <= r.top)
		direction.y *= -1;

	center.x += direction.x;
	center.y += direction.y;
}

void Square::Draw(HDC hdc)
{
	Rectangle(hdc, center.x - width / 2, center.y - height / 2, center.x + width / 2, center.y + height / 2);
}
