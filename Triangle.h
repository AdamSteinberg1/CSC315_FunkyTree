#pragma once
#include <vector>
#include "Vec2.h"
//class for a triangle with points a, b, c

class Triangle
{
  public:
    Triangle();
    Triangle(Vec2 a, Vec2 b, Vec2 c);
    Vec2 operator [](int i) const; //get the ith point of the triangle
    Vec2 & operator [](int i);     //set the ith point of the triangle
  private:
    std::vector<Vec2> points;
};
