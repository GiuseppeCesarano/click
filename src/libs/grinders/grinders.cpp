#include "grinders.hpp"
#include "python_decl.hpp"
#include <array>
#include <cmath>
#include <numeric>
#include <string>
#include <string_view>
#include <utility/utility.hpp>

namespace {
class grinder {
  const double CLICK_VALUE { 0.00 };

  using range = utl::non_owning_range<std::array<int, 0>::const_iterator>;
  const range FORMATTING_VALUES {};

  [[nodiscard]] int dotted_parser(const std::string& clicks_str) const noexcept
  {
    int res = utl::ERROR_CODE;
    using jit = utl::jumping_iterator<std::string::const_iterator, 2>;

    if ((clicks_str.size() == FORMATTING_VALUES.size() * 2 - 1) && std::all_of(jit { clicks_str.begin() }, jit { clicks_str.end() + 1 }, utl::is_digit)) {
      jit str_itr { clicks_str.begin() };
      res = std::reduce(FORMATTING_VALUES.begin(), FORMATTING_VALUES.end(), 0, [&str_itr](int reduced, int current) {
        return reduced + current * (*str_itr++ - '0');
      });
    }

    return res;
  }

  [[nodiscard]] std::string dotted_encoder(int clicks) const noexcept
  {
    std::string ret {};

#pragma unroll 3
    for (const auto VAL : FORMATTING_VALUES) {
      const auto NUM = static_cast<int>(std::round(clicks / VAL));
      clicks -= NUM * VAL;
      ret.append(std::to_string(NUM));
      ret.append(".");
    }
    ret.pop_back();

    return ret;
  }

  public:
  grinder() = default;

  explicit consteval grinder(const int h_clicks)
      : CLICK_VALUE(100.0 / h_clicks)
  {
  }

  template <size_t S>
  consteval grinder(const int h_clicks, const std::array<int, S>& formatting_values)
      : CLICK_VALUE(100.0 / h_clicks)
      , FORMATTING_VALUES(formatting_values)
  {
  }

  [[nodiscard]] constexpr double normalize_clicks(const int clicks) const noexcept
  {
    return clicks * CLICK_VALUE;
  }

  [[nodiscard]] constexpr int specify_clicks(const double clicks) const noexcept
  {
    return static_cast<int>(std::round(clicks / CLICK_VALUE));
  }

  [[nodiscard]] int string_to_specific(const std::string& clicks_str) const noexcept
  {
    return FORMATTING_VALUES.is_empty() ? utl::stpi(clicks_str) : dotted_parser(clicks_str);
  }

  [[nodiscard]] std::string specific_to_string(const int clicks) const noexcept
  {
    return FORMATTING_VALUES.is_empty() ? utl::pits(clicks) : dotted_encoder(clicks);
  }

  [[nodiscard]] std::string operator[](double normalized_click) const noexcept
  {
    return specific_to_string(specify_clicks(normalized_click));
  }

  [[nodiscard]] double operator[](const std::string& readable_clicks) const noexcept
  {
    return normalize_clicks(string_to_specific(readable_clicks));
  }
};

// Needed to avoid a temporary creation that resoults in a non-constexpr constructor
PYTHON_INITIALIZER

// clang-format off
  constexpr auto GRINDERS { []() consteval {
      using namespace std::literals::string_view_literals;
  constexpr std::array<std::pair<std::string_view, grinder>, PYTHON_SIZE> grinders { { PYTHON_MAP } };
  return utl::map { grinders };
  }()};
// clang-format on
}

std::string convert_setting(const auto& in_grinder, const std::string& click_str, const auto& out_grinder) noexcept
{
  const auto NORMALIZED_CLICKS = GRINDERS[in_grinder][click_str];
  return NORMALIZED_CLICKS > 0 ? (GRINDERS[out_grinder][NORMALIZED_CLICKS]) : ":(";
}

std::string convert_setting_id(const size_t in_grinder, const std::string& click_str, size_t out_grinder) noexcept
{
  return convert_setting(in_grinder, click_str, out_grinder);
}

std::string default_setting(const auto& in_grinder) noexcept
{
  constexpr auto DEF_CLICK = GRINDERS.at(std::string_view { "C40" }).normalize_clicks(18);
  return GRINDERS[in_grinder][DEF_CLICK];
}

std::string default_setting_id(const size_t in_grinder) noexcept
{
  return default_setting(in_grinder);
}
