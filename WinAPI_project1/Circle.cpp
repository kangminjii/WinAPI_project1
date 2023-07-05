#include "Circle.h"

Circle::Circle(POINT C)
{
	center = { C.x, C.y };
	radius = 20;
	direction = { C.x, C.y };
}

Circle::Circle()
{
	center = { 0,0 };
	radius = 20;
	direction = { 10,10 };
}

void Circle::SetPosition(int x, int y)
{
	center.x = x;
	center.y = y;
}

void Circle::Update(RECT &r)
{
	if (center.x + radius >= r.right || center.x - radius <= r.left)
		direction.x *= -1;
	if (center.y + radius >= r.bottom || center.y - radius <= r.top)
		direction.y *= -1;

	center.x += direction.x;
	center.y += direction.y;
}

void Circle::Draw(HDC hdc)
{
	Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}

BOOL Circle::Collision(HDC hdc)
{
	/*if (LengthPts(pt1, pt2) < radius)  return TRUE;
		return FALSE;
	}*/
	return true;
}
