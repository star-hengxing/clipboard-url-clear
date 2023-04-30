#pragma once

#include <string_view>
#include <string>

void clipboard_handle() noexcept;
// b23.tv/xxxxxxx
std::string b23_to_source(const std::string_view short_url) noexcept;

std::string get_clear_url(const std::string_view string) noexcept;
