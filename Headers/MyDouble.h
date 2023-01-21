#pragma once

#include <cmath>
#include <iostream>

struct MyDouble {
  static constexpr double kEps = 0.000001;
  double value;

  MyDouble(double value = 0.0);

  MyDouble operator-() const;

  MyDouble& operator+=(const MyDouble& rhs);
  MyDouble& operator-=(const MyDouble& rhs);
  MyDouble& operator*=(const MyDouble& rhs);
  MyDouble& operator/=(const MyDouble& rhs);
};

bool operator==(const MyDouble& lhs, const MyDouble& rhs);
bool operator!=(const MyDouble& lhs, const MyDouble& rhs);
bool operator<(const MyDouble& lhs, const MyDouble& rhs);
bool operator>(const MyDouble& lhs, const MyDouble& rhs);
bool operator<=(const MyDouble& lhs, const MyDouble& rhs);
bool operator>=(const MyDouble& lhs, const MyDouble& rhs);

MyDouble operator+(const MyDouble& lhs, const MyDouble& rhs);
MyDouble operator-(const MyDouble& lhs, const MyDouble& rhs);
MyDouble operator*(const MyDouble& lhs, const MyDouble& rhs);
MyDouble operator/(const MyDouble& lhs, const MyDouble& rhs);

std::istream& operator>>(std::istream& in, MyDouble& rhs);
std::ostream& operator<<(std::ostream& out, const MyDouble& rhs);