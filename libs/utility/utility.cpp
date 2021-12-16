#include "utility.hpp"
#include <cmath>
#include <iostream>
#include <sstream>

namespace utl {

int stpi(const std::string& str) noexcept
{
  int res { 0 };
  const auto RBEGIN { str.rbegin() };

  for (auto i = RBEGIN; i != str.rend(); ++i) {
    if (*i > '9' || *i < '0') {
      res = ERROR_CODE;
      break;
    }
    const int BASE { 10 };
    res += (*i - '0') * static_cast<int>(std::pow(BASE, i - RBEGIN));
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
