#pragma once
#include "Vec3.h"
//class for two-dimensional vectors using ints
class Vec2
{
  public:
    float X;
    float Y;
    Vec2(float x, float y);
    Vec2();
    float winding(const Vec2 otherVector) const;
    float dot(const Vec2 otherVector) const;
    double magnitude() const;
    double angleBetween(const Vec2 otherVector) const;
    Vec2 operator+(const Vec2 otherVector) const;
    Vec2 operator-(const Vec2 otherVector) const;
    bool operator==(Vec2& otherVector) const;
    Vec2 operator-() const;
    operator Vec3() const;
};
