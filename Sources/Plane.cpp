#include "../Headers/Plane.h"

Plane::Plane(const Point& p1, const Point& p2, const Point& p3) {
  std::vector<LE> system;
  system.push_back(LE({p1.x, p1.y, p1.z, 1}, 0));
  system.push_back(LE({p2.x, p2.y, p2.z, 1}, 0));
  system.push_back(LE({p3.x, p3.y, p3.z, 1}, 0));
  SoLE sole(system);
  std::vector<MyDouble> coefficients = sole.Solve();
  a_ = coefficients[0];
  b_ = coefficients[1];
  c_ = coefficients[2];
  d_ = coefficients[3];
}

MyDouble Plane::Distance(const Point& p) const {
  return a_ * p.x + b_ * p.y + c_ * p.z + d_;
}

bool Plane::Contains(const Point& p) const { return  Distance(p) == 0; }

Point Plane::Normal() const { return {a_, b_, c_}; }

std::vector<MyDouble> Plane::GetParameters() const { return {a_, b_, c_, d_}; }