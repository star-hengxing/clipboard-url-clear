#include <iostream>
#include <string_view>
#include <string>

#include <ada.h>
#include <fast_io.h>
#include <cppitertools/enumerate.hpp>

#include "base/macro.hpp"
#include "clipboard.hpp"

inline auto const database_string = fast_io::allocation_file_loader{"clear_domains.csv"};
inline auto const database = Table::read({database_string.data(), database_string.size()});

NAMESPACE_BEGIN()

constexpr auto B23_TV = std::string_view{"b23.tv"};

bool is_letter(char c) noexcept
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool is_number(char c) noexcept
{
    return c >= '0' && c <= '9';
}

bool is_alpha(char c) noexcept
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

std::string_view find_url(const std::string_view string) noexcept
{
    auto const start = string.find("http");
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
    auto const total_size = string.size();

    for (auto i = start + url_size; i < total_size; i += 1)
    {
        auto const c = string[i];
        if (!is_alpha(c) && !valid_url_char(c))
            break;

        url_size += 1;
    }

    return string.substr(start, url_size);
}

NAMESPACE_END()

std::string get_clear_url(const std::string_view string) noexcept
{
    auto const target = find_url(string);
    if (target.empty())
        return {};

    auto url = ada::parse<ada::url_aggregator>(target);
    // ignore invalid url
    if (!url || url->has_empty_hostname())
    {
        return {};
    }

    auto const hostname = url->get_hostname();
    // get long link from short link
    if (hostname == B23_TV)
    {
        // https://b23.tv/aaa?bbb
        url->set_search({});
        return b23_to_source(url->get_href());
    }

    for (auto [i, domain] : iter::enumerate(database.domains))
    {
        if (hostname.ends_with(domain))
        {
            if (!url->has_search())
            {
                return std::string{url->get_href()};
            }
            // need reserve?
            std::string search;
            auto params = ada::url_search_params{url->get_search()};
            if (params.size() != 0)
            {
                for (auto key : database.url_keys[i])
                {
                    auto const value = params.get(key);
                    if (value)
                    {
                        search = fast_io::concat(search, key, "=", value.value(), "&");
                    }
                }
            }

            if (search.empty())
            {
                // remove
                url->set_search({});
            }
            else
            {
                // remove last '&'
                search.pop_back();
                url->set_search(search);
            }

            return std::string{url->get_href()};
        }
    }

    return {};
}
