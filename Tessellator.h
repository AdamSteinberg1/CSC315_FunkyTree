#pragma once
//class to do tessellation
#include <vector>
#include "Vec2.h"
#include "Triangle.h"

class Polygon; //have to forward declare to appease the compiler

class Tessellator
{
  private:
    bool isClockwise(std::vector<Vec2> v);
    bool diagonalIntersect(std::vector<Vec2> points, int index);
    int sgn(float num);
    bool validEar(std::vector<Vec2> points, int index, float & winding);
    bool intersect(Vec2 startPoint1, Vec2 endPoint1, Vec2 startPoint2, Vec2 endPoint2);
    float det(float a, float b, float c, float d);

  public:
    Tessellator();
    std::vector<Triangle> tessellate(Polygon p);
};
