//implementation of Triangle.h
#include "Triangle.h"
#include <math.h>

Triangle::Triangle()
{
  //do nothing!
}

Triangle::Triangle(Vec2 a, Vec2 b, Vec2 c)
{
  points.push_back(a);
  points.push_back(b);
  points.push_back(c);
}

Vec2 Triangle::get_a()
{
  return points[0];
}

Vec2 Triangle::get_b()
{
  return points[1];
}

Vec2 Triangle::get_c()
{
  return points[2];
}
