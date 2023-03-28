#include "Figures.h"

//----------------------------------Shape-------------------------------------
Shape::Shape(const std::vector<Polygon>& polygons,
             const Point& size, const Point& position,
             const Point& rotation, const Point& center)
    : polygons_(polygons), center_(center),
      forward_(1, 0, 0), left_(0, 1, 0), up_(0, 0, 1){
  Plane x_scale(Point(0, 0, 0), Point(0, 1, 0), Point(0, 0, 1));
  Plane y_scale(Point(0, 0, 0), Point(1, 0, 0), Point(0, 0, 1));
  Plane z_scale(Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0));
  Scale(x_scale, size.x);
  Scale(y_scale, size.y);
  Scale(z_scale, size.z);

  *this += position - center;

  Rotate(Point(1, 0, 0), rotation.x);
  Rotate(Point(0, 1, 0), rotation.y);
  Rotate(Point(0, 0, 1), rotation.z);
}

Line Shape::GetForwardAxis() const {
  return Line(center_, center_ + forward_);
}

Line Shape::GetLeftAxis() const {
  return Line(center_, center_ + left_);
}

Line Shape::GetUpAxis() const {
  return Line(center_, center_ + up_);
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

MyDouble Shape::DistanceTo(const Point& p) const {
  bool inside = true;
  MyDouble min_distance = constants::kInf;
  for (size_t cur_polygon = 0; cur_polygon < polygons_.size(); ++cur_polygon) {
    MyDouble cur_distance = polygons_[cur_polygon].DistanceTo(p);
    if (cur_distance > 0) {
      inside = false;
    } else {
      cur_distance *= -1;
    }

    if (cur_distance < min_distance) {
      min_distance = cur_distance;
    }
  }
  if (inside) {
    min_distance *= -1;
  }
  return min_distance;
}

Shape& Shape::operator+=(const Point& p) {
  for (size_t i = 0; i < polygons_.size(); ++i) {
    polygons_[i] += p;
  }
  center_ += p;
  return *this;
}

Shape& Shape::operator-=(const Point& p) {
  return (*this += -p);
}

Shape& Shape::MoveForward(const MyDouble& distance) {
  return (*this += forward_ * distance);
}

Shape& Shape::MoveLeft(const MyDouble& distance) {
  return (*this += left_ * distance);
}

Shape& Shape::MoveUp(const MyDouble& distance) {
  return (*this += up_ * distance);
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

  forward_ += center_;
  left_ += center_;
  up_ += center_;

  center_.Rotate(axis, deg);
  forward_.Rotate(axis, deg);
  left_.Rotate(axis, deg);
  up_.Rotate(axis, deg);

  forward_ -= center_;
  left_ -= center_;
  up_ -= center_;

  return *this;
}

Shape& Shape::Rotate(const Point& p, const MyDouble& deg) {
  Line axis(center_, center_ + p);
  return Rotate(axis, deg);
}

Shape& Shape::RotateAroundForwardAxis(const MyDouble& deg) {
  return Rotate(forward_, deg);
}

Shape& Shape::RotateAroundLeftAxis(const MyDouble& deg) {
  return Rotate(left_, deg);
}

Shape& Shape::RotateAroundUpAxis(const MyDouble& deg) {
  return Rotate(up_, deg);
}

//--------------------------------Figures-------------------------------------

Cube::Cube(const Point& size, const Point& position,
           const Point& rotation, const Point& center_position)
    : Shape({Polygon({Point(0, 0, 0), Point(0, 1, 0), Point(1, 1, 0), Point(1, 0, 0)}),
             Polygon({Point(0, 0, 0), Point(1, 0, 0), Point(1, 0, 1), Point(0, 0, 1)}),
             Polygon({Point(0, 0, 0), Point(0, 0, 1), Point(0, 1, 1), Point(0, 1, 0)}),
             Polygon({Point(0, 0, 1), Point(1, 0, 1), Point(1, 1, 1), Point(0, 1, 1)}),
             Polygon({Point(0, 1, 0), Point(0, 1, 1), Point(1, 1, 1), Point(1, 1, 0)}),
             Polygon({Point(1, 0, 0), Point(1, 1, 0), Point(1, 1, 1), Point(1, 0, 1)})},
             size, position, rotation, center_position) {}