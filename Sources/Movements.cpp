#include "../Headers/Point.h"
#include "../Headers/Plane.h"
#include "../Headers/Line.h"
#include "../Headers/Polygon.h"

//----------------------------------Intersections-----------------------------
Line Plane::Intersection(const Plane& pl) const {
  Line ret(*this, pl);
  return ret;
}

Point Plane::Intersection(const Line& l) const {
  std::vector<LE> system;
  std::vector<MyDouble> parameters;
  parameters = GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, -parameters[3]));
  parameters = l.GetParameters().first.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, -parameters[3]));
  parameters = l.GetParameters().second.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, -parameters[3]));
  SoLE sole(system);
  parameters = sole.Solution();
  if (!sole.HasSolution()) {
    return Point(constants::kInf, constants::kInf, constants::kInf);
  }
  return Point(parameters[0], parameters[1], parameters[2]);
}

Point Line::Intersection(const Plane& pl) const {
  return pl.Intersection(*this);
}

Point Line::Intersection(const Line& l) const {
  std::vector<LE> system;
  std::vector<MyDouble> parameters;
  parameters = GetParameters().first.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, -parameters[3]));
  parameters = GetParameters().second.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, -parameters[3]));
  parameters = l.GetParameters().first.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, -parameters[3]));
  parameters = l.GetParameters().second.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, -parameters[3]));
  SoLE sole(system);
  parameters = sole.Solution();
  if (!sole.HasSolution()) {
    return Point(constants::kInf, constants::kInf, constants::kInf);
  }
  return Point(parameters[0], parameters[1], parameters[2]);
}

Point Polygon::Intersection(const Line& l) const {
  Plane pl(points[0], points[1], points[2]);
  Point intersection = pl.Intersection(l);
  return (Contains(intersection) ?
      intersection : Point(constants::kInf, constants::kInf, constants::kInf));
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
  Point height = pl.Normal() * pl.Distance(*this);
  if (!pl.Contains(*this + height)) {
    height *= -1;
  }
  *this = (*this + height) - height * k;
  return *this;
}

Point& Point::Scale(const Line& axis, const MyDouble& k) {
  Point height = -axis.Normal(*this) * axis.Distance(*this);
  *this = (*this + height) - height * k;
  return (*this);
}

Polygon& Polygon::Scale(const Point& center, const MyDouble& k) {
  for (size_t i = 0; i < points.size(); ++i) {
    points[i].Scale(center, k);
  }
  return *this;
}

Polygon& Polygon::Scale(const Plane& pl, const MyDouble& k) {
  for (size_t i = 0; i < points.size(); ++i) {
    points[i].Scale(pl, k);
  }
  return *this;
}

Polygon& Polygon::Scale(const Line& axis, const MyDouble& k) {
  for (size_t i = 0; i < points.size(); ++i) {
    points[i].Scale(axis, k);
  }
  return *this;
}

//--------------------------------Reflects------------------------------------
Point& Point::Reflect(const Point& center) { return Scale(center, -1); }
Point& Point::Reflect(const Plane& pl) { return Scale(pl, -1); }
Point& Point::Reflect(const Line& axis) { return Scale(axis, -1); }

Polygon& Polygon::Reflect(const Point& center) { return Scale(center, -1); }
Polygon& Polygon::Reflect(const Plane& pl) { return Scale(pl, -1); }
Polygon& Polygon::Reflect(const Line& axis) { return Scale(axis, -1); }

//------------------------------------Rotations-------------------------------
MyDouble DegToRad(MyDouble deg) { return deg * constants::kPi / 180.0; }
MyDouble RadToDeg(MyDouble rad) { return rad * 180.0 / constants::kPi; }

Point& Point::Rotate(const Line& axis, const MyDouble& deg) {
  MyDouble angle = DegToRad(deg);
  Point e3 = axis.Collinear();
  Point e1 = axis.Normal(*this);
  Point e2 = CrossProduct(e3, e1);

  MyDouble normalLength = axis.Distance(*this);

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

Polygon& Polygon::Rotate(const Line& axis, const MyDouble& deg) {
  for (size_t i = 0; i < points.size(); ++i) {
    points[i].Rotate(axis, deg);
  }
  return *this;
}