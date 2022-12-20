#include "../Headers/MyDouble.h"

//-------------------------------Constructors--------------------------------
MyDouble::MyDouble(double value): value(value) {}

//---------------------------------Compares----------------------------------
bool operator==(const MyDouble& lhs, const MyDouble& rhs) {
  return std::fabs(lhs.value - rhs.value) < MyDouble::kEps;
}

bool operator!=(const MyDouble& lhs, const MyDouble& rhs) {
  return !(lhs == rhs);
}

bool operator<(const MyDouble& lhs, const MyDouble& rhs) {
  return (lhs != rhs) && std::fabs(rhs.value - lhs.value) > 0;
}

bool operator>(const MyDouble& lhs, const MyDouble& rhs) {
  return rhs < lhs;
}

bool operator<=(const MyDouble& lhs, const MyDouble& rhs) {
  return !(lhs > rhs);
}

bool operator>=(const MyDouble& lhs, const MyDouble& rhs) {
  return !(lhs < rhs);
}

//-------------------------------Arithmetics---------------------------------
MyDouble& MyDouble::operator+=(const MyDouble& rhs) {
  value += rhs.value;
  return *this;
}

MyDouble& MyDouble::operator-=(const MyDouble& rhs) {
  value -= rhs.value;
  return *this;
}

MyDouble& MyDouble::operator*=(const MyDouble& rhs) {
  value *= rhs.value;
  return *this;
}

MyDouble& MyDouble::operator/=(const MyDouble& rhs) {
  value /= rhs.value;
  return *this;
}

MyDouble operator+(const MyDouble& lhs, const MyDouble& rhs) {
  MyDouble ret = lhs;
  ret += rhs;
  return ret;
}

MyDouble operator-(const MyDouble& lhs, const MyDouble& rhs) {
  MyDouble ret = lhs;
  ret -= rhs;
  return ret;
}

MyDouble operator*(const MyDouble& lhs, const MyDouble& rhs) {
  MyDouble ret = lhs;
  ret *= rhs;
  return ret;
}

MyDouble operator/(const MyDouble& lhs, const MyDouble& rhs) {
  MyDouble ret = lhs;
  ret /= rhs;
  return ret;
}

//-------------------------------i/o-stream----------------------------------
std::istream& operator>>(std::istream& in, MyDouble& rhs) {
  in >> rhs.value;
  return in;
}

std::ostream& operator<<(std::ostream& out, const MyDouble& rhs) {
  out << rhs.value;
  return out;
}