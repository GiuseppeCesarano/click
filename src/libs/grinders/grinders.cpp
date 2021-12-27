#include "grinders.hpp"
#include <array>
#include <string>
#include <utility/utility.hpp>

constexpr double grinder::click_value() const noexcept
{
  return CLICK_VALUE;
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
  int res { utl::ERROR_CODE };
  if (FORMATTING_VALUES.size() == 0) {
    res = utl::stpi(clicks_str);
  } else {
    const auto INPUT_EXPECTED_LENGHT { FORMATTING_VALUES.size() * 2 - 1 };
    if (clicks_str.size() == INPUT_EXPECTED_LENGHT) {
      res = 0;
      size_t pos { 0 };
      for (const auto VAL : FORMATTING_VALUES) {
        if (clicks_str[pos] < '0' || clicks_str[pos] > '9') {
          res = utl::ERROR_CODE;
          break;
        }
        res += VAL * (clicks_str[pos] - '0');
        pos += 2;
      }
    }
  }
  return res;
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

std::string grinder::operator<<(double norm_clicks) const noexcept
{
  return specific_to_string(specify_clicks(norm_clicks));
}

constexpr double grinder::operator()(int clicks) const noexcept
{
  return normalize_clicks(clicks);
}

double grinder::operator()(const std::string& readable_clicks) const noexcept
{
  return normalize_clicks(string_to_specific(readable_clicks));
}

std::string operator>>(const double norm_setting, const grinder& g)
{
  return g << norm_setting;
}

std::string convert_setting(const auto& in_grinder, const std::string& click_str, const auto& out_grinder) noexcept
{
  const auto NORMALIZED_CLICKS = GRINDERS[in_grinder](click_str);
  return NORMALIZED_CLICKS > 0 ? (GRINDERS[out_grinder] << NORMALIZED_CLICKS) : ":(";
}

std::string convert_setting_id(size_t in_grinder, const std::string& click_str, size_t out_grinder) noexcept
{
  return convert_setting(in_grinder, click_str, out_grinder);
}
