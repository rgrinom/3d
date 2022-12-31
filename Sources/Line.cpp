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
  std::vector<MyDouble> parameters = pl1_.GetParameters();
  while (pl1_.Contains(p)) {
    p = Point(distr_(gen_), distr_(gen_), distr_(gen_));
  }
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
  if ((pl2.Distance(p) >= 0 && pl2.Distance(ret) <= 0) ||
      (pl2.Distance(p) <= 0 && pl2.Distance(ret) >= 0)) {
    ret *= -1;
  }
  return ret;
}

MyDouble Line::Distance(const Point& p) const {
  Point a = Normal(p);
  Line l(p, p + a);
  Point intersection = Intersection(*this, l);
  return p.Distance(intersection);
}

//----------------------------------Intersections-----------------------------
Line Intersection(const Plane& pl1, const Plane& pl2) {
  Line ret(pl1, pl2);
  return ret;
}

Point Intersection(const Plane& pl, const Line& l) {
  std::vector<LE> system;
  std::vector<MyDouble> parameters;
  parameters = pl.GetParameters();
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

Point Intersection(const Line& l, const Plane& pl) {
  return Intersection(pl, l);
}

Point Intersection(const Line& l1, const Line& l2) {
  std::vector<LE> system;
  std::vector<MyDouble> parameters;
  parameters = l1.GetParameters().first.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, -parameters[3]));
  parameters = l1.GetParameters().second.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, -parameters[3]));
  parameters = l2.GetParameters().first.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, -parameters[3]));
  parameters = l2.GetParameters().second.GetParameters();
  system.push_back(LE({parameters[0], parameters[1], parameters[2]}, -parameters[3]));
  SoLE sole(system);
  parameters = sole.Solution();
  if (!sole.HasSolution()) {
    return Point(constants::kInf, constants::kInf, constants::kInf);
  }
  return Point(parameters[0], parameters[1], parameters[2]);
}

//---------------------------------Scales-------------------------------------
Point& Scale(Point& p, const Point& center, const MyDouble& k) {
  p = center + (p - center) * k;
  return p;
}

Point& Scale(Point& p, const Plane& pl, const MyDouble& k) {
  Point height = pl.Normal() * pl.Distance(p);
  if (!pl.Contains(p + height)) {
    height *= -1;
  }
  p = (p + height) - height * k;
  return p;
}

Point& Scale(Point& p, const Line& axis, const MyDouble& k) {
  Point height = -axis.Normal(p) * axis.Distance(p);
  p = (p + height) - height * k;
  return p;
}

//--------------------------------Reflects------------------------------------
Point& Reflect(Point& p, const Point& center) { return Scale(p, center, -1); }
Point& Reflect(Point& p, const Plane& pl) { return Scale(p, pl, -1); }
Point& Reflect(Point& p, const Line& axis) { return Scale(p, axis, -1); }

//------------------------------------Rotations-------------------------------
MyDouble DegToRad(MyDouble deg) { return deg * constants::kPi / 180.0; }
MyDouble RadToDeg(MyDouble rad) { return rad * 180.0 / constants::kPi; }

Point& Rotate(Point& p, const Line& axis, const MyDouble& deg) {
  MyDouble angle = DegToRad(deg);
  Point e3 = axis.Collinear();
  Point e1 = axis.Normal(p);
  Point e2 = CrossProduct(e3, e1);

  MyDouble normalLength = axis.Distance(p);

  MyDouble x1 = normalLength * std::cos(angle.value);
  MyDouble y1 = normalLength * std::sin(angle.value);

  MyDouble x = e1.x * x1 + e2.x * y1;
  MyDouble y = e1.y * x1 + e2.y * y1;
  MyDouble z = e1.z * x1 + e2.z * y1;

  Point newNormal(x, y, z);
  Point proection = p - (e1 * normalLength);

  p = proection + newNormal;
  return p;
}