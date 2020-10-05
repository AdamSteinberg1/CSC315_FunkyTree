#pragma once
//class for three-dimensional vectors using ints
class Vec3
{
  public:
    int X;
    int Y;
    int Z;
    Vec3(int x, int y, int z);
    Vec3();
    Vec3 operator+(const Vec3 otherVector) const;
    Vec3 operator-(const Vec3 otherVector) const;
    bool operator==(Vec3& otherVector) const;
    Vec3 operator-() const;
};
