#include "../Headers/Line.h"

std::random_device Line::rd_;
std::mt19937 Line::gen_ = std::mt19937(rd_());
std::uniform_int_distribution<> Line::distr_ = std::uniform_int_distribution<>(1, 10);

Line::Line(const Point& p1, const Point& p2) {
  Point p = {distr_(gen_), distr_(gen_), distr_(gen_)};
  while (CrossProduct(p2 - p1, p - p1).Length() == 0) {
    p = {distr_(gen_), distr_(gen_), distr_(gen_)};
  }
  // std::cout << p << "\n";
  pl1_ = Plane(p1, p2, p);
  std::vector<MyDouble> parameters = pl1_.GetParameters();
  // std::cout << parameters[0] << " " << parameters[1] << " " << parameters[2] << " " << parameters[3] << "\n";
  // std::cout << pl1_.Distance(p) << "\n";
  while (pl1_.Contains(p)) {
    p = {distr_(gen_), distr_(gen_), distr_(gen_)};
    // std::cout << "Point changed\n";
  }
  pl2_ = Plane(p1, p2, p);
}

Line::Line(const Plane& pl1, const Plane& pl2): pl1_(pl1), pl2_(pl2) {}

bool Line::Contains(const Point& p) { return pl1_.Contains(p) && pl2_.Contains(p); }

std::pair<Plane, Plane> Line::GetParameters() const { return {pl1_, pl2_}; }

//----------------------------------Intersections-----------------------------
Line Intersection(const Plane& pl1, const Plane& pl2) {
  Line ret(pl1, pl2);
  return ret;
}

Point Intersection(const Plane& pl, const Line& l) {
  std::vector<LE> system;
  std::vector<MyDouble> tmp;
  tmp = pl.GetParameters();
  system.push_back(LE({tmp[0], tmp[1], tmp[2]}, -tmp[3]));
  tmp = l.GetParameters().first.GetParameters();
  system.push_back(LE({tmp[0], tmp[1], tmp[2]}, -tmp[3]));
  tmp = l.GetParameters().second.GetParameters();
  system.push_back(LE({tmp[0], tmp[1], tmp[2]}, -tmp[3]));
  SoLE sole(system);
  tmp = sole.Solve();
  if (!sole.HasSolution()) {
    return {constants::kInf, constants::kInf, constants::kInf};
  }
  return {tmp[0], tmp[1], tmp[2]};
}

Point Intersection(const Line& l, const Plane& pl) {
  return Intersection(pl, l);
}

Point Intersection(const Line& l1, const Line& l2) {
  std::vector<LE> system;
  std::vector<MyDouble> tmp;
  tmp = l1.GetParameters().first.GetParameters();
  system.push_back(LE({tmp[0], tmp[1], tmp[2]}, -tmp[3]));
  tmp = l1.GetParameters().second.GetParameters();
  system.push_back(LE({tmp[0], tmp[1], tmp[2]}, -tmp[3]));
  tmp = l2.GetParameters().first.GetParameters();
  system.push_back(LE({tmp[0], tmp[1], tmp[2]}, -tmp[3]));
  tmp = l2.GetParameters().second.GetParameters();
  system.push_back(LE({tmp[0], tmp[1], tmp[2]}, -tmp[3]));
  SoLE sole(system);
  tmp = sole.Solve();
  if (!sole.HasSolution()) {
    return {constants::kInf, constants::kInf, constants::kInf};
  }
  return {tmp[0], tmp[1], tmp[2]};
}