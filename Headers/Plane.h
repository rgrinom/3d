#pragma once

#include "Point.h"
#include "SoLE.h"

class Line;

class Plane {
 public:
  Plane() = default;
  Plane(const Point& p1, const Point& p2, const Point& p3);

  MyDouble Distance(const Point& p) const;
  bool Contains(const Point& p) const;
  Point Normal() const;
  std::vector<MyDouble> GetParameters() const;

  Line Intersection(const Plane& pl) const;
  Point Intersection(const Line& l) const;

 private:
  MyDouble a_ = 0, b_ = 0, c_ = 0, d_ = 0;
};