#include "../Headers/Point.h"

//------------------------------Constructors----------------------------------
Point::Point(MyDouble x, MyDouble y, MyDouble z): x(x), y(y), z(z) {}
Point::Point(std::vector<MyDouble> parameters)
    : x(parameters[0]), y(parameters[1]), z(parameters[2]) {}

//-------------------------------Compares-------------------------------------
bool operator==(const Point& lhs, const Point& rhs) {
  return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
}

bool operator!=(const Point& lhs, const Point& rhs) { return !(lhs == rhs); }

bool operator<(const Point& lhs, const Point& rhs) {
  if (lhs.x != rhs.x) {
    return lhs.x < rhs.x;
  }
  if (lhs.y != rhs.y) {
    return lhs.y < rhs.y;
  }
  return lhs.z < rhs.z;
}

//------------------------------Arithmetics-----------------------------------
Point Point::operator-() const {
  Point ret = *this;
  ret *= -1;
  return ret;
}

Point& Point::Normalize() {
  *this /= (*this).Length();
  return *this;
}

Point& Point::operator+=(const Point& rhs) {
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}

Point& Point::operator-=(const Point& rhs) {
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;
  return *this;
}

Point& Point::operator*=(const MyDouble& rhs) {
  x *= rhs;
  y *= rhs;
  z *= rhs;
  return *this;
}

Point& Point::operator/=(const MyDouble& rhs) {
  x /= rhs;
  y /= rhs;
  z /= rhs;
  return *this;
}

Point operator+(const Point& lhs, const Point& rhs) {
  Point ret = lhs;
  ret += rhs;
  return ret;
}

Point operator-(const Point& lhs, const Point& rhs) {
  Point ret = lhs;
  ret -= rhs;
  return ret;
}

Point operator*(const Point& lhs, const MyDouble& rhs) {
  Point ret = lhs;
  ret *= rhs;
  return ret;
}

Point operator/(const Point& lhs, const MyDouble& rhs) {
  Point ret = lhs;
  ret /= rhs;
  return ret;
}

//---------------------------------i/o-stream--------------------------------

std::istream& operator>>(std::istream& in, Point& p) {
  in >> p.x >> p.y >> p.z;
  return in;
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
  out << p.x << " " << p.y << " " << p.z;
  return out;
}

//---------------------------------Qualities---------------------------------
MyDouble Point::Length() const {
  return MyDouble(std::sqrt((x * x + y * y + z * z).value));
}

MyDouble Point::Distance(const Point& rhs) const {
  return (*this - rhs).Length();
}

MyDouble DotProduct(const Point& lhs, const Point& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Point CrossProduct(const Point& lhs, const Point& rhs) {
  return {lhs.y * rhs.z - lhs.z * rhs.y,
          lhs.z * rhs.x - lhs.x * rhs.z,
          lhs.x * rhs.y - lhs.y * rhs.x};
}