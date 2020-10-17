#include "Clipper.h"

Clipper::Clipper(int xMin, int xMax, int yMin, int yMax)
{
  this->xMin = xMin;
  this->xMax = xMax;
  this->yMin = yMin;
  this->yMax = yMax;
}

Polygon Clipper::clip(Polygon p)
{
  std::vector<Vec2> points = p.getPoints();
  points = clipLeft(points);
  points = clipRight(points);
  points = clipBottom(points);
  points = clipTop(points);
  return Polygon(points);
}

std::vector<Vec2> Clipper::clipLeft(std::vector<Vec2> points)
{
  std::vector<Vec2> result;
  int n = points.size();
  for(int i = 0; i < n; i++)
  {
    Vec2 p1 = points[i];
    Vec2 p2 = points[(i+1)%n];
    float slope = p1.X == p2.X ? 0 : (p1.Y-p2.Y)/(p1.X-p2.X); //avoid divide by zero error

    if(p1.X > xMin)
    {
      if(p2.X > xMin)
      {
        //both points inside
        result.push_back(p2);
      }
      else
      {
        //only first point inside
        Vec2 intersect;
        intersect.X = xMin;
        intersect.Y = p2.Y + (xMin - p2.X) * slope;
        result.push_back(intersect);
      }
    }
    else
    {
      if(p2.X > xMin)
      {
        //only second point inside
        Vec2 intersect;
        intersect.X = xMin;
        intersect.Y = p2.Y + (xMin - p2.X) * slope;
        result.push_back(intersect);
        result.push_back(p2);
      }
    }
  }
  return result;
}

std::vector<Vec2> Clipper::clipRight(std::vector<Vec2> points)
{
  std::vector<Vec2> result;
  int n = points.size();
  for(int i = 0; i < n; i++)
  {
    Vec2 p1 = points[i];
    Vec2 p2 = points[(i+1)%n];
    float slope = p1.X == p2.X ? 0 : (p1.Y-p2.Y)/(p1.X-p2.X); //avoid divide by zero error

    if(p1.X < xMax)
    {
      if(p2.X < xMax)
      {
        //both points inside
        result.push_back(p2);
      }
      else
      {
        //only first point inside
        Vec2 intersect;
        intersect.X = xMax;
        intersect.Y = p2.Y + (xMax - p2.X) * slope;
        result.push_back(intersect);
      }
    }
    else
    {
      if(p2.X < xMax)
      {
        //only second point inside
        Vec2 intersect;
        intersect.X = xMax;
        intersect.Y = p2.Y + (xMax - p2.X) * slope;
        result.push_back(intersect);
        result.push_back(p2);
      }
    }
  }
  return result;
}

std::vector<Vec2> Clipper::clipBottom(std::vector<Vec2> points)
{
  std::vector<Vec2> result;
  int n = points.size();
  for(int i = 0; i < n; i++)
  {
    Vec2 p1 = points[i];
    Vec2 p2 = points[(i+1)%n];
    float slope = p1.X == p2.X ? 0 : (p1.Y-p2.Y)/(p1.X-p2.X); //avoid divide by zero error

    if(p1.Y > yMin)
    {
      if(p2.Y > yMin)
      {
        //both points inside
        result.push_back(p2);
      }
      else
      {
        //only first point inside
        Vec2 intersect;
        intersect.Y = yMin;
        if(p1.X != p2.X)
          intersect.X = p2.X + (yMin - p2.Y) / slope;
        else
          intersect.X = p2.X;
        result.push_back(intersect);
      }
    }
    else
    {
      if(p2.Y > yMin)
      {
        //only second point inside
        Vec2 intersect;
        intersect.Y = yMin;
        if(p1.X != p2.X)
          intersect.X = p2.X + (yMin - p2.Y) / slope;
        else
          intersect.X = p2.X;
        result.push_back(intersect);
        result.push_back(p2);
      }
    }
  }
  return result;
}

std::vector<Vec2> Clipper::clipTop(std::vector<Vec2> points)
{
  std::vector<Vec2> result;
  int n = points.size();
  for(int i = 0; i < n; i++)
  {
    Vec2 p1 = points[i];
    Vec2 p2 = points[(i+1)%n];
    float slope = p1.X == p2.X ? 0 : (p1.Y-p2.Y)/(p1.X-p2.X); //avoid divide by zero error

    if(p1.Y < yMax)
    {
      if(p2.Y < yMax)
      {
        //both points inside
        result.push_back(p2);
      }
      else
      {
        //only first point inside
        Vec2 intersect;
        intersect.Y = yMax;
        if(p1.X != p2.X)
          intersect.X = p2.X + (yMax - p2.Y) / slope;
        else
          intersect.X = p2.X;
        result.push_back(intersect);
      }
    }
    else
    {
      if(p2.Y < yMax)
      {
        //only second point inside
        Vec2 intersect;
        intersect.Y = yMax;
        if(p1.X != p2.X)
          intersect.X = p2.X + (yMax - p2.Y) / slope;
        else
          intersect.X = p2.X;
        result.push_back(intersect);
        result.push_back(p2);
      }
    }
  }
  return result;
}
