#pragma once

#include <algorithm>
#include <array>
#include <iterator>
#include <limits>
#include <string>

namespace utl {
const auto ERROR_CODE = std::numeric_limits<int>::min();

[[nodiscard]] bool is_digit(char) noexcept;

template <typename it_type, size_t jump_size = 2>
class jumping_iterator : public it_type {

  public:
  jumping_iterator& operator++()
  {
    std::advance(*this, jump_size);
    return *this;
  }

  jumping_iterator operator++(int)
  {
    const jumping_iterator tmp = *this;
    std::advance(*this, jump_size);
    return tmp;
  }
};

int stpi(const std::string&) noexcept;
std::string pits(int) noexcept;

template <typename key, typename value, std::size_t size>
class map {
  using data_array = std::array<std::pair<key, value>, size>;
  data_array data {};
  const value ERROR_VALUE {};

  public:
  explicit consteval map(data_array d) noexcept
      : data(std::move(d))
  {
  }

  constexpr const value& at(const key& k) const
  {
    const auto itr = std::find_if(begin(data), end(data),
        [&k](const auto& v) { return v.first == k; });
    return itr != data.end() ? itr->second : ERROR_VALUE;
  }

  [[nodiscard]] constexpr const value& operator[](size_t pos) const noexcept
  {
    return data[pos].second;
  }

  [[nodiscard]] constexpr const value& at(size_t pos) const noexcept
  {
    return data.at(pos).second;
  }

  [[nodiscard]] constexpr std::array<key, size> key_list() const noexcept
  {
    std::array<key, size> ret {};
    std::transform(data.begin(), data.end(), ret.begin(), [](const auto& elm) { return elm.first; });
    return ret;
  }
};
} // namespace utl
