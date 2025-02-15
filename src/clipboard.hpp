#pragma once

#include <vector>
#include <string>
#include <string_view>

#include "base/macro.hpp"

LIBRARY_API void clipboard_handle() noexcept;
// b23.tv/xxxxxxx
LIBRARY_API std::string b23_to_source(const std::string_view short_url) noexcept;
// only support single link
LIBRARY_API std::string get_clear_url(const std::string_view string) noexcept;

LIBRARY_API std::string get_location(const std::string_view response) noexcept;

struct Table
{
public:
    const std::vector<std::string_view> domains;
    const std::vector<std::vector<std::string_view>> url_keys;

public:
    LIBRARY_API static Table read(std::string_view string) noexcept;
};
