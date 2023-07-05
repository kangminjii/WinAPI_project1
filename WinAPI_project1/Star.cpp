#include "Star.h"
#include <cmath>
#define PI 3.141592

Star::Star(POINT R)
{
	center.x = R.x;
	center.y = R.y;
	radius = 50;
	direction = { 10, 10 };
}

Star::Star()
{
	center = { 0, 0 };
	radius = 50;
	direction = { 10, 10 };
}

void Star::SetPosition(int x, int y)
{
	center.x = x;
	center.y = y;
}

void Star::Update(RECT& r)
{
    if (center.x + radius >= r.right || center.x - radius <= r.left)
        direction.x *= -1;
    if (center.y + radius >= r.bottom || center.y - radius <= r.top)
        direction.y *= -1;

    center.x += direction.x;
    center.y += direction.y;
}

void Star::Draw(HDC hdc)
{
    double angle = 2 * PI / 10;

    POINT pt[10] = {};

    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            pt[i].x = center.x + radius * sin(angle * i);
            pt[i].y = center.y + radius * cos(angle * i);
        }

        if (i % 2 == 1)
        {
            pt[i].x = center.x + (radius / 2) * sin(angle * i);
            pt[i].y = center.y + (radius / 2) * cos(angle * i);
        }

    }

    Polygon(hdc, pt, 10);
}