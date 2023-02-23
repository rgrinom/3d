#include "../Headers/Line.h"

Line::Line(const Point& p1, const Point& p2): p0(p1), a((p2 - p1).Normalize()) {}

Point Line::Normal(const Point& p) const {
  Point n1 = CrossProduct(a, p - p0).Normalize();
  return CrossProduct(n1, a);
}

MyDouble Line::Distance(const Point& p) const {
  return DotProduct(Normal(p), p - p0);
}

bool Line::Contains(const Point& p) const { return Distance(p) == 0; }

Point Line::Proection(const Point& p) const {
  return p - Normal(p) * Distance(p);
}

std::istream& operator>>(std::istream& in, Line& l) {
  Point p1, p2;
  in >> p1 >> p2;
  l.p0 = p1;
  l.a = p2 - p1;
  return in;
}

std::ostream& operator<<(std::ostream& out, const Line& l) {
  out << l.p0 << l.a;
  return out;
}