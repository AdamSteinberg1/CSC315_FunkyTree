#pragma once
//class for a polygon
#include <vector>
#include "Vec2.h"
#include "Triangle.h"

class Polygon
{
  private:
    std::vector<Vec2> points;
    bool isClockwise(std::vector<Vec2> v);
    bool diagonalIntersect(std::vector<Vec2> local_points, int index);
    int sgn(int num);
    bool validEar(std::vector<Vec2> local_points, int index, int & winding);
    bool intersect(Vec2 startPoint1, Vec2 endPoint1, Vec2 startPoint2, Vec2 endPoint2);
    int det(int a, int b, int c, int d);


  public:
    Polygon();
    Polygon(std::vector<Vec2> v);
    std::vector<Triangle> tesselate();
};