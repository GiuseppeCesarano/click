#pragma once

#include <algorithm>
#include <array>
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

template <typename it_type>
struct non_owning_range {
  const it_type BEGIN {};
  const it_type END {};

  consteval non_owning_range() = default;

  template <typename T>
  explicit consteval non_owning_range(const T& c) noexcept
      : BEGIN(c.begin())
      , END(c.end())
  {
  }

  [[nodiscard]] constexpr auto begin() const noexcept
  {
    return BEGIN;
  }

  [[nodiscard]] constexpr auto end() const noexcept
  {
    return END;
  }

  [[nodiscard]] constexpr size_t size() const noexcept
  {
    return static_cast<size_t>(END - BEGIN);
  }

  [[nodiscard]] constexpr bool is_empty() const noexcept
  {
    return size() == 0;
  }
};

int stpi(const std::string&) noexcept;
std::string pits(int) noexcept;

template <typename key, typename value, std::size_t size>
class map {
  using data_array = std::array<std::pair<key, value>, size>;
  data_array data {};
  static constexpr value ERROR_VALUE {};

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
