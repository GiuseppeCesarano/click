#pragma once

#include <algorithm>
#include <array>
#include <iterator>
#include <limits>
#include <string>

namespace utl {
const auto ERROR_CODE = std::numeric_limits<int>::min();

struct is_digit : std::unary_function<char, bool> {
  constexpr bool operator()(const char c) const
  {
    return (c >= '0' && c <= '9');
  }
};

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

  constexpr const value& operator[](size_t pos) const { return data[pos].second; }

  constexpr const value& at(size_t pos) const { return data.at(pos).second; }

  constexpr std::array<key, size> key_list() const
  {
    std::array<key, size> ret {};
    auto ret_it = ret.begin();
    for (const auto& i : data) {
      *ret_it++ = i.first;
    }
    return ret;
  }
};
} // namespace utl
