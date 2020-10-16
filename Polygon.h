#pragma once
//class for a polygon
#include <vector>
#include <list>
#include "Vec2.h"
#include "Triangle.h"
#include "Mat3.h"

class Polygon
{
  protected:
    std::vector<Vec2> points;

  public:
    Polygon();
    Polygon(std::vector<Vec2> v);
    Vec2 operator [](int i) const; //get the ith point of the polygon
    Vec2 & operator [](int i);     //set the ith point of the polygon
    std::vector<Triangle> tessellate();
    std::vector<Triangle> tessellateNew();
    std::vector<Vec2> getPoints();
    void addPoint(Vec2 point);
    void addPoint(int x, int y);
    Polygon transform(Mat3 trans);
};
