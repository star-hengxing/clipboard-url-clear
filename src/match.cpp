#include <string_view>
#include <string>

#include <ada.h>

#include "clipboard.hpp"

static constexpr std::string_view QUERY_PARAMETERS_DOMAIN[]
{
    std::string_view{"bilibili.com"},
    std::string_view{"zhihu.com"},
    std::string_view{"tieba.baidu.com"},
};

static constexpr auto B23_TV = std::string_view{"b23.tv"};

static bool is_letter(char c) noexcept
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static bool is_number(char c) noexcept
{
    return c >= '0' && c <= '9';
}

static bool is_alpha(char c) noexcept
{
    return is_letter(c) || is_number(c);
}

bool valid_url_char(char target) noexcept
{
    constexpr std::string_view chars = "./_&=#?-%~[]";

    for (auto c : chars)
    {
        if (target == c)
        {
            return true;
        }
    }
    return false;
}

static std::string_view find_url(const std::string_view string) noexcept
{
    const auto start = string.find("http");
    if (start == std::string::npos)
        return {};

    std::size_t offset;
    auto tmp = string.substr(start, string.size() - start);
    if (tmp.starts_with("https://")) [[likely]]
    {
        offset = 4;
    }
    else if (tmp.starts_with("http://")) [[unlikely]]
    {
        offset = 3;
    }
    else
    {
        return {};
    }

    auto url_size = 4 + offset;
    const auto total_size = string.size();

    for (auto i = start + url_size; i < total_size; i += 1)
    {
        const auto c = string[i];
        if (!is_alpha(c) && !valid_url_char(c))
            break;

        url_size += 1;
    }

    return string.substr(start, url_size);
}

std::string get_clear_url(const std::string_view string) noexcept
{
    const auto target = find_url(string);
    if (target.empty())
        return {};

    auto url = ada::parse<ada::url_aggregator>(target);
    // ignore invalid url
    if (!url || url->has_empty_hostname())
    {
        return {};
    }

    const auto hostname = url->get_hostname();
    // get long link from short link
    if (hostname == B23_TV)
    {
        // https://b23.tv/aaa?bbb
        url->set_search({});
        return b23_to_source(url->get_href());
    }

    for (auto&& domain : QUERY_PARAMETERS_DOMAIN)
    {
        if (hostname.ends_with(domain))
        {
            url->set_search({});
            return std::string{url->get_href()};
        }
    }

    return {};
}
