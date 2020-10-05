//class for a 3D matrix
#pragma once
#include "Vec2.h"

class Mat3 //a Circle is a Polygon with many sides, so it inherits
{
  public:
    Mat3();
    Mat3(double inarr[3][3]);
    static Mat3 createRotation(double angle);
    static Mat3 createScale(double factor);
    Mat3 operator*(const Mat3 otherMatrix) const;
    double entries[3][3];
    printMatrix();
};
