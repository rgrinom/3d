#pragma once

#include <vector>
#include <random>

#include "../Headers/MyDouble.h"

class LE {
 public:
  LE(const std::vector<MyDouble>& values, const MyDouble& b);

  LE& operator+=(const LE& rhs);
  LE& operator-=(const LE& rhs);
  LE& operator*=(MyDouble rhs);
  LE& operator/=(MyDouble rhs);

  size_t Size();
  MyDouble& operator[](size_t ind);
  MyDouble operator[](size_t ind) const;

 private:
  std::vector<MyDouble> values_;
  MyDouble b_;
};

LE operator+(const LE& lhs, const LE& rhs);
LE operator-(const LE& lhs, const LE& rhs);
LE operator*(const LE& lhs, MyDouble rhs);
LE operator/(const LE& lhs, MyDouble rhs);

class SoLE {
 public:
  SoLE(std::vector<LE> system);
  std::vector<MyDouble> Solution();
  std::vector<MyDouble> RandomSolution();
  bool HasSolution();

 private:
  std::vector<LE> system_;
  size_t based_cnt_, unknown_cnt_;
  std::vector<bool> is_based_;
  bool has_solution_;

  static std::random_device rd_;
  static std::mt19937 gen_;
  static std::uniform_int_distribution<> distr_;

  void Gauss();
};