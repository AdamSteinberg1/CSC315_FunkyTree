//class for a 3D matrix
#pragma once
#include <vector>
#include "Vec2.h"
#include "Polygon.h"

class Mat3 //a Circle is a Polygon with many sides, so it inherits
{
  public:
    Mat3();
    Mat3(int[][]);
  private:
    int[][] entries;
};
