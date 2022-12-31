#pragma once

#include <random>
#include <cmath>

#include "Point.h"
#include "Plane.h"

class Polygon;

class Line {
 public:
  Line() = default;
  Line(const Point& p1, const Point& p2);
  Line(const Plane& pl1, const Plane& pl2);
  bool Contains(const Point& p) const;
  std::pair<Plane, Plane> GetParameters() const;
  Point Collinear() const;
  Point Normal(const Point& p) const;
  MyDouble Distance(const Point& p) const;

  Point Intersection(const Plane& pl) const;
  Point Intersection(const Line& l) const;
  Point Intersection(const Polygon& poly) const;

 private:
  Plane pl1_, pl2_;

  static std::random_device rd_;
  static std::mt19937 gen_;
  static std::uniform_int_distribution<> distr_;
};