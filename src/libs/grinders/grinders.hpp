#pragma once
#include "python_decl.hpp"
#include <array>
#include <cmath>
#include <initializer_list>
#include <sstream>
#include <string>
#include <string_view>
#include <utility/utility.hpp>
#include <utility>

class grinder {
  const double CLICK_VALUE { 0.00 };

  const std::initializer_list<int> FORMATTING_VALUES {};

  public:
  grinder() = default;

  explicit consteval grinder(int h_clicks)
      : CLICK_VALUE(100.0 / h_clicks)
  {
  }

  consteval grinder(int h_clicks, std::initializer_list<int> formatting_values)
      : CLICK_VALUE(100.0 / h_clicks)
      , FORMATTING_VALUES(formatting_values)
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

// Needed to avoid a temporary creation that resoults in a non-constexpr constructor
PYTHON_INITIALIZER

// clang-format off
const auto GRINDERS { []() consteval {
    using namespace std::literals::string_view_literals;
const std::array<std::pair<std::string_view, grinder>, PYTHON_SIZE> grinders { { PYTHON_MAP } };
return utl::map { grinders };
}()};
// clang-format on

constexpr auto supported_grinders() noexcept
{
  return GRINDERS.key_list();
}

[[nodiscard]] std::string convert_setting(const auto&, const std::string&, const auto&) noexcept;
[[nodiscard]] std::string convert_setting_id(size_t, const std::string&, size_t) noexcept;
