#pragma once

#include <vector>

#include "Point.h"
#include "Plane.h"
#include "Line.h"
#include "Polygon.h"

class Shape {
 public:
  Shape(std::vector<Polygon> polygons,
        MyDouble x = 0, MyDouble y = 0, MyDouble z = 0,
        MyDouble x_size = 1, MyDouble y_size = 1, MyDouble z_size = 1,
        MyDouble x_angle = 0, MyDouble y_angle = 0, MyDouble z_angle = 0,
        MyDouble center_x = 0, MyDouble center_y = 0, MyDouble center_z = 0);
  std::vector<Point> Intersection(const Line& l) const;

  Shape& operator+=(const Point& p);
  Shape& operator-=(const Point& p);

  Shape& Scale(const Point& center, const MyDouble& k);
  Shape& Scale(const Plane& pl, const MyDouble& k);
  Shape& Scale(const Line& axis, const MyDouble& k);

  Shape& Reflect(const Point& center);
  Shape& Reflect(const Plane& pl);
  Shape& Reflect(const Line& axis);

  Shape& Rotate(const Line& axis, const MyDouble& deg);

 private:
  std::vector<Polygon> polygons_;
};

class Cube: Shape {
 public:
  Cube(MyDouble x = 0, MyDouble y = 0, MyDouble z = 0,
       MyDouble x_size = 1, MyDouble y_size = 1, MyDouble z_size = 1,
       MyDouble x_angle = 0, MyDouble y_angle = 0, MyDouble z_angle = 0,
       MyDouble center_x = 0, MyDouble center_y = 0, MyDouble center_z = 0);
};