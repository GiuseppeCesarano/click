#pragma once
#include "../utility/utility.hpp"
#include <cmath>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

class grinder {
  const double CLICK_VALUE { 0.00 };

  /*  No need to free those since they will have
    the same lifetime of the program */
  int (*const string_to_clicks)(const std::string&) { [](const std::string&) { return utl::ERROR_CODE; } };
  std::string (*const clicks_to_string)(int) {};

  public:
  grinder() = default;

  consteval grinder(int h_clicks,
      int (*const str_to_clicks)(const std::string&),
      std::string (*const clicks_to_str)(int)) noexcept
      : CLICK_VALUE(100.0 / h_clicks)
      , string_to_clicks(str_to_clicks)
      , clicks_to_string(clicks_to_str)
  {
  }

  [[nodiscard]] constexpr double click_value() const noexcept;

  [[nodiscard]] constexpr double normalize_clicks(int) const noexcept;

  [[nodiscard]] constexpr int specify_clicks(double) const noexcept;

  [[nodiscard]] int string_to_specific(const std::string&) const noexcept;

  [[nodiscard]] std::string specific_to_string(int) const noexcept;

  [[nodiscard]] std::string operator<<(double) const noexcept;

  [[nodiscard]] constexpr double operator()(int) const noexcept;

  [[nodiscard]] double operator()(const std::string&) const noexcept;
};

// TODO: Migliora ste funzioni
template <const size_t CLICKS_PER_ROTATION, const size_t CLICKS_PER_NUMBER>
[[nodiscard]] int readable_to_clicks(const std::string& clicks_str)
{
  constexpr std::array<short, 3> NUM_VALS { CLICKS_PER_ROTATION, CLICKS_PER_NUMBER, 1 };
  int res { utl::ERROR_CODE };
  const unsigned short INPUT_EXPECTED_LENGHT { 5 };
  if (clicks_str.size() == INPUT_EXPECTED_LENGHT) {
    res = 0;
    size_t pos { 0 };
    for (const auto VAL : NUM_VALS) {
      if (clicks_str[pos] < '0' || clicks_str[pos] > '9') {
        res = utl::ERROR_CODE;
        break;
      }
      res += VAL * (clicks_str[pos] - '0');
      pos += 2;
    }
  }
  return res;
}

template <const size_t CLICKS_PER_ROTATION, const size_t CLICKS_PER_NUMBER>
[[nodiscard]] std::string clicks_to_readable(int clicks)
{
  std::stringstream ss;
  constexpr std::array<short, 3> NUM_VALS { CLICKS_PER_ROTATION, CLICKS_PER_NUMBER, 1 };
  for (const auto VAL : NUM_VALS) {
    int num = static_cast<int>(std::round(clicks / VAL));
    ss << num << '.';
    clicks -= num * VAL;
  }
  auto ret = ss.str();
  return { ret.begin(), ret.end() - 1 };
}

// clang-format off
const auto GRINDERS { []() consteval {
  using namespace std::literals::string_view_literals;

  const std::array<std::pair<std::string_view, grinder>, 4> grinders {{ 
    { "C40"sv, { 18, &utl::stpi, &utl::pits } },
    { "C40 Red Clicks"sv, { 36, &utl::stpi, &utl::pits } },
    { "Mini Mill"sv, { 8, &utl::stpi, &utl::pits } },
    { "JX-PRO"sv, { 113, &readable_to_clicks<40, 4>, &clicks_to_readable<40, 4> } } 
  }};

  return utl::map { grinders };
}()};
// clang-format on

constexpr auto supported_grinders() noexcept
{
  return GRINDERS.key_list();
}

[[nodiscard]] std::string convert_setting_id(size_t, const std::string&, size_t) noexcept;
[[nodiscard]] std::string convert_setting(const std::string&, const std::string&, const std::string&) noexcept;
