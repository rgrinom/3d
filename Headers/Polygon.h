#pragma once

#include <vector>
#include <fstream>

#include "Point.h"
#include "Plane.h"
#include "Line.h"

class Polygon {
 public:
  Polygon(const std::vector<Point>& points);
  bool Contains(const Point& p) const;
  Point operator[](size_t ind) const;
  Point& operator[](size_t ind);

  Point Intersection(const Line& l) const;
  MyDouble DistanceTo(const Point& p) const;

  Polygon& operator+=(const Point& p);
  Polygon& operator-=(const Point& p);

  Polygon& Scale(const Point& center, const MyDouble& k);
  Polygon& Scale(const Plane& pl, const MyDouble& k);
  Polygon& Scale(const Line& axis, const MyDouble& k);

  Polygon& Reflect(const Point& center);
  Polygon& Reflect(const Plane& pl);
  Polygon& Reflect(const Line& axis);

  Polygon& Rotate(const Line& axis, const MyDouble& deg);

 private:
  std::vector<Point> points_;

  bool SegmentContains(const Point& p1, const Point& p2, const Point& p) const;

  friend std::ostream& operator<<(std::ostream& out, const Polygon& poly);

  static std::random_device rd_;
  static std::mt19937 gen_;
  static std::uniform_int_distribution<> distr_;
};

std::ostream& operator<<(std::ostream& out, const Polygon& poly);