#pragma once

#include <vector>

#include "Point.h"
#include "Plane.h"
#include "Line.h"
#include "Polygon.h"

class Shape {
 public:
  Shape(const std::vector<Polygon>& polygons,
        const Point& size = Point(1, 1, 1),
        const Point& position = Point(0, 0, 0),
        const Point& rotation = Point(0, 0, 0),
        const Point& center = Point(0, 0, 0));
  std::vector<Point> Intersection(const Line& l) const;

  Shape& operator+=(const Point& p);
  Shape& operator-=(const Point& p);
  Shape& MoveForward(const MyDouble& distance);
  Shape& MoveLeft(const MyDouble& distance);
  Shape& MoveUp(const MyDouble& distance);

  Shape& Scale(const Point& center, const MyDouble& k);
  Shape& Scale(const Plane& pl, const MyDouble& k);
  Shape& Scale(const Line& axis, const MyDouble& k);

  Shape& Reflect(const Point& center);
  Shape& Reflect(const Plane& pl);
  Shape& Reflect(const Line& axis);

  Shape& Rotate(const Line& axis, const MyDouble& deg);
  Shape& Rotate(const Point& p, const MyDouble& deg);
  Shape& RotateAroundForwardAxis(const MyDouble& deg);
  Shape& RotateAroundLeftAxis(const MyDouble& deg);
  Shape& RotateAroundUpAxis(const MyDouble& deg);

  Line GetForwardAxis();
  Line GetLeftAxis();
  Line GetUpAxis();

 private:
  std::vector<Polygon> polygons_;
  Point center_;
  Point forward_, left_, up_;
};

class Cube: public Shape {
 public:
  Cube(const Point& size = Point(1, 1, 1),
       const Point& position = Point(0, 0, 0),
       const Point& rotation = Point(0, 0, 0),
       const Point& center_position = Point(0, 0, 0));
};