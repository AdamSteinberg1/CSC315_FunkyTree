#include "Polygon.h"
#include "LinkedList.h"
#include "Tessellator.h"
#include <algorithm>
#include <stdio.h>

Polygon::Polygon(){}

Polygon::Polygon(std::vector<Vec2> v)
{
  points = v;
}

//get the ith point of the polygon
Vec2 Polygon::operator [](int i) const
{
  return points[i];
}

//set the ith point of the polygon
Vec2 & Polygon::operator [](int i)
{
  return points[i];
}

std::vector<Vec2> Polygon::getPoints()
{
  return points;
}

void Polygon::addPoint(Vec2 point)
{
  points.push_back(point);
}

void Polygon::addPoint(int x, int y)
{
  points.push_back(Vec2(x, y));
}

std::vector<Triangle> Polygon::tessellate()
{
    Tessellator t;
    return t.tessellate(*this);
}

std::vector<Triangle> Polygon::tessellateNew()
{
    Tessellator t;
    return t.tessellate(*this);
}

//returns a new polygon where every point has been multiplied by the matrix trans
//converts each point into homogeneous coordinates, applies the transformation, and then converts each point back to two-dimensional vectors
Polygon Polygon::transform(Mat3 trans)
{
  std::vector<Vec2> newPoints = points;
  for(int i =0; i < newPoints.size(); i++)
  {
    Vec3 image = trans * newPoints[i]; //implicit cast to homogeneous coordinate Vec3 occurs here
    newPoints[i] = Vec2(image.X, image.Y);
  }
  return Polygon(newPoints);
}
