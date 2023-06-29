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
    string type; // 타입(원, 별, 사각형)

public:
    virtual void Update();
    virtual int Draw(string type); // 자기 자신을 그리는 함수
    virtual BOOL Collision() = 0;
    // 그 외 함수
};


