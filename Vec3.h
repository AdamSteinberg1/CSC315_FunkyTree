#pragma once
//class for three-dimensional vectors using ints
class Vec3
{
  public:
    float X;
    float Y;
    float Z;
    Vec3(float x, float y, float z);
    Vec3();
    Vec3 operator+(const Vec3 otherVector) const;
    Vec3 operator-(const Vec3 otherVector) const;
    bool operator==(Vec3& otherVector) const;
    Vec3 operator-() const;
};
