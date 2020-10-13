#include "Polygon.h"
#include <algorithm>
#include <stdio.h>
#include <GL/glut.h>


Polygon::Polygon()
{
  //do nothing!
}

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

std::vector<Triangle> Polygon::tesselate()
{

    std::vector< Triangle > triangles;

    std::vector<Vec2> local_points = points; //we need a local copy because we don't want to destroy our points list



    int n = local_points.size();
    while(n > 3)
    {

      if(isClockwise(local_points)) //if the points are not defined in a CCW manner, then reverse them
        std::reverse(local_points.begin(), local_points.end());

      for(int i = 0; i < n; i++)
      {
        int winding;
        if(validEar(local_points, i, winding)) //ccw winding and the diagonal does not intersect any line segments
        {
            Triangle t (local_points[i], local_points[(i+1)%n], local_points[(i+2)%n]);
            triangles.push_back(t);

            //remove middle point
            local_points.erase(local_points.begin() + (i + 1)%n);
            n--;
            break; //start over
        }
        else if(winding == 0)
        {
            local_points.erase(local_points.begin() + (i + 1)%n);
            n--;
            break; //start over
        }
        if(i == n-1)
        {
          //remove first point
          local_points.erase(local_points.begin());
          n--;
          break; //start over
        }
      }


    }
    Triangle finalTriangle (local_points[0], local_points[1], local_points[2]);
    triangles.push_back(finalTriangle);

    return triangles;
}

std::vector<Triangle> Polygon::tesselateNew()
{
    std::vector< Triangle > triangles;

    //we need a local copy because we don't want to destroy our points list
    std::list<Vec2> local_points;
    for(int i =0; i < points.size(); i++)
    {
      list.push_back(points[i]);
    }



    while(local_points.size() > 3)
    {

      if(isClockwise(local_points)) //if the points are not defined in a CCW manner, then reverse them
        local_points.reverse():

      for(std::list<int>::iterator it=local_points.begin(); it != local_points.end(); it++)
      {
        int winding;
        if(validEar(local_points, it, winding)) //ccw winding and the diagonal does not intersect any line segments
        {
            //have to do lots of checks to make the linked list act circular
            Vec2 p1, p2, p3;
            p1 = *it;
            if(it + 1 == local_points.end())
            {
              p2 = *(local_points.begin());
              p3 = *(local_points.begin() + 1);
            }
            if(it + 2 == local_points.end())
            {
              p2 = *(it+1);
              p3 = *(local_points.begin());
            }
            else
            {
              p2 = *(it+1);
              p3 = *(it+2);
            }

            Triangle t (p1, p2, p3);
            triangles.push_back(t);

            //remove middle point
            if(it+1 != l.end())
            {
              local_points.erase(local_points.begin() + it + 1);
            }
            else
            {
              local_points.erase(local_points.begin());
            }
            break; //start over
        }
        else if(winding == 0)
        {
          //remove middle point
          if(it+1 != l.end())
          {
            local_points.erase(local_points.begin() + it + 1);
          }
          else
          {
            local_points.erase(local_points.begin());
          }
          break; //start over
        }
        if(it == local_points.end() - 1)
        {
          //remove first point
          local_points.erase(local_points.begin());
          break; //start over
        }
      }


    }
    Vec2 p1 = local_points.pop_back();
    Vec2 p2 = local_points.pop_back();
    Vec2 p3 = local_points.pop_back();
    Triangle finalTriangle (p1, p2, p3);
    triangles.push_back(finalTriangle);

    return triangles;
}

//returns true if the points are defined in a clockwise manner
bool Polygon::isClockwise(std::vector<Vec2> v)
{
  int sum = 0;
  int n = v.size();
  for(int i = 0; i < n; i++)
  {
    sum += (v[(i+1)%n].X - v[i].X) * (v[(i+1)%n].Y + v[i].Y);
  }
  return sum > 0;
}
//returns true if the points are defined in a clockwise manner
bool Polygon::isClockwise(std::list<Vec2> l)
{
  int sum = 0;
  for (std::list<Vec2>::iterator it=l.begin(); it != l.end(); it++)
  {
    if(it + 1 != l.end())
    {
      sum += ((it+1)->X - it->X) * ((it+1)->Y - it->Y);
    }
    else
    {
      sum += (l.begin()->X - it->X) * (l.begin()->Y - it->Y);
    }
  }
  return sum > 0;
}

//returns true if the diagonal line segment intersects any other line segments
bool Polygon::diagonalIntersect(std::vector<Vec2> local_points, int index)
{
  int n = local_points.size();
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


    if(intersect(local_points[index], local_points[(index+2)%n], local_points[i], local_points[(i+1)%n]))
    {
      return true;
    }
  }
  return false;
}

int Polygon::sgn(int num) //returns 1 if num is postiive, -1 if num is negative, and 0 if num is 0
{
  if (num > 0) return 1;
  if (num < 0) return -1;
  return 0;
}


//check all conditions that would allow us to remove an ear from our polygon
bool Polygon::validEar(std::vector<Vec2> local_points, int index, int & winding)
{
  int n = local_points.size();

  //check that it has a ccw winding
  Vec2 line1 = local_points[index] - local_points[(index+1)%n];
  Vec2 line2 = local_points[(index+2)%n] - local_points[(index+1)%n];
  winding = line1.winding(line2);
  if (winding >= 0)
  {
    return false;
  }

  //check that the diagonal does not intersect anything
  if(diagonalIntersect(local_points, index))
  {
    return false;
  }

  //check the special case where it trys to draws a line that is outside the polygon
  Vec2 nextLine = local_points[(index+3)%n] - local_points[(index+2)%n];
  Vec2 imminentLine = local_points[index] - local_points[(index + 2)%n];
  if(imminentLine.angleBetween(-line2) > nextLine.angleBetween(-line2))
  {
    if(sgn(imminentLine.winding(line2)) == sgn(nextLine.winding(line2))) //they must be turning the same way for it to be invalid
    {
      return false;
    }
  }

  return true;
}
//check all conditions that would allow us to remove an ear from our polygon
bool Polygon::validEar(std::list<Vec2> local_points, std::list<Vec2>::iterator it, int & winding)
{
  int n = local_points.size();

  //check that it has a ccw winding
  Vec2 line1 = local_points[index] - local_points[(index+1)%n];
  Vec2 line2 = local_points[(index+2)%n] - local_points[(index+1)%n];
  winding = line1.winding(line2);
  if (winding >= 0)
  {
    return false;
  }

  //check that the diagonal does not intersect anything
  if(diagonalIntersect(local_points, index))
  {
    return false;
  }

  //check the special case where it trys to draws a line that is outside the polygon
  Vec2 nextLine = local_points[(index+3)%n] - local_points[(index+2)%n];
  Vec2 imminentLine = local_points[index] - local_points[(index + 2)%n];
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
bool Polygon::intersect(Vec2 startPoint1, Vec2 endPoint1, Vec2 startPoint2, Vec2 endPoint2)
{
  int den = det(endPoint1.X - startPoint1.X, -(endPoint2.X - startPoint2.X), endPoint1.Y - startPoint1.Y,  -(endPoint2.Y - startPoint2.Y));
  if(den == 0) //parallel line segments
    return false;

  double u_a = det(startPoint2.X - startPoint1.X, -(endPoint2.X - startPoint2.X), startPoint2.Y - startPoint1.Y, -(endPoint2.Y - startPoint2.Y)) / double(den);
  double u_b = det(endPoint1.X - startPoint1.X, startPoint2.X - startPoint1.X, endPoint1.Y - startPoint1.Y, startPoint2.Y - startPoint1.Y) / double(den);

  return u_a >= 0 && u_a <= 1 && u_b >= 0 && u_b <= 1;
}

//determinate of 2x2 matrix
int Polygon::det(int a, int b, int c, int d)
{
  /*
    | a b |
    | c d |
  */
  return a*d - b *c;
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
