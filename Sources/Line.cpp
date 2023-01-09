#include "../Headers/Line.h"

std::random_device Line::rd_;
std::mt19937 Line::gen_ = std::mt19937(rd_());
std::uniform_int_distribution<> Line::distr_ = std::uniform_int_distribution<>(-10000, 10000);

Line::Line(const Point& p1, const Point& p2) {
  Point p(distr_(gen_), distr_(gen_), distr_(gen_));
  while (CrossProduct(p2 - p1, p - p1).Length() == 0) {
    p = Point(distr_(gen_), distr_(gen_), distr_(gen_));
  }
  pl1_ = Plane(p1, p2, p);
  p = p1 + DotProduct(p2 - p1, p - p1);
  pl2_ = Plane(p1, p2, p);
}

Line::Line(const Plane& pl1, const Plane& pl2): pl1_(pl1), pl2_(pl2) {}

bool Line::Contains(const Point& p) const {
  return pl1_.Contains(p) && pl2_.Contains(p);
}

std::pair<Plane, Plane> Line::GetParameters() const { return {pl1_, pl2_}; }

Point Line::Collinear() const {
  std::vector<LE> system;
  std::vector<MyDouble> parameters = pl1_.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, 0));
  parameters = pl2_.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, 0));
  SoLE sole(system);
  std::vector<MyDouble> ans = sole.Solution();
  return Point(ans[0], ans[1], ans[2]).Normalize();
}

Point Line::Normal(const Point& p) const {
  std::vector<LE> system;
  std::vector<MyDouble> parameters = pl1_.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, -parameters[3]));
  parameters = pl2_.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, -parameters[3]));
  SoLE sole(system);
  parameters = sole.Solution();
  Point p1(parameters[0], parameters[1], parameters[2]);
  Point a = Collinear();
  Point p2 = p1 + a;
  Plane pl1(p1, p2, p);
  Point pl1_normal = pl1.Normal();
  Plane pl2(p1, p2, p1 + pl1_normal);
  Point ret = pl2.Normal();
  if ((pl2.Distance(p) >= 0 && pl2.Distance(p1 + ret) <= 0) ||
      (pl2.Distance(p) <= 0 && pl2.Distance(p1 + ret) >= 0)) {
    ret *= -1;
  }
  return ret;
}

MyDouble Line::Distance(const Point& p) const {
  Point a = Normal(p);
  Line l(p, p + a);
  Point intersection = Intersection(l);
  return p.Distance(intersection);
}