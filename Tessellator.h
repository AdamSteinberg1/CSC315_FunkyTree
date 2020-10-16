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
    bool diagonalIntersect(std::vector<Vec2> local_points, int index);
    bool diagonalIntersect(LinkedList<Vec2> pointList);
    int sgn(int num);
    bool validEar(std::vector<Vec2> local_points, int index, int & winding);
    bool validEar(LinkedList<Vec2> & pointlist, int & winding);
    bool intersect(Vec2 startPoint1, Vec2 endPoint1, Vec2 startPoint2, Vec2 endPoint2);
    int det(int a, int b, int c, int d);

  public:
    Tessellator();
    std::vector<Triangle> tessellate(Polygon p);
    std::vector<Triangle> tessellateNew(Polygon p);
};
