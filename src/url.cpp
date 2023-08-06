#include <string>

#include <fast_io.h>

#include "clipboard.hpp"

Table Table::read(std::string_view string) noexcept
{
    if (string.empty())
        return {};

    std::vector<std::string_view> domains;
    std::vector<std::vector<std::string_view>> url_keys;

    auto start = string.data();
    auto const end = start + string.size();

    auto pos = start;
    auto has_domain = false;
    std::vector<std::string_view> tmp;
    while (pos < end)
    {
        auto const c = *pos;
        auto const size = static_cast<size_t>(pos - start);
        auto const str = std::string_view{start, size};
        if (c == ',')
        {
            if (has_domain)
            {
                tmp.push_back(str);
            }
            else
            {
                // domain is right? use ada parse?
                if (str.find('.') != std::string_view::npos)
                {
                    has_domain = true;
                    domains.push_back(str);
                }
                else
                {
                    perrln(fast_io::concat("Invalid domain: ", str));
                    // TODO: skip error row
                    std::exit(-1);
                }
            }

            start = pos + 1;
            pos = start;
        }
        else if (c == '\r' || c == '\n')
        {
            // domain has key?
            if (!str.empty())
            {
                if (has_domain)
                {
                    tmp.push_back(str);
                    // reset
                    has_domain = false;
                }
                else
                {
                    domains.push_back(str);
                }
            }
            url_keys.push_back(std::move(tmp));
            // CRLF or LF
            auto const skip_count = (*(pos + 1) == '\n') ? 2 : 1;
            start = pos + skip_count;
            pos = start;
        }
        else [[likely]]
        {
            pos += 1;
        }
    }

    // if current row end without CRLF
    if (start != pos)
    {
        auto const size = static_cast<size_t>(pos - start);
        auto const str = std::string_view{start, size};
        if (has_domain)
        {
            tmp.push_back(str);
        }
        else
        {
            domains.push_back(str);
        }

        url_keys.push_back(std::move(tmp));
    }

    return {domains, url_keys};
}
