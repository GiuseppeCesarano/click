#include "grinders.hpp"
#include <array>
#include <numeric>
#include <string>
#include <utility/utility.hpp>

int grinder::dotted_parser(const std::string& clicks_str) const noexcept
{
  int res = utl::ERROR_CODE;
  using jit = utl::jumping_iterator<std::string::const_iterator, 2>;

  if ((clicks_str.size() == FORMATTING_VALUES.size() * 2 - 1) && std::all_of(jit { clicks_str.begin() }, jit { clicks_str.end() + 1 }, utl::is_digit())) {
    jit str_itr { clicks_str.begin() };
    res = std::reduce(FORMATTING_VALUES.begin(), FORMATTING_VALUES.end(), 0, [&str_itr](int reduced, int current) {
      return reduced + current * (*str_itr++ - '0');
    });
  }

  return res;
}

constexpr double grinder::normalize_clicks(int clicks) const noexcept
{
  return clicks * CLICK_VALUE;
}

constexpr int grinder::specify_clicks(double clicks) const noexcept
{
  return static_cast<int>(std::round(clicks / CLICK_VALUE));
}

int grinder::string_to_specific(const std::string& clicks_str) const noexcept
{
  return FORMATTING_VALUES.size() == 0 ? utl::stpi(clicks_str) : dotted_parser(clicks_str);
}

std::string grinder::specific_to_string(int clicks) const noexcept
{
  std::string ret;
  if (FORMATTING_VALUES.size() == 0) {
    ret = utl::pits(clicks);
  } else {
    std::stringstream ss;
    for (const auto VAL : FORMATTING_VALUES) {
      int num = static_cast<int>(std::round(clicks / VAL));
      ss << num << '.';
      clicks -= num * VAL;
    }
    ret = ss.str();
    ret = ret.substr(0, ret.size() - 1);
  }
  return ret;
}

double grinder::operator[](const std::string& readable_clicks) const noexcept
{
  return normalize_clicks(string_to_specific(readable_clicks));
}

std::string grinder::operator[](const double normalized_click) const noexcept
{
  return specific_to_string(specify_clicks(normalized_click));
}

std::string convert_setting(const auto& in_grinder, const std::string& click_str, const auto& out_grinder) noexcept
{
  const auto NORMALIZED_CLICKS = GRINDERS[in_grinder][click_str];
  return NORMALIZED_CLICKS > 0 ? (GRINDERS[out_grinder][NORMALIZED_CLICKS]) : ":(";
}

std::string convert_setting_id(size_t in_grinder, const std::string& click_str, size_t out_grinder) noexcept
{
  return convert_setting(in_grinder, click_str, out_grinder);
}
