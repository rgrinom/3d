#include "SoLE.h"

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

LE& LE::operator*=(MyDouble rhs) {
  for (size_t i = 0; i < values_.size(); ++i) {
    values_[i] *= rhs;
  }
  b_ *= rhs;
  return *this;
}

LE& LE::operator/=(MyDouble rhs) {
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

LE operator*(const LE& lhs, MyDouble rhs) {
  LE ret = lhs;
  ret *= rhs;
  return ret;
}

LE operator/(const LE& lhs, MyDouble rhs) {
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
std::random_device SoLE::rd_;
std::mt19937 SoLE::gen_ = std::mt19937(rd_());
std::uniform_int_distribution<> SoLE::distr_ = std::uniform_int_distribution<>(-10000, 10000);

//-------------------------------Constructors--------------------------------
SoLE::SoLE(const std::vector<LE>& system)
    : system_(system), based_cnt_(0), unknown_cnt_(system_[0].Size()),
      is_based_(system_[0].Size()) {
  Gauss();
}

std::vector<MyDouble> SoLE::Solution() {
  std::vector<MyDouble> ans(unknown_cnt_);
  size_t cur_equation = based_cnt_ - 1;
  size_t not_based_ind = unknown_cnt_;

  for (size_t cur_unknown_ = unknown_cnt_; cur_unknown_ > 0; --cur_unknown_) {
    size_t cur_unknown = cur_unknown_ - 1;
    if (!is_based_[cur_unknown]) {
      if (not_based_ind == unknown_cnt_) {
        ans[cur_unknown] = 1;
        not_based_ind = cur_unknown;
      }
      continue;
    }
    ans[cur_unknown] = system_[cur_equation][unknown_cnt_];
    if (not_based_ind != unknown_cnt_) {
      ans[cur_unknown] -= system_[cur_equation][not_based_ind];
    }
    --cur_equation;
  }
  return ans;
}

std::vector<MyDouble> SoLE::RandomSolution() {
  std::vector<MyDouble> ans(unknown_cnt_);
  size_t cur_equation = based_cnt_ - 1;

  for (size_t cur_unknown_ = unknown_cnt_; cur_unknown_ > 0; --cur_unknown_) {
    size_t cur_unknown = cur_unknown_ - 1;
    if (!is_based_[cur_unknown]) {
      ans[cur_unknown] = distr_(gen_);
      continue;
    }
    ans[cur_unknown] = system_[cur_equation][unknown_cnt_];
    for (size_t i = cur_unknown + 1; i < unknown_cnt_; ++i) {
      ans[cur_unknown] -= ans[i] * system_[cur_equation][i];
    }
    --cur_equation;
  }
  return ans;
}

bool SoLE::HasSolution() { return has_solution_; }

void SoLE::Gauss() {
  for (size_t cur_unknown = 0; cur_unknown < unknown_cnt_; ++cur_unknown) {
    for (size_t cur_equation = based_cnt_; cur_equation < system_.size();
         ++cur_equation) {
      if (system_[cur_equation][cur_unknown] != 0) {
        std::swap(system_[cur_equation], system_[based_cnt_]);
        break;
      }
    }
    if (system_[based_cnt_][cur_unknown] == 0) {
      continue;
    }
    system_[based_cnt_] /= system_[based_cnt_][cur_unknown];
    for (size_t cur_equation = 0; cur_equation < system_.size();
         ++cur_equation) {
      if (cur_equation == based_cnt_) {
        continue;
      }
      system_[cur_equation] -= system_[based_cnt_] * system_[cur_equation][cur_unknown];
    }
    is_based_[cur_unknown] = true;
    ++based_cnt_;
    if (based_cnt_ == system_.size()) {
      break;
    }
  }
  has_solution_ = true;
  for (size_t cur_equation = based_cnt_; cur_equation < system_.size();
       ++cur_equation) {
    if (system_[cur_equation][unknown_cnt_] != 0) {
      has_solution_ = false;
      break;
    }
  }
}