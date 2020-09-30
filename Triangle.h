#pragma once
#include <vector>
#include "Vec2.h"
//class for a triangle with points a, b, c

class Triangle
{
  public:
    Triangle();
    Triangle(Vec2 a, Vec2 b, Vec2 c);
    Vec2 get_a();
    Vec2 get_b();
    Vec2 get_c();

  private:
    std::vector<Vec2> points;
};
