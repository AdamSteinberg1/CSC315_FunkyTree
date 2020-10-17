#include "Mat3.h"
#include <math.h>
#include <stdio.h>


//no args contructor makes identity matrix
Mat3::Mat3()
{
  for(int i =0; i < 3; i++)
  {
    for(int j= 0; j < 3; j++)
    {
      if(i == j)
        entries[i][j] = 1.0;
      else
        entries[i][j] = 0.0;
    }
  }
}

//fills the entries in the matrix with the argument array
Mat3::Mat3(float inarr[3][3])
{
  for(int i =0; i < 3; i++)
  {
    for(int j= 0; j < 3; j++)
    {
      entries[i][j] = inarr[i][j];
    }
  }
}

//creates a counterclockwise rotation matrix
Mat3 Mat3::createRotation(float angle, Vec2 center)
{
  float values[3][3] =
  {
    {cos(angle), -sin(angle), 0},
    {sin(angle),  cos(angle), 0},
    {0,           0,          1}
  };
  Mat3 rotate(values);
  Mat3 trans = createTranslation(-center.X, -center.Y); //translation matrix
  Mat3 trans_inverse = createTranslation(center.X, center.Y); //inverse of translation matrix
  //we translate to the center, rotate, then translate back
  return trans_inverse * rotate * trans;
}

//creates a scaling matrix
Mat3 Mat3::createScale(float factor, Vec2 center)
{
  float values[3][3]  =
  {
    {factor, 0, 0},
    {0, factor, 0},
    {0,      0, 1}
  };
  Mat3 scale(values);
  Mat3 trans = createTranslation(-center.X, -center.Y); //translation matrix
  Mat3 trans_inverse = createTranslation(center.X, center.Y); //inverse of translation matrix
  //we translate to the center, scale, then translate back
  return trans_inverse * scale * trans;
}

//creates a reflection matrix across the y-axis where center is the origin
Mat3 Mat3::createReflectionY(Vec2 center)
{
  float values[3][3]  =
  {
    {-1, 0, 0},
    { 0, 1, 0},
    { 0, 0, 1}
  };
  Mat3 refl(values);
  Mat3 trans = createTranslation(-center.X, -center.Y); //translation matrix
  Mat3 trans_inverse = createTranslation(center.X, center.Y); //inverse of translation matrix
  //we translate to the center, reflect, then translate back
  return trans_inverse * refl * trans;
}

Mat3 Mat3::createTranslation(float x, float y)
{
  float values[3][3]  =
  {
    {1, 0, x},
    {0, 1, y},
    {0, 0, 1}
  };
  return Mat3(values);
}

//matrix multiplication
Mat3 Mat3::operator*(const Mat3 otherMatrix) const
{
  float values[3][3];
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      float sum = 0;
      for (int k = 0; k < 3; k++)
      {
        sum += entries[i][k] * otherMatrix.entries[k][j];
      }
      values[i][j] = sum;
    }
  }
  return Mat3(values);
}

//multiplies a matrix time a vector
//all float values are rounded to ints
Vec3 Mat3::operator*(const Vec3 v) const
{
  Vec3 result;
  result.X = entries[0][0] * v.X + entries[0][1] * v.Y +entries[0][2] * v.Z;
  result.Y = entries[1][0] * v.X + entries[1][1] * v.Y +entries[1][2] * v.Z;
  result.Z = entries[2][0] * v.X + entries[2][1] * v.Y +entries[2][2] * v.Z;
  return result;
}

void Mat3::printMatrix()
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      printf("%f ", entries[i][j]);
    }
    printf("\n");
  }
}
