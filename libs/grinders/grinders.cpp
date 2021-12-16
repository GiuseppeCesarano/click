#include "grinders.hpp"
#include "../utility/utility.hpp"
#include <array>
#include <string>

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
  return string_to_clicks(clicks_str);
}

std::string grinder::specific_to_string(int clicks) const noexcept
{
  return clicks_to_string(clicks);
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

std::string convert_setting_id(size_t in_grinder, const std::string& click_str, size_t out_grinder) noexcept
{
  const auto NORMALIZED_CLICKS = GRINDERS[in_grinder](click_str);
  return NORMALIZED_CLICKS > 0 ? (GRINDERS[out_grinder] << NORMALIZED_CLICKS) : ":(";
}

std::string convert_setting(const std::string& in_grinder, const std::string& click_str, const std::string& out_grinder) noexcept
{
  const auto NORMALIZED_CLICKS = GRINDERS.at(in_grinder)(click_str);
  return NORMALIZED_CLICKS > 0 ? (GRINDERS.at(out_grinder) << NORMALIZED_CLICKS) : ":(";
}
