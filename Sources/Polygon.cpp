#include "../Headers/Polygon.h"

std::random_device Polygon::rd_;
std::mt19937 Polygon::gen_ = std::mt19937(rd_());
std::uniform_int_distribution<> Polygon::distr_ = std::uniform_int_distribution<>(-10000, 10000);

//------------------------------Segment---------------------------------------
Segment::Segment(const Point& p1, const Point& p2): p1_(p1), p2_(p2) {}

Segment::Segment(const std::vector<Point>& points_)
    : p1_(points_[0]), p2_(points_[1]) {}

bool Segment::Contains(const Point& p) const {
  Line l(p1_, p2_);
  if (!l.Contains(p)) {
    return false;
  }
  return (DotProduct(p2_ - p1_, p - p1_) >= 0) &&
         (DotProduct(p1_ - p2_, p - p2_) >= 0);
}

//------------------------------Polygon---------------------------------------
Polygon::Polygon(const std::vector<Point>& points): points_(points) {}

bool Polygon::Contains(const Point& p) const {
  Plane pl(points_[0], points_[1], points_[2]);
  if (!pl.Contains(p)) {
    return false;
  }

  for (size_t cur_point_ind = 0; cur_point_ind < points_.size(); ++cur_point_ind) {
    size_t next_point_ind = (cur_point_ind + 1) % points_.size();
    const Point& cur_point = points_[cur_point_ind];
    const Point& next_point = points_[next_point_ind];
    if (Segment(cur_point, next_point).Contains(p)) {
      return true;
    }
  }

  Line l;
  bool is_line_good = false;
  while (!is_line_good) {
    MyDouble k1(distr_(gen_)), k2(distr_(gen_));
    Point p1 = pl.p0 + pl.u * k1 + pl.v * k2;
    l = Line(p, p1);
    is_line_good = true;
    for (size_t cur_point_ind = 0; cur_point_ind < points_.size(); ++cur_point_ind) {
      const Point& cur_point = points_[cur_point_ind];
      if (l.Contains(cur_point)) {
        is_line_good = false;
        break;
      }
    }
  }

  size_t intersections_cnt = 0;
  for (size_t cur_point_ind = 0; cur_point_ind < points_.size(); ++cur_point_ind) {
    size_t next_point_ind = (cur_point_ind + 1) % points_.size();
    const Point& cur_point = points_[cur_point_ind];
    const Point& next_point = points_[next_point_ind];
    Point intersection = l.Intersection(Line(cur_point, next_point));
    if (Segment(cur_point, next_point).Contains(intersection) &&
        intersection < p) {
      ++intersections_cnt;
    }
  }
  
  return intersections_cnt % 2 == 1;
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

std::ostream& operator<<(std::ostream& out, const Polygon& poly) {
  for (size_t i = 0; i < poly.points_.size(); ++i) {
    out << poly.points_[i] << "\n";
  }
  return out;
}