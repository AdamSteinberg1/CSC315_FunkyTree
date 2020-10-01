//implementation of Triangle.h
#include "Triangle.h"
#include <math.h>

Triangle::Triangle()
{
}

Triangle::Triangle(Vec2 a, Vec2 b, Vec2 c)
{
  points.push_back(a);
  points.push_back(b);
  points.push_back(c);
}

//get the ith point of the polygon
Vec2 Triangle::operator [](int i) const
{
  return points[i];
}

//set the ith point of the polygon
Vec2 & Triangle::operator [](int i)
{
  return points[i];
}
