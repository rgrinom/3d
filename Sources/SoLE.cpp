#include "../Headers/SoLE.h"

//------------------------------------LE-------------------------------------
//-------------------------------Constructors--------------------------------
LE::LE(const std::vector<MyDouble>& values, const MyDouble& b)
    : values_(values), b_(b) {}

//-------------------------------Arithmetics---------------------------------
LE& LE::operator+=(const LE& rhs) {
  for (size_t i = 0; i < values_.size(); ++i) {
    values_[i] += rhs.values_[i];
  }
  b_ += rhs.b_;
  return *this;
}

LE& LE::operator-=(const LE& rhs) {
  for (size_t i = 0; i < values_.size(); ++i) {
    values_[i] -= rhs.values_[i];
  }
  b_ -= rhs.b_;
  return *this;
}

LE& LE::operator*=(const MyDouble& rhs) {
  for (size_t i = 0; i < values_.size(); ++i) {
    values_[i] *= rhs;
  }
  b_ *= rhs;
  return *this;
}

LE& LE::operator/=(const MyDouble& rhs) {
  for (size_t i = 0; i < values_.size(); ++i) {
    values_[i] /= rhs;
  }
  b_ /= rhs;
  return *this;
}

LE operator+(const LE& lhs, const LE& rhs) {
  LE ret = lhs;
  ret += rhs;
  return ret;
}

LE operator-(const LE& lhs, const LE& rhs) {
  LE ret = lhs;
  ret -= rhs;
  return ret;
}

LE operator*(const LE& lhs, const MyDouble& rhs) {
  LE ret = lhs;
  ret *= rhs;
  return ret;
}

LE operator/(const LE& lhs, const MyDouble& rhs) {
  LE ret = lhs;
  ret /= rhs;
  return ret;
}

//-------------------------------Size/Access----------------------------------
size_t LE::Size() { return values_.size(); }

MyDouble& LE::operator[](size_t ind) {
  return (ind < values_.size() ? values_[ind] : b_);
}

MyDouble LE::operator[](size_t ind) const {
  return (ind < values_.size() ? values_[ind] : b_);
}

//----------------------------------SoLE-------------------------------------
//-------------------------------Constructors--------------------------------
SoLE::SoLE(std::vector<LE> system)
    : system_(system), based_cnt_(0), unknown_cnt(system_[0].Size()),
      is_based(system_.size()) {}

std::vector<MyDouble> SoLE::Solve() {
  Gauss();
  std::vector<MyDouble> ans(unknown_cnt);
  size_t cur_equation = based_cnt_ - 1;
  for (size_t cur_unknown_ = unknown_cnt; cur_unknown_ > 0; --cur_unknown_) {
    size_t cur_unknown = cur_unknown_ - 1;
    if (!is_based[cur_unknown]) {
      continue;
    }
    ans[cur_unknown] = system_[cur_equation][unknown_cnt];
    --cur_equation;
  }
  return ans;
}

void SoLE::Gauss() {
  for (size_t cur_unknown = 0; cur_unknown < std::min(unknown_cnt, system_.size()); ++cur_unknown) {
    for (size_t cur_equation = based_cnt_; cur_equation < system_.size();
         ++cur_equation) {
      if (system_[cur_equation][based_cnt_] != 0) {
        std::swap(system_[cur_equation], system_[based_cnt_]);
        break;
      }
    }
    if (system_[based_cnt_][based_cnt_] == 0) {
      continue;
    }
    system_[based_cnt_] /= system_[based_cnt_][based_cnt_];
    for (size_t cur_equation = 0; cur_equation < system_.size();
         ++cur_equation) {
      if (cur_equation == based_cnt_) {
        continue;
      }
      system_[cur_equation] -= system_[based_cnt_] * system_[cur_equation][based_cnt_];
    }
    is_based[based_cnt_] = true;
    ++based_cnt_;
  }
}