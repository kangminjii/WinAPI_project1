#pragma once
#include "framework.h"
#include <iostream>
using namespace std;


class CObject
{
protected:
    POINT x, y;
    double speed;
    double direction;
    string type; // Ÿ��(��, ��, �簢��)

public:
    virtual void Update();
    virtual int Draw(string type); // �ڱ� �ڽ��� �׸��� �Լ�
    virtual BOOL Collision() = 0;
    // �� �� �Լ�
};


