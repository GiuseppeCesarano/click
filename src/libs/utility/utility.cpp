#include "utility.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <sstream>

namespace utl {

int stpi(const std::string& str) noexcept
{
  int res { ERROR_CODE };

  if (std::all_of(str.begin(), str.end(), is_digit())) {
    const char* BACK { &str.back() };
    res = std::reduce(str.begin(), str.end(), static_cast<int>(0), [BACK](int n, const char& c) {
      const int BASE { 10 };
      return n + (c - '0') * static_cast<int>(std::pow(BASE, BACK - &c));
    });
  }

  return res;
}

std::string pits(int n) noexcept
{
  if (n < 0) {
    return {};
  }
  std::stringstream ss;
  ss << n;
  return ss.str();
}
} // namespace utl
