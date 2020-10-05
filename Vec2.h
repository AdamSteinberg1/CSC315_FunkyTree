#pragma once
#include "Vec3.h"
//class for two-dimensional vectors using ints
class Vec2
{
  public:
    int X;
    int Y;
    Vec2(int x, int y);
    Vec2();
    int winding(const Vec2 otherVector) const;
    int dot(const Vec2 otherVector) const;
    double magnitude() const;
    double angleBetween(const Vec2 otherVector) const;
    Vec2 operator+(const Vec2 otherVector) const;
    Vec2 operator-(const Vec2 otherVector) const;
    bool operator==(Vec2& otherVector) const;
    Vec2 operator-() const;
    operator Vec3() const;
};
