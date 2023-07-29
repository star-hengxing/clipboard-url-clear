#pragma once

#include <vector>
#include <string>
#include <string_view>

void clipboard_handle() noexcept;
// b23.tv/xxxxxxx
std::string b23_to_source(const std::string_view short_url) noexcept;
// only support single link
std::string get_clear_url(const std::string_view string) noexcept;
// read urls form file
std::vector<std::string> read_urls(const std::string_view filename) noexcept;
