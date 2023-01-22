#include "../Headers/Point.h"
#include "../Headers/Plane.h"
#include "../Headers/Line.h"
#include "../Headers/Polygon.h"

//----------------------------------Intersections-----------------------------
Line Plane::Intersection(const Plane& pl) const {
  std::vector<LE> system;
  system.reserve(3);
  system.push_back(LE({u.x, v.x, -pl.u.x, -pl.v.x}, pl.p0.x - p0.x));
  system.push_back(LE({u.y, v.y, -pl.u.y, -pl.v.y}, pl.p0.y - p0.y));
  system.push_back(LE({u.z, v.z, -pl.u.z, -pl.v.z}, pl.p0.z - p0.z));
  SoLE sole(system);
  std::vector<MyDouble> solution = sole.Solution();
  Point intersection_p0 = p0 + u * solution[0] + v * solution[1];
  Point intersection_a = CrossProduct(Normal(), pl.Normal());
  return Line(intersection_p0, intersection_p0 + intersection_a);
}

Point Plane::Intersection(const Line& l) const {
  std::vector<LE> system;
  system.reserve(3);
  system.push_back(LE({u.x, v.x, -l.a.x}, l.p0.x - p0.x));
  system.push_back(LE({u.y, v.y, -l.a.y}, l.p0.y - p0.y));
  system.push_back(LE({u.z, v.z, -l.a.z}, l.p0.z - p0.z));
  SoLE sole(system);
  std::vector<MyDouble> solution = sole.Solution();
  if (!sole.HasSolution()) {
    return constants::kNotAPoint;
  }
  return l.p0 + l.a * solution[2];
}

Point Line::Intersection(const Plane& pl) const {
  return pl.Intersection(*this);
}

Point Line::Intersection(const Line& l) const {
  std::vector<LE> system;
  system.reserve(3);
  system.push_back(LE({a.x, -l.a.x}, l.p0.x - p0.x));
  system.push_back(LE({a.y, -l.a.y}, l.p0.y - p0.y));
  system.push_back(LE({a.z, -l.a.z}, l.p0.z - p0.z));
  SoLE sole(system);
  std::vector<MyDouble> solution = sole.Solution();
  if (!sole.HasSolution()) {
    return constants::kNotAPoint;
  }
  return l.p0 + l.a * solution[1];
}

Point Polygon::Intersection(const Line& l) const {
  Plane pl(points_[0], points_[1], points_[2]);
  Point intersection = pl.Intersection(l);
  return (Contains(intersection) ?
      intersection : constants::kNotAPoint);
}

Point Line::Intersection(const Polygon& poly) const {
  return poly.Intersection(*this);
}

//---------------------------------Scales-------------------------------------
Point& Point::Scale(const Point& center, const MyDouble& k) {
  *this = center + (*this - center) * k;
  return *this;
}

Point& Point::Scale(const Plane& pl, const MyDouble& k) {
  Point height = -pl.Normal(*this) * pl.Distance(*this);
  *this = (*this + height) - height * k;
  return *this;
}

Point& Point::Scale(const Line& axis, const MyDouble& k) {
  Point height = -axis.Normal(*this) * axis.Distance(*this);
  *this = (*this + height) - height * k;
  return *this;
}

//--------------------------------Reflects------------------------------------
Point& Point::Reflect(const Point& center) { return Scale(center, -1); }
Point& Point::Reflect(const Plane& pl) { return Scale(pl, -1); }
Point& Point::Reflect(const Line& axis) { return Scale(axis, -1); }

//------------------------------------Rotations-------------------------------
MyDouble DegToRad(MyDouble deg) { return deg * constants::kPi / 180.0; }
MyDouble RadToDeg(MyDouble rad) { return rad * 180.0 / constants::kPi; }

Point& Point::Rotate(const Line& axis, const MyDouble& deg) {
  MyDouble normalLength = axis.Distance(*this);
  if (normalLength == 0) {
    return *this;
  }
  
  MyDouble angle = DegToRad(deg);
  Point e3 = axis.a;
  Point e1 = axis.Normal(*this);
  Point e2 = CrossProduct(e3, e1);


  MyDouble x1 = normalLength * std::cos(angle.value);
  MyDouble y1 = normalLength * std::sin(angle.value);

  MyDouble x = e1.x * x1 + e2.x * y1;
  MyDouble y = e1.y * x1 + e2.y * y1;
  MyDouble z = e1.z * x1 + e2.z * y1;

  Point newNormal(x, y, z);
  Point proection = *this - (e1 * normalLength);

  *this = proection + newNormal;
  return *this;
}