#pragma once
#include <string>

[[nodiscard]] std::string convert_setting(const auto&, const std::string&, const auto&) noexcept;
[[nodiscard]] std::string convert_setting_id(size_t, const std::string&, size_t) noexcept;
[[nodiscard]] std::string default_setting(const auto&) noexcept;
[[nodiscard]] std::string default_setting_id(const size_t) noexcept;
