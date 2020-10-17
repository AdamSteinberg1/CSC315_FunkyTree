#pragma once
//class to clip a polygon
#include <vector>
#include "Polygon.h"

class Clipper
{
  private:
    int xMin, xMax, yMin, yMax;
    std::vector<Vec2> clipLeft(std::vector<Vec2> points);
    std::vector<Vec2> clipRight(std::vector<Vec2> points);
    std::vector<Vec2> clipBottom(std::vector<Vec2> points);
    std::vector<Vec2> clipTop(std::vector<Vec2> points);

  public:
    Clipper(int xMin, int xMax, int yMin, int yMax);
    Polygon clip(Polygon p);
};
