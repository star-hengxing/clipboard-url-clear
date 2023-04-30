#include <fast_io.h>

#include <clipboard.hpp>

void test(std::string_view str) noexcept
{
    auto result = get_clear_url(str);
    if (result.empty())
    {
        perrln(str);
    }
}

int main(int argc, char** argv)
{
    
}
