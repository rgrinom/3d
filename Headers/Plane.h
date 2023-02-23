#pragma once

#include <fstream>

#include "Point.h"
#include "SoLE.h"

class Line;

class Plane {
 public:
  Point p0, u, v;

  Plane() = default;
  Plane(const Point& p1, const Point& p2, const Point& p3);

  Point Normal() const;
  Point Normal(const Point& p) const;
  MyDouble Distance(const Point& p) const;
  MyDouble SignedDistance(const Point& p) const;
  bool Contains(const Point& p) const;
  Point Proection(const Point& p) const;

  Line Intersection(const Plane& pl) const;
  Point Intersection(const Line& l) const;
};

std::istream& operator>>(std::istream& in, Plane& pl);
std::ostream& operator<<(std::ostream& out, const Plane& pl);