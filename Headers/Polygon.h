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
  std::vector<Point> points;

  Polygon(const std::vector<Point>& points);
  bool Contains(const Point& p) const;
};

//---------------------------------Intersections-----------------------------
Point Intersection(const Polygon& poly, const Line& l);
Point Intersection(const Line& l, const Polygon& poly);

//------------------------------------Scales----------------------------------
void Scale(Polygon& poly, const Point& center, const MyDouble& k);
void Scale(Polygon& poly, const Plane& pl, const MyDouble& k);
void Scale(Polygon& poly, const Line& axis, const MyDouble& k);

//-----------------------------------Reflections------------------------------
void Reflect(Polygon& poly, const Point& center);
void Reflect(Polygon& poly, const Plane& pl);
void Reflect(Polygon& poly, const Line& axis);

//------------------------------------Rotations-------------------------------
void Rotate(Polygon& poly, const Line& axis, const MyDouble& deg);