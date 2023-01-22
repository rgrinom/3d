#include "../Headers/Polygon.h"

std::random_device Polygon::rd_;
std::mt19937 Polygon::gen_ = std::mt19937(rd_());
std::uniform_int_distribution<> Polygon::distr_ = std::uniform_int_distribution<>(-10000, 10000);

//------------------------------Polygon---------------------------------------
Polygon::Polygon(const std::vector<Point>& points): points_(points) {}

bool Polygon::Contains(const Point& p) const {
  size_t posistive_rotations = 0, negative_rotations = 0;
  Point normal = Plane(points_[0], points_[1], points_[2]).Normal();
  for (size_t cur_point_ind = 0; cur_point_ind < points_.size(); ++cur_point_ind) {
    size_t next_point_ind = (cur_point_ind + 1) % points_.size();
    const Point& cur_point = points_[cur_point_ind];
    const Point& next_point = points_[next_point_ind];
    Point cur_normal = CrossProduct(next_point - cur_point, p - cur_point);
    MyDouble dot_product = DotProduct(normal, cur_normal);
    if (dot_product > 0) {
      ++posistive_rotations;
    } else if (dot_product < 0) {
      ++negative_rotations;
    }
  }
  return (posistive_rotations == 0 || negative_rotations == 0);
}

Point Polygon::operator[](size_t ind) const { return points_[ind]; }
Point& Polygon::operator[](size_t ind) {return points_[ind]; }

Polygon& Polygon::operator+=(const Point& p) {
  for (size_t i = 0; i < points_.size(); ++i) {
    points_[i] += p;
  }
  return *this;
}

Polygon& Polygon::operator-=(const Point& p) {
  for (size_t i = 0; i < points_.size(); ++i) {
    points_[i] -= p;
  }
  return *this;
}

Polygon& Polygon::Scale(const Point& center, const MyDouble& k) {
  for (size_t i = 0; i < points_.size(); ++i) {
    points_[i].Scale(center, k);
  }
  return *this;
}

Polygon& Polygon::Scale(const Plane& pl, const MyDouble& k) {
  for (size_t i = 0; i < points_.size(); ++i) {
    points_[i].Scale(pl, k);
  }
  return *this;
}

Polygon& Polygon::Scale(const Line& axis, const MyDouble& k) {
  for (size_t i = 0; i < points_.size(); ++i) {
    points_[i].Scale(axis, k);
  }
  return *this;
}

Polygon& Polygon::Reflect(const Point& center) { return Scale(center, -1); }
Polygon& Polygon::Reflect(const Plane& pl) { return Scale(pl, -1); }
Polygon& Polygon::Reflect(const Line& axis) { return Scale(axis, -1); }

Polygon& Polygon::Rotate(const Line& axis, const MyDouble& deg) {
  for (size_t i = 0; i < points_.size(); ++i) {
    points_[i].Rotate(axis, deg);
  }
  return *this;
}

bool Polygon::SegmentContains(const Point& p1, const Point& p2,
                              const Point& p) const {
  Line l(p1, p2);
  if (!l.Contains(p)) {
    return false;
  }
  return (DotProduct(p2 - p1, p - p1) >= 0) &&
         (DotProduct(p1 - p2, p - p2) >= 0);
}

std::ostream& operator<<(std::ostream& out, const Polygon& poly) {
  for (size_t i = 0; i < poly.points_.size(); ++i) {
    out << poly.points_[i] << "\n";
  }
  return out;
}