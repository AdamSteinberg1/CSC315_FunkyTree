#include "Polygon.h"
#include "Tessellator.h"
#include "Clipper.h"
#include <algorithm>

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

void Polygon::addPoint(float x, float y)
{
  points.push_back(Vec2(x, y));
}

std::vector<Triangle> Polygon::tessellate()
{
    Tessellator t;
    return t.tessellate(*this);
}

Polygon Polygon::clip(int xMin, int xMax, int yMin, int yMax)
{
  Clipper c(xMin, xMax, yMin, yMax);
  return c.clip(*this);
}

//returns a new polygon where every point has been multiplied by the matrix trans
//converts each point into homogeneous coordinates, applies the transformation, and then converts each point back to two-dimensional vectors
Polygon Polygon::transform(Mat3 trans)
{
  std::vector<Vec2> newPoints;
  newPoints.reserve(points.size());

  for(int i =0; i < points.size(); i++)
  {
    Vec3 image = trans * points[i]; //implicit cast to homogeneous coordinate Vec3 occurs here
    newPoints.push_back(Vec2(image.X, image.Y));
  }

  return Polygon(newPoints);
}
