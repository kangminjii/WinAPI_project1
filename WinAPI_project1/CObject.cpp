#include "CObject.h"

void CObject::Update()
{
}

int CObject::Draw(string type)
{
    if (type == "Circle")
    {
        return 1;
    }
    else if (type == "Square")
    {
        return 2;
    }
    else
    {
        // star
        return 3;
    }
}

BOOL CObject::Collision()
{
    return 0;
}
