#pragma once

#include <vector>

#include "Point.h"
#include "Plane.h"
#include "Line.h"

class Segment {
 public:
  Segment(const Point& p1, const Point& p2);
  Segment(const std::vector<Point>& points);
  bool Contains(const Point& p) const;

 private:
  Point p1_, p2_;
};

class Polygon {
 public:
  Polygon(const std::vector<Point>& points);
  bool Contains(const Point& p) const;
  Point operator[](size_t ind) const;
  Point& operator[](size_t ind);

  Point Intersection(const Line& l) const;

  Polygon& Scale(const Point& center, const MyDouble& k);
  Polygon& Scale(const Plane& pl, const MyDouble& k);
  Polygon& Scale(const Line& axis, const MyDouble& k);

  Polygon& Reflect(const Point& center);
  Polygon& Reflect(const Plane& pl);
  Polygon& Reflect(const Line& axis);

  Polygon& Rotate(const Line& axis, const MyDouble& deg);

 private:
  std::vector<Point> points;
};