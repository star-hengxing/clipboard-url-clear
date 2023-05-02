#include <string_view>
#include <string>

#include <fast_io.h>

#include "clipboard.hpp"

static constexpr auto B23_TV = std::string_view{"b23.tv/"};
static constexpr auto BILIBILI = std::string_view{"bilibili.com"};
static constexpr auto ZHIHU = std::string_view{"zhihu.com"};

std::string get_clear_url(const std::string_view string) noexcept
{
    // TODO: use regex
    auto bilibili_start = string.find(B23_TV);
    if (bilibili_start != std::string_view::npos)
    {
        // short url identifier has 7 byte
        const auto link_size = B23_TV.size() + 7;
        if (bilibili_start + link_size > string.size())
            return {};

        const auto url = fast_io::concat("https://", string.substr(bilibili_start, link_size));
        return b23_to_source(url);
    }

    auto start = string.find(ZHIHU);
    if (start != std::string_view::npos)
    {
        auto end = string.find('?', start);
        if (end != std::string_view::npos)
        {
            const auto url = fast_io::concat("https://", string.substr(start, end - start));
            return std::string{url};
        }
    }

    start = string.find(BILIBILI);
    if (start == std::string_view::npos)
        return {};

    auto end = string.find('?', start);
    if (end != std::string_view::npos)
    {
        const auto url = fast_io::concat("https://", string.substr(start, end - start));
        return std::string{url};
    }

    return {};
}
