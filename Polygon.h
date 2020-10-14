#pragma once
//class for a polygon
#include <vector>
#include <list>
#include "Vec2.h"
#include "Triangle.h"
#include "Mat3.h"

class Polygon
{
  private:
    bool isClockwise(std::vector<Vec2> v);
    bool diagonalIntersect(std::vector<Vec2> local_points, int index);
    bool diagonalIntersect(std::list<Vec2> local_points, std::list<Vec2>::iterator it);
    int sgn(int num);
    bool validEar(std::vector<Vec2> local_points, int index, int & winding);
    bool validEar(std::list<Vec2> local_points, int & winding, std::list<Vec2>::iterator it);
    bool intersect(Vec2 startPoint1, Vec2 endPoint1, Vec2 startPoint2, Vec2 endPoint2);
    int det(int a, int b, int c, int d);

  protected:
    std::vector<Vec2> points;

  public:
    Polygon();
    Polygon(std::vector<Vec2> v);
    Vec2 operator [](int i) const; //get the ith point of the polygon
    Vec2 & operator [](int i);     //set the ith point of the polygon
    std::vector<Triangle> tesselate();
    std::vector<Triangle> tesselateNew();
    std::vector<Vec2> getPoints();
    void addPoint(Vec2 point);
    void addPoint(int x, int y);
    Polygon transform(Mat3 trans);
};
