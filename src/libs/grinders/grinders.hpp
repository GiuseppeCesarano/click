#pragma once
#include "python_decl.hpp"
#include <array>
#include <string>
#include <utility/utility.hpp>

class grinder {
  const double CLICK_VALUE { 0.00 };

  using range = utl::range<std::array<int, 0>::const_iterator>;
  const range FORMATTING_VALUES {};

  [[nodiscard]] int dotted_parser(const std::string&) const noexcept;
  [[nodiscard]] std::string dotted_encoder(int) const noexcept;

  public:
  grinder() = default;

  explicit consteval grinder(int h_clicks)
      : CLICK_VALUE(100.0 / h_clicks)
  {
  }

  template <size_t S>
  consteval grinder(int h_clicks, const std::array<int, S>& formatting_values)
      : CLICK_VALUE(100.0 / h_clicks)
      , FORMATTING_VALUES(formatting_values)
  {
  }

  [[nodiscard]] constexpr double normalize_clicks(int) const noexcept;

  [[nodiscard]] constexpr int specify_clicks(double) const noexcept;

  [[nodiscard]] int string_to_specific(const std::string&) const noexcept;

  [[nodiscard]] std::string specific_to_string(int) const noexcept;

  [[nodiscard]] std::string operator[](double) const noexcept;

  [[nodiscard]] double operator[](const std::string&) const noexcept;
};

[[nodiscard]] std::string convert_setting(const auto&, const std::string&, const auto&) noexcept;
[[nodiscard]] std::string convert_setting_id(size_t, const std::string&, size_t) noexcept;
