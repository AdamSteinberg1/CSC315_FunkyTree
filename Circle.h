#pragma once
//a circle class that extends Polygon
#include <vector>
#include "Vec2.h"
#include "Polygon.h"

class Circle : public Polygon //a Circle is a Polygon with many sides, so it inherits
{
  public:
    Circle(int radius, Vec2 center);
    Circle(int radius, Vec2 center, double threshold);
  private:
    std::vector<Vec2> createOctant(int radius);
    static bool compareVectors (Vec2 p1, Vec2 p2);
    void removeDuplicates(std::vector<Vec2> & v);
    void addPoint(std::vector<Vec2> & v, Vec2 p, double threshold);
};
