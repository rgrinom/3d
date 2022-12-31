#pragma once

#include <cmath>
#include <vector>

#include "MyDouble.h"

class Line;
class Plane;

namespace constants {
  const MyDouble kInf(1000000000);
  const MyDouble kPi(3.14159265359);
}

MyDouble DegToRad(MyDouble deg);
MyDouble RadToDeg(MyDouble rad);

struct Point {
  MyDouble x, y, z;

  Point(MyDouble x = 0, MyDouble y = 0, MyDouble z = 0);
  Point(std::vector<MyDouble> parameters);

  Point operator-() const;
  Point& Normalize();

  Point& operator+=(const Point& rhs);
  Point& operator-=(const Point& rhs);
  Point& operator*=(const MyDouble& rhs);
  Point& operator/=(const MyDouble& rhs);

  MyDouble Length() const;
  MyDouble Distance(const Point& rhs) const;

  Point& Scale(const Point& center, const MyDouble& k);
  Point& Scale(const Line& axis, const MyDouble& k);
  Point& Scale(const Plane& pl, const MyDouble& k);

  Point& Reflect(const Point& center);
  Point& Reflect(const Plane& pl);
  Point& Reflect(const Line& axis);

  Point& Rotate(const Line& axis, const MyDouble& deg);
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);
bool operator<(const Point& lhs, const Point& rhs);

Point operator+(const Point& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Point& rhs);
Point operator*(const Point& lhs, const MyDouble& rhs);
Point operator/(const Point& lhs, const MyDouble& rhs);

std::istream& operator>>(std::istream& in, Point& p);
std::ostream& operator<<(std::ostream& out, const Point& p);

MyDouble DotProduct(const Point& lhs, const Point& rhs);
Point CrossProduct(const Point& lhs, const Point& rhs);