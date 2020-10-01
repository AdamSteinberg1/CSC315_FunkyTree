#include "Circle.h"
#include <math.h>
#include <algorithm>
#include <stdio.h>


Circle::Circle(int radius, Vec2 center)
{
  for(Vec2 point : createOctant(radius))
  {
    printf("here\n");
    //create all the reflections of the octant
    points.push_back(point);
    points.push_back(Vec2(-point.X, point.Y));
    points.push_back(Vec2(point.X, -point.Y));
    points.push_back(Vec2(-point.X, -point.Y));
    points.push_back(Vec2(point.Y, point.X));
    points.push_back(Vec2(-point.Y, point.X));
    points.push_back(Vec2(point.Y, -point.X));
    points.push_back(Vec2(-point.Y, -point.X));
  }
  std::sort (points.begin(), points.end(), compareVectors);
  removeDuplicates(points);

  //translate circle from origin to center
  for(int i = 0; i < points.size(); i++)
  {
    points[i] = points[i] + center;
  }
}

//constructs a section of a circle
//points with an angle greater than threshold are not included
Circle::Circle(int radius, Vec2 center, double threshold)
{
  for(Vec2 point : createOctant(radius))
  {
    //create all the reflections of the octant
    addPoint(points, point, threshold);
    addPoint(points, Vec2(-point.X, point.Y), threshold);
    addPoint(points, Vec2(point.X, -point.Y), threshold);
    addPoint(points, Vec2(-point.X, -point.Y), threshold);
    addPoint(points, Vec2(point.Y, point.X), threshold);
    addPoint(points, Vec2(-point.Y, point.X), threshold);
    addPoint(points, Vec2(point.Y, -point.X), threshold);
    addPoint(points, Vec2(-point.Y, -point.X), threshold);
  }
  std::sort (points.begin(), points.end(), compareVectors);
  removeDuplicates(points);

  //translate circle from origin to center
  for(int i = 0; i < points.size(); i++)
  {
    points[i] = points[i] + center;
  }
}

std::vector<Vec2> Circle::createOctant(int radius) //creates all the points in the second octant
{
  std::vector<Vec2> octant;
  int x, y;
  float d;

  x = 0;
  y = radius;
  d = 5.0 /4.0 - radius;
  octant.push_back(Vec2(x,y));
  while(y>x)
  {
    if (d <= 0) //choose east
    {
      d += x * 2.0 + 3;
      x++;
    }
    else //choose SE
    {
      d += (x-y) * 2.0 + 5;
      x++;
      y--;
    }
    octant.push_back(Vec2(x,y));
  }
  return octant;
}

//compares vectors by their ccw angle from the x axis
bool Circle::compareVectors (Vec2 p1, Vec2 p2)
{
   double theta1 = atan2(p1.Y, p1.X);
   double theta2 = atan2(p2.Y, p2.X);
   return theta1 < theta2;
}

void Circle::addPoint(std::vector<Vec2> & v, Vec2 p, double threshold)
{
  double theta = atan2(p.Y, p.X);
  if(fabs(theta) <= threshold)
  {
    v.push_back(p);
  }
}

//removes duplicates assuming v is already sorted
void Circle::removeDuplicates(std::vector<Vec2> & v)
{
    for (int i = 0; i < v.size(); i++)
    {
      if(i+1 >= v.size())
        break;

      while(v[i] == v[i+1])
      {
        v.erase(v.begin()+i);

        if(i+1 >= v.size())
          break;
      }
    }
}
