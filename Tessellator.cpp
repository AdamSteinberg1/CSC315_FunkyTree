#include "Tessellator.h"
#include "Polygon.h"
#include "LinkedList.h"
#include <algorithm>


Tessellator::Tessellator() {}

std::vector<Triangle> Tessellator::tessellate(Polygon p)
{
  std::vector<Triangle> triangles;

  std::vector<Vec2> points = p.getPoints();

  if(isClockwise(points)) //if the points are not defined in a CCW manner, then reverse them
    std::reverse(points.begin(), points.end());

  int n = points.size();
  while(n > 3)
  {
    for(int i = 0; i < n; i++)
    {
      int winding;
      if(validEar(points, i, winding)) //ccw winding and the diagonal does not intersect any line segments
      {
          Triangle t (points[i], points[(i+1)%n], points[(i+2)%n]);
          triangles.push_back(t);

          //remove middle point
          points.erase(points.begin() + (i + 1)%n);
          n--;
          break; //start over
      }
      else if(winding == 0)
      {
          points.erase(points.begin() + (i + 1)%n);
          n--;
          break; //start over
      }
      if(i == n-1)
      {
        //we cannot find any points to remove, so we must take drastic action
        //remove first point
        points.erase(points.begin());
        n--;
        break; //start over
      }
    }
  }
  Triangle finalTriangle (points[0], points[1], points[2]);
  triangles.push_back(finalTriangle);

  return triangles;
}

std::vector<Triangle> Tessellator::tessellateNew(Polygon p)
{
  std::vector<Triangle> triangles;

  std::vector<Vec2> points = p.getPoints();

  if(isClockwise(points)) //if the points are not defined in a CCW manner, then reverse them
    std::reverse(points.begin(), points.end());

  LinkedList<Vec2> pointList;
  for(Vec2 point : points)
  {
    pointList.insert(point);
  }

  int n = points.size();
  while(n > 3)
  {
    for(int i = 0; i < n; i++)
    {
      int winding;
      if(validEar(points, i, winding)) //ccw winding and the diagonal does not intersect any line segments
      {
          Triangle t (points[i], points[(i+1)%n], points[(i+2)%n]);
          triangles.push_back(t);

          //remove middle point
          points.erase(points.begin() + (i + 1)%n);
          n--;
          break; //start over
      }
      else if(winding == 0)
      {
          points.erase(points.begin() + (i + 1)%n);
          n--;
          break; //start over
      }
      if(i == n-1)
      {
        //we cannot find any points to remove, so we must take drastic action
        //remove first point
        points.erase(points.begin());
        n--;
        break; //start over
      }
    }
  }
  Triangle finalTriangle (points[0], points[1], points[2]);
  triangles.push_back(finalTriangle);

  return triangles;
}

//returns true if the points are defined in a clockwise manner
bool Tessellator::isClockwise(std::vector<Vec2> v)
{
    int sum = 0;
    int n = v.size();
    for(int i = 0; i < n; i++)
    {
      sum += (v[(i+1)%n].X - v[i].X) * (v[(i+1)%n].Y + v[i].Y);
    }
    return sum > 0;
}

//returns true if the diagonal line segment intersects any other line segments
bool Tessellator::diagonalIntersect(std::vector<Vec2> points, int index)
{
  int n = points.size();
  for(int i = 0; i < n; i++)
  {

    //first make sure that we don't perform the check if any of the points are the same
    if(i == index)
      continue;
    if(i == (index + 2)%n)
      continue;
    if((i+1)%n == index)
      continue;
    if((i+1)%n == (index+2)%n)
      continue;


    if(intersect(points[index], points[(index+2)%n], points[i], points[(i+1)%n]))
    {
      return true;
    }
  }
  return false;
}

//returns 1 if num is postiive, -1 if num is negative, and 0 if num is 0
int Tessellator::sgn(int num)
{
    if (num > 0)
      return 1;
    if (num < 0)
      return -1;
    return 0;
}

//check all conditions that would allow us to remove an ear from our polygon
bool Tessellator::validEar(std::vector<Vec2> points, int index, int & winding)
{
  int n = points.size();

  //check that it has a ccw winding
  Vec2 line1 = points[index] - points[(index+1)%n];
  Vec2 line2 = points[(index+2)%n] - points[(index+1)%n];
  winding = line1.winding(line2);
  if (winding >= 0)
  {
    return false;
  }

  //check that the diagonal does not intersect anything
  if(diagonalIntersect(points, index))
  {
    return false;
  }

  //check the special case where it trys to draws a line that is outside the polygon
  Vec2 nextLine = points[(index+3)%n] - points[(index+2)%n];
  Vec2 imminentLine = points[index] - points[(index + 2)%n];
  if(imminentLine.angleBetween(-line2) > nextLine.angleBetween(-line2))
  {
    if(sgn(imminentLine.winding(line2)) == sgn(nextLine.winding(line2))) //they must be turning the same way for it to be invalid
    {
      return false;
    }
  }

  return true;
}

//returns true if two line segments intersect
bool Tessellator::intersect(Vec2 startPoint1, Vec2 endPoint1, Vec2 startPoint2, Vec2 endPoint2)
{
  int den = det(endPoint1.X - startPoint1.X, -(endPoint2.X - startPoint2.X), endPoint1.Y - startPoint1.Y,  -(endPoint2.Y - startPoint2.Y));
  if(den == 0) //parallel line segments
    return false;

  double u_a = det(startPoint2.X - startPoint1.X, -(endPoint2.X - startPoint2.X), startPoint2.Y - startPoint1.Y, -(endPoint2.Y - startPoint2.Y)) / double(den);
  double u_b = det(endPoint1.X - startPoint1.X, startPoint2.X - startPoint1.X, endPoint1.Y - startPoint1.Y, startPoint2.Y - startPoint1.Y) / double(den);

  return u_a > 0 && u_a < 1 && u_b > 0 && u_b < 1;
}

//determinate of 2x2 matrix
int Tessellator::det(int a, int b, int c, int d)
{
  /*
    | a b |
    | c d |
  */
  return a*d - b *c;
}
