#pragma once

#include <random>
#include <cmath>

#include "Point.h"
#include "Plane.h"

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

 private:
  Plane pl1_, pl2_;

  static std::random_device rd_;
  static std::mt19937 gen_;
  static std::uniform_int_distribution<> distr_;
};

//----------------------------------Intersections-----------------------------
Line Intersection(const Plane& pl1, const Plane& pl2);
Point Intersection(const Plane& pl, const Line& l);
Point Intersection(const Line& l, const Plane& pl);
Point Intersection(const Line& l1, const Line& l2);

//------------------------------------Scales----------------------------------
Point& Scale(Point& p, const Point& center, const MyDouble& k);
Point& Scale(Point& p, const Plane& pl, const MyDouble& k);
Point& Scale(Point& p, const Line& axis, const MyDouble& k);

//-----------------------------------Reflections------------------------------
Point& Reflect(Point& p, const Point& center);
Point& Reflect(Point& p, const Plane& pl);
Point& Reflect(Point& p, const Line& axis);

//------------------------------------Rotations-------------------------------
namespace constants {
  const MyDouble kPi(3.14159265359);
}

MyDouble DegToRad(MyDouble deg);
MyDouble RadToDeg(MyDouble rad);
Point& Rotate(Point& p, const Line& axis, const MyDouble& deg);