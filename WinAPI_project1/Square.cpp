#include "Square.h"

Square::Square(POINT R)
{
	center = { R.x, R.y };
	radius = 25;
	direction = { 10, 10 };
}

Square::Square()
{
	center = { 0, 0 };
	radius = 25;
	direction = { 10, 10 };
}

void Square::SetPosition(int x, int y)
{
	center = { x, y };
}

void Square::Update(RECT& r)
{
	if (center.x + radius >= r.right || center.x - radius <= r.left)
		direction.x *= -1;
	if (center.y + radius >= r.bottom || center.y - radius <= r.top)
		direction.y *= -1;

	center.x += direction.x;
	center.y += direction.y;
}

void Square::Draw(HDC hdc)
{
	Rectangle(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}
