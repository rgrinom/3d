#pragma once

#include <cmath>
#include <fstream>

#include "Point.h"
#include "Plane.h"

class Polygon;

class Line {
 public:
  Point p0, a;

  Line() = default;
  Line(const Point& p1, const Point& p2);
  Point Normal(const Point& p) const;
  MyDouble Distance(const Point& p) const;
  bool Contains(const Point& p) const;
  Point Proection(const Point& p) const;

  Point Intersection(const Plane& pl) const;
  Point Intersection(const Line& l) const;
  Point Intersection(const Polygon& poly) const;
};

std::istream& operator>>(std::istream& in, Line& l);
std::ostream& operator<<(std::ostream& out, const Line& l);