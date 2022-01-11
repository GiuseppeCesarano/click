#include "utility.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>

namespace utl {

bool is_digit(const char c) noexcept
{
  return isdigit(c) != 0;
}

int stpi(const std::string& str) noexcept
{
  auto ret = std::stoi(str);
  return ret > 0 ? ret : ERROR_CODE;
}

std::string pits(int n) noexcept
{
  return n > 0 ? std::to_string(n) : std::string {};
}
} // namespace utl
