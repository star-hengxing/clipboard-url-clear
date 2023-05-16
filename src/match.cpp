#include <string_view>
#include <string>

#include <ctre.hpp>
#include <ada.h>

#include "clipboard.hpp"

static constexpr std::string_view QUERY_PARAMETERS_DOMAIN[]
{
    std::string_view{"bilibili.com"},
    std::string_view{"zhihu.com"},
    std::string_view{"tieba.baidu.com"},
};

static constexpr auto B23_TV = std::string_view{"b23.tv"};
// https://github.com/hanickadot/compile-time-regular-expressions/issues/178
static constexpr auto REGEX_URL = ctll::fixed_string{R"((?<all>(http://www\.|https://www\.|http://|https://)?[a-zA-Z0-9]+([\-\.]{1}[a-z0-9]+)*\.[a-z]{2,5}(:[0-9]{1,5})?(/[^\s]*)?/?\b))"};

std::string get_clear_url(const std::string_view string) noexcept
{
    // TODO: optimize regex
    const auto [whole, a, b, c, d, e] = ctre::match<REGEX_URL>(string);
    if (!whole)
    {
        return {};
    }

    auto url = ada::parse<ada::url_aggregator>(whole.to_view());
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
