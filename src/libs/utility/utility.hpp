#pragma once

#include <algorithm>
#include <array>
#include <limits>
#include <string>

namespace utl {
const auto ERROR_CODE = std::numeric_limits<int>::min();

int stpi(const std::string&) noexcept;
std::string pits(int) noexcept;

template <typename key, typename value, std::size_t size>
class map {
  using data_array = std::array<std::pair<key, value>, size>;
  data_array data {};
  const value ERROR_VALUE {};

  public:
  explicit consteval map(data_array d)
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
