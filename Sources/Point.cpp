#include "../Headers/Point.h"

//-------------------------------Compares-------------------------------------
bool operator==(const Point& lhs, const Point& rhs) {
  return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
}

bool operator!=(const Point& lhs, const Point& rhs) { return !(lhs == rhs); }

//------------------------------Arithmetics-----------------------------------
Point Point::operator-() const {
  Point ret = *this;
  ret *= -1;
  return ret;
}

void Point::Normalize() { *this /= (*this).Length(); }

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

MyDouble Distance(const Point& lhs, const Point& rhs) {
  return (rhs - lhs).Length();
}

MyDouble DotProduct(const Point& lhs, const Point& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Point CrossProduct(const Point& lhs, const Point& rhs) {
  return {lhs.y * rhs.z - lhs.z * rhs.y,
          lhs.z * rhs.x - lhs.x * rhs.z,
          lhs.x * rhs.y - lhs.y * rhs.x};
}