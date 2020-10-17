//implementation of Vec3.h
#include "Vec3.h"
#include <math.h>

Vec3::Vec3(float x, float y, float z)
{
  X = x;
  Y = y;
  Z = z;
}
Vec3::Vec3()
{
  X = 0;
  Y = 0;
}

Vec3 Vec3::operator+(const Vec3 otherVector) const //vector addition
{
  Vec3 result;
  result.X = X + otherVector.X;
  result.Y = Y + otherVector.Y;
  result.Z = Z + otherVector.Z;
  return result;
}

Vec3 Vec3::operator-(const Vec3 otherVector) const //vector subtraction
{
  Vec3 result;
  result.X = X - otherVector.X;
  result.Y = Y - otherVector.Y;
  result.Z = Z - otherVector.Z;
  return result;
}

bool Vec3::operator==(Vec3& otherVector) const
{
  return X == otherVector.X && Y == otherVector.Y && Z == otherVector.Z;
}

Vec3 Vec3::operator-() const //unary - means invert the vector
{
  Vec3 result(-X, -Y, -Z);
  return result;
}
