#include <string_view>
#include <string>

#ifdef HTTP_BACKEND_CPR
    #include <fast_io.h>
    #include <cpr/cpr.h>
#else
    #include <httplib.h>
#endif
#include <cppitertools/enumerate.hpp>

#include "clipboard.hpp"

// ms
inline constexpr auto TIME_OUT = 1000;

std::string get_location(const std::string_view response) noexcept
{
    constexpr std::string_view LOCATION{"Location: "};

    if (response.size() < LOCATION.size())
        return {};

    auto const index = response.find(LOCATION);
    if (index == std::string_view::npos)
        return {};

    auto const tmp = response.substr(index + LOCATION.size());
    for (auto const [i, v] : iter::enumerate(tmp))
    {
        if (v == '\r')
        {
            if (i + 1 < tmp.size() && tmp[i + 1] == '\n')
                return get_clear_url(tmp.substr(0, i));
            else
                return {};
        }
    }
    // missing "\r\n"? try
    return get_clear_url(tmp);
}

std::string b23_to_source(const std::string_view short_url) noexcept
{
#ifdef HTTP_BACKEND_CPR
    std::string tmp;
    std::string_view url;
    if (!short_url.starts_with("https"))
    {
        tmp = fast_io::concat("https", short_url.substr(4, short_url.size() - 4));
        url = tmp;
    }
    else
    {
        url = short_url;
    }

    cpr::Response response = cpr::Head
    (
        cpr::Url{url.data(), url.size()},
        cpr::Redirect{0L},
        cpr::Timeout(TIME_OUT)
    );

    auto const link = response.header["Location"];
#else
    httplib::Client client{"https://b23.tv"};
    client.set_connection_timeout(0, 1000000); // 1000 milliseconds
    httplib::Result result = client.Get(std::string{short_url});

    auto const link = result->get_header_value("Location");
#endif

    if (link.empty())
        return {};

    return get_clear_url(link);
}
