#include "Mat3.h"
#include <math.h>

//no args contructor make a matrix of all 0s
Mat3::Mat3()
{
  for(int i =0; i < 3; i++)
  {
    for(int j= 0; j < 3; j++)
    {
      entries[i][j] = 0.0;
    }
  }
}

//fills the entries in the matrix with the argument array
Mat3::Mat3(double inarr[3][3])
{
  for(int i =0; i < 3; i++)
  {
    for(int j= 0; j < 3; j++)
    {
      entries[i][j] = inarr[i][j];
    }
  }
}

Mat3 Mat3::createRotation(double angle)
{
  double values[3][3] =
  {
    {cos(angle), -sin(angle), 0},
    {sin(angle), cos(angle), 0},
    {0,0,1}
  };
  return Mat3(values);
}

Mat3 Mat3::createScale(double factor)
{
  double values[3][3]  =
  {
    {factor, 0, 0},
    {0, factor, 0},
    {0,0,1}
  };
}
Mat3 Mat3::operator*(const Mat3 otherMatrix) const
{
  double values[3][3];
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      double sum = 0;
      for (int k = 0; k < 3; k++)
      {
        sum += entries[i][k] * otherMatrix.entries[k][j];
      }
      values[i][j] = sum;
    }
  }
}
