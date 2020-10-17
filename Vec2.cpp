//implementation of Vec2.h
#include "Vec2.h"
#include <math.h>

Vec2::Vec2(float x, float y)
{
  X = x;
  Y = y;
}
Vec2::Vec2()
{
  X = 0;
  Y = 0;
}

//returns the z component of the cross product: thisVector X otherVector
float Vec2::winding(const Vec2 otherVector) const
{
  return (X * otherVector.Y - Y * otherVector.X);
}


float Vec2::dot(const Vec2 otherVector) const
{
  return X * otherVector.X + Y * otherVector.Y;
}

double Vec2::magnitude() const
{
  return sqrt(X*X + Y*Y);
}

double Vec2::angleBetween(const Vec2 otherVector) const
{
  return acos(dot(otherVector) / (magnitude() * otherVector.magnitude())); //in radians
}

Vec2 Vec2::operator+(const Vec2 otherVector) const //vector addition
{
  Vec2 result;
  result.X = X + otherVector.X;
  result.Y = Y + otherVector.Y;
  return result;
}

Vec2 Vec2::operator-(const Vec2 otherVector) const //vector subtraction
{
  Vec2 result;
  result.X = X - otherVector.X;
  result.Y = Y - otherVector.Y;
  return result;
}

bool Vec2::operator==(Vec2& otherVector) const
{
  return X == otherVector.X && Y == otherVector.Y;
}

Vec2 Vec2::operator-() const //unary - means invert the vector
{
  Vec2 result(-X, -Y);
  return result;
}

//when trying to cast Vec2 into Vec3, convert it to a homogeneous coordinate
Vec2::operator Vec3() const
{
  return Vec3(X, Y, 1);
}
