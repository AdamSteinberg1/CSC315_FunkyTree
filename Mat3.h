//class for a 3D matrix
#pragma once
#include "Vec2.h"
#include "Vec3.h"

class Mat3 //a Circle is a Polygon with many sides, so it inherits
{
  public:
    Mat3();
    Mat3(float inarr[3][3]);
    float entries[3][3];
    static Mat3 createRotation(float angle, Vec2 center);
    static Mat3 createScale(float factor, Vec2 center);
    static Mat3 createTranslation(float x, float y);
    static Mat3 createReflectionY(Vec2 center);
    Mat3 operator*(const Mat3 otherMatrix) const;
    Vec3 operator*(const Vec3 v) const;
    void printMatrix();
};
