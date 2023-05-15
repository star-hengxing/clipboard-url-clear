#include <string_view>
#include <string>

#include <cpr/cpr.h>

std::string b23_to_source(const std::string_view short_url) noexcept
{
    const auto redirect_count = (short_url.starts_with("https") ? 0L : 1L);
    cpr::Response response = cpr::Head
    (
        cpr::Url{short_url.data(), short_url.size()},
        cpr::Redirect{redirect_count}
    );

    const auto link = response.header["Location"];
    if (link.empty())
        return {};

    const auto index = link.find('?');
    if (index == std::string::npos)
        return {};

    return link.substr(0, index);
}
