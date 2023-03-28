#include "Plane.h"

Plane::Plane(const Point& p1, const Point& p2, const Point& p3)
    : p0(p1), u((p2 - p1).Normalize()), v((p3 - p1).Normalize()) {}

Point Plane::Normal() const { return CrossProduct(u, v).Normalize(); }

Point Plane::Normal(const Point& p) const {
  Point ret = Normal();
  if (DotProduct(ret, p - p0) < 0) {
    ret *= -1;
  }
  return ret;
}

MyDouble Plane::Distance(const Point& p) const {
  return DotProduct(Normal(p), p - p0);
}

MyDouble Plane::SignedDistance(const Point& p) const {
  return DotProduct(Normal(), p - p0);
}

bool Plane::Contains(const Point& p) const { return Distance(p) == 0; }

Point Plane::Proection(const Point& p) const {
  return p - Normal(p) * Distance(p);
}

std::istream& operator>>(std::istream& in, Plane& pl) {
  Point p1, p2, p3;
  in >> p1 >> p2 >> p3;
  pl.p0 = p1;
  pl.u = p2 - p1;
  pl.v = p3 - p1;
  return in;
}

std::ostream& operator<<(std::ostream& out, const Plane& pl) {
  out << pl.p0 << pl.u << pl.v;
  return out;
}