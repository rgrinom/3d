#pragma once

#include <vector>

#include "../Headers/MyDouble.h"

class LE {
 public:
  LE(const std::vector<MyDouble>& values, const MyDouble& b);

  LE& operator+=(const LE& rhs);
  LE& operator-=(const LE& rhs);
  LE& operator*=(const MyDouble& rhs);
  LE& operator/=(const MyDouble& rhs);

  size_t Size();
  MyDouble& operator[](size_t ind);
  MyDouble operator[](size_t ind) const;

 private:
  std::vector<MyDouble> values_;
  MyDouble b_;
};

LE operator+(const LE& lhs, const LE& rhs);
LE operator-(const LE& lhs, const LE& rhs);
LE operator*(const LE& lhs, const MyDouble& rhs);
LE operator/(const LE& lhs, const MyDouble& rhs);

class SoLE {
 public:
  SoLE(std::vector<LE> system);
  std::vector<MyDouble> Solve();
  bool HasSolution();

 private:
  std::vector<LE> system_;
  size_t based_cnt_, unknown_cnt;
  std::vector<bool> is_based;
  bool has_solution_;

  void Gauss();
};