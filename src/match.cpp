#include "clipboard.hpp"

std::string get_clear_url(const std::string_view string) noexcept
{
    // TODO: use regex
    auto start = string.find("https://");
    if (start == std::string_view::npos)
        return {};

    auto bili = string.find("b23.tv/", start);
    if (bili != std::string_view::npos)
    {
        // short url identifier has 7 byte
        const auto link_size = std::string_view{"https://b23.tv/"}.size() + 7;
        if (start + link_size >= string.size())
            return {};

        return b23_to_source(string.substr(start, link_size));
    }

    auto end = string.find('?', start);
    if (end != std::string_view::npos)
    {
        auto url = string.substr(start, end - start);
        if (url.find("zhihu.com", start) != std::string_view::npos)
            return std::string{url};
    }

    return {};
}
