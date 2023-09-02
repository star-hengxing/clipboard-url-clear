#pragma once

#include <vector>
#include <string>
#include <string_view>

void clipboard_handle() noexcept;
// b23.tv/xxxxxxx
std::string b23_to_source(const std::string_view short_url) noexcept;
// only support single link
std::string get_clear_url(const std::string_view string) noexcept;

std::string get_location(const std::string_view response) noexcept;

struct Table
{
public:
    const std::vector<std::string_view> domains;
    const std::vector<std::vector<std::string_view>> url_keys;

public:
    static Table read(std::string_view string) noexcept;
};
