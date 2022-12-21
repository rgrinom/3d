#pragma once

#include <cmath>

#include "MyDouble.h"

struct Point {
  MyDouble x, y, z;

  Point operator-() const;
  void Normalize();

  Point& operator+=(const Point& rhs);
  Point& operator-=(const Point& rhs);
  Point& operator*=(const MyDouble& rhs);
  Point& operator/=(const MyDouble& rhs);

  MyDouble Length() const;
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);

Point operator+(const Point& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Point& rhs);
Point operator*(const Point& lhs, const MyDouble& rhs);
Point operator/(const Point& lhs, const MyDouble& rhs);

MyDouble Distance(const Point& lhs, const Point& rhs);

MyDouble DotProduct(const Point& lhs, const Point& rhs);
Point CrossProduct(const Point& lhs, const Point& rhs);