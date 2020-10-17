#pragma once
//class for a polygon
#include <vector>
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
    std::vector<Vec2> getPoints();
    void addPoint(Vec2 point);
    void addPoint(float x, float y);
    Polygon transform(Mat3 trans);
    Polygon clip(int xMin, int xMax, int yMin, int yMax);

};
