#include "../Headers/Figures.h"

//----------------------------------Shape-------------------------------------
Shape::Shape(std::vector<Polygon> polygons,
             MyDouble x_size, MyDouble y_size, MyDouble z_size,
             MyDouble x, MyDouble y, MyDouble z,
             MyDouble x_angle, MyDouble y_angle, MyDouble z_angle,
             MyDouble center_x, MyDouble center_y, MyDouble center_z)
    : polygons_(polygons) {

  Plane x_scale(Point(0, 0, 0), Point(0, 1, 0), Point(0, 0, 1));
  Plane y_scale(Point(0, 0, 0), Point(1, 0, 0), Point(0, 0, 1));
  Plane z_scale(Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0));
  Scale(x_scale, x_size);
  Scale(y_scale, y_size);
  Scale(z_scale, z_size);

  Point pos(x, y, z);
  Point center(center_x, center_y, center_z);

  Line x_spin(center, center + Point(1, 0, 0));
  Line y_spin(center, center + Point(0, 1, 0));
  Line z_spin(center, center + Point(0, 0, 1));
  Rotate(x_spin, x_angle);
  Rotate(y_spin, y_angle);
  Rotate(z_spin, z_angle);

  *this += pos - center;
}

std::vector<Point> Shape::Intersection(const Line& l) const {
  std::vector<Point> ret;
  for (size_t i = 0; i < polygons_.size(); ++i) {
    Point cur_intersection = polygons_[i].Intersection(l);
    if (cur_intersection != constants::kNotAPoint) {
      ret.push_back(cur_intersection);
    }
  }
  return ret;
}

Shape& Shape::operator+=(const Point& p) {
  for (size_t i = 0; i < polygons_.size(); ++i) {
    polygons_[i] += p;
  }
  return *this;
}

Shape& Shape::operator-=(const Point& p) {
  for (size_t i = 0; i < polygons_.size(); ++i) {
    polygons_[i] -= p;
  }
  return *this;
}

Shape& Shape::Scale(const Point& center, const MyDouble& k) {
  for (size_t i = 0; i < polygons_.size(); ++i) {
    polygons_[i].Scale(center, k);
  }
  return *this;
}

Shape& Shape::Scale(const Plane& pl, const MyDouble& k) {
  for (size_t i = 0; i < polygons_.size(); ++i) {
    polygons_[i].Scale(pl, k);
  }
  return *this;
}

Shape& Shape::Scale(const Line& axis, const MyDouble& k) {
  for (size_t i = 0; i < polygons_.size(); ++i) {
    polygons_[i].Scale(axis, k);
  }
  return *this;
}

Shape& Shape::Reflect(const Point& center) { return Scale(center, -1); }
Shape& Shape::Reflect(const Plane& pl) { return Scale(pl, -1); }
Shape& Shape::Reflect(const Line& axis) { return Scale(axis, -1); }

Shape& Shape::Rotate(const Line& axis, const MyDouble& deg) {
  for (size_t i = 0; i < polygons_.size(); ++i) {
    polygons_[i].Rotate(axis, deg);
  }
  return *this;
}

//--------------------------------Figures-------------------------------------

Cube::Cube(MyDouble x_size, MyDouble y_size, MyDouble z_size,
           MyDouble x, MyDouble y, MyDouble z,
           MyDouble x_angle, MyDouble y_angle, MyDouble z_angle,
           MyDouble center_x, MyDouble center_y, MyDouble center_z)
      : Shape({Polygon({Point(0, 0, 0), Point(1, 0, 0), Point(1, 1, 0), Point(0, 1, 0)}),
               Polygon({Point(0, 0, 0), Point(1, 0, 0), Point(1, 0, 1), Point(0, 0, 1)}),
               Polygon({Point(0, 0, 0), Point(0, 1, 0), Point(0, 1, 1), Point(0, 0, 1)}),
               Polygon({Point(0, 0, 1), Point(1, 0, 1), Point(1, 1, 1), Point(0, 1, 1)}),
               Polygon({Point(0, 1, 0), Point(1, 1, 0), Point(1, 1, 1), Point(0, 1, 1)}),
               Polygon({Point(1, 0, 0), Point(1, 1, 0), Point(1, 1, 1), Point(1, 0, 1)})},
              x_size, y_size, z_size, x, y, z, x_angle, y_angle, z_angle, center_x, center_y, center_z) {
}