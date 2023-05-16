#include <string_view>
#include <string>

#include <fast_io.h>
#include <cpr/cpr.h>

std::string b23_to_source(const std::string_view short_url) noexcept
{
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
        cpr::Redirect{0L}
    );

    const auto link = response.header["Location"];
    if (link.empty())
        return {};

    const auto index = link.find('?');
    if (index == std::string::npos)
        return {};

    return link.substr(0, index);
}
