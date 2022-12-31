#include "../Headers/Polygon.h"

//------------------------------Segment---------------------------------------
Segment::Segment(const Point& p1, const Point& p2): p1_(p1), p2_(p2) {}

Segment::Segment(const std::vector<Point>& points)
    : p1_(points[0]), p2_(points[1]) {}

bool Segment::Contains(const Point& p) const {
  Line l(p1_, p2_);
  if (!l.Contains(p)) {
    return false;
  }
  return (DotProduct(p2_ - p1_, p - p1_) >= 0) &&
         (DotProduct(p1_ - p2_, p - p2_) >= 0);
}

//------------------------------Polygon---------------------------------------
Polygon::Polygon(const std::vector<Point>& points): points(points) {}

bool Polygon::Contains(const Point& p) const {
  Plane pl(points[0], points[1], points[2]);
  if (!pl.Contains(p)) {
    return false;
  }
  for (size_t cur_point_ind = 0; cur_point_ind < points.size(); ++cur_point_ind) {
    size_t next_point_ind = (cur_point_ind + 1) % points.size();
    const Point& cur_point = points[cur_point_ind];
    const Point& next_point = points[next_point_ind];
    if (Segment(cur_point, next_point).Contains(p)) {
      return true;
    }
  }

  std::vector<MyDouble> pl_parameters = pl.GetParameters();
  std::vector<LE> system;
  system.push_back(LE({pl_parameters[0], pl_parameters[1], pl_parameters[2]}, -pl_parameters[3]));
  SoLE sole(system);
  Line l;
  bool is_line_good = false;
  while (!is_line_good) {
    Point p1(sole.RandomSolution());
    l = Line(p, p1);
    is_line_good = true;
    for (size_t cur_point_ind = 0; cur_point_ind < points.size(); ++cur_point_ind) {
      const Point& cur_point = points[cur_point_ind];
      if (l.Contains(cur_point)) {
        is_line_good = false;
        break;
      }
    }
  }

  size_t intersections_cnt = 0;
  for (size_t cur_point_ind = 0; cur_point_ind < points.size(); ++cur_point_ind) {
    size_t next_point_ind = (cur_point_ind + 1) % points.size();
    const Point& cur_point = points[cur_point_ind];
    const Point& next_point = points[next_point_ind];
    Point intersection = Intersection(l, Line(cur_point, next_point));
    if (Segment(cur_point, next_point).Contains(intersection) &&
        intersection < p) {
      ++intersections_cnt;
    }
  }
  
  return intersections_cnt % 2 == 1;
}

//---------------------------------Intersections-----------------------------
Point Intersection(const Polygon& poly, const Line& l) {
  Plane pl(poly.points[0], poly.points[1], poly.points[2]);
  Point intersection = Intersection(pl, l);
  return (poly.Contains(intersection) ?
      intersection : Point(constants::kInf, constants::kInf, constants::kInf));
}

Point Intersection(const Line& l, const Polygon& poly) {
  return Intersection(poly, l);
}

//------------------------------------Scales----------------------------------
Polygon& Scale(Polygon& poly, const Point& center, const MyDouble& k) {
  for (size_t i = 0; i < poly.points.size(); ++i) {
    Scale(poly.points[i], center, k);
  }
  return poly;
}

Polygon& Scale(Polygon& poly, const Plane& pl, const MyDouble& k) {
  for (size_t i = 0; i < poly.points.size(); ++i) {
    Scale(poly.points[i], pl, k);
  }
  return poly;
}

Polygon& Scale(Polygon& poly, const Line& axis, const MyDouble& k) {
  for (size_t i = 0; i < poly.points.size(); ++i) {
    Scale(poly.points[i], axis, k);
  }
  return poly;
}

//-----------------------------------Reflections------------------------------
Polygon& Reflect(Polygon& poly, const Point& center) { return Scale(poly, center, -1); }
Polygon& Reflect(Polygon& poly, const Plane& pl) { return Scale(poly, pl, -1); }
Polygon& Reflect(Polygon& poly, const Line& axis) { return Scale(poly, axis, -1); }

//------------------------------------Rotations-------------------------------
Polygon& Rotate(Polygon& poly, const Line& axis, const MyDouble& deg) {
  for (size_t i = 0; i < poly.points.size(); ++i) {
    Rotate(poly.points[i], axis, deg);
  }
  return poly;
}