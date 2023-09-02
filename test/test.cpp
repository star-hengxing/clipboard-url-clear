#include <string>

#include <boost/ut.hpp>

#include <clipboard.hpp>
#include <base/macro.hpp>

using namespace boost::ut;

NAMESPACE_BEGIN()

void url_test() noexcept
{
    "get_clear_url"_test = [] {
        "bilibili"_test = [] {
            expect(get_clear_url("https://www.bilibili.com/video/aaa?bbb") == "https://www.bilibili.com/video/aaa");
            expect(get_clear_url("http://www.bilibili.com/video/aaa?bbb") == "http://www.bilibili.com/video/aaa");
        };

        "tieba"_test = [] {
            expect(get_clear_url("https://tieba.baidu.com/aaa?bbb") == "https://tieba.baidu.com/aaa");
            expect(get_clear_url("http://tieba.baidu.com/aaa?bbb") == "http://tieba.baidu.com/aaa");
        };

        "zhihu"_test = [] {
            expect(get_clear_url("https://www.zhihu.com/question/aaa/answer/bbb?ccc") == "https://www.zhihu.com/question/aaa/answer/bbb");
            expect(get_clear_url("http://www.zhihu.com/question/aaa/answer/bbb?ccc") == "http://www.zhihu.com/question/aaa/answer/bbb");
            expect(get_clear_url("https://zhuanlan.zhihu.com/p/aaa?bbb") == "https://zhuanlan.zhihu.com/p/aaa");
            expect(get_clear_url("http://zhuanlan.zhihu.com/p/aaa?bbb") == "http://zhuanlan.zhihu.com/p/aaa");
        };

        "random"_test = [] {
            auto const src = std::string{"https://tieba.baidu.com/aaa?bbb"};
            auto const dst = std::string_view{"https://tieba.baidu.com/aaa"};
            for (auto c : {' ', '\n', '"'})
            {
                expect(get_clear_url(src + c + "abcd") == dst);
            }
        };

        "reserved url parameters"_test = [] {
            expect(get_clear_url("https://tieba.baidu.com/f?kw=aaa&bbb=ccc") == "https://tieba.baidu.com/f?kw=aaa");
            expect(get_clear_url("https://www.bilibili.com/video/aaa?p=1&bbb=ccc") == "https://www.bilibili.com/video/aaa?p=1");
        };
    };
}

void database_test() noexcept
{
    "parse url database"_test = [] {
        "single url"_test = [] {
            auto table = Table::read("baidu.com,key1,key2");
            expect(table.domains.front() == "baidu.com");
            expect(table.url_keys.front()[0] == "key1");
            expect(table.url_keys.front()[1] == "key2");
        };
        "multiple url"_test = [] {
            auto table = Table::read("bilibili.com,p\nzhihu.com\ntieba.baidu.com,kw\nxiaohongshu.com");
            expect(table.domains.size() == table.url_keys.size());
            expect(table.domains[0] == "bilibili.com");
            expect(table.domains[1] == "zhihu.com");
            expect(table.domains[2] == "tieba.baidu.com");
            expect(table.domains[3] == "xiaohongshu.com");
            expect(table.url_keys[0][0] == "p");
            expect(table.url_keys[1].empty());
            expect(table.url_keys[2][0] == "kw");
            expect(table.url_keys[3].empty());
        };
    };
}

void http_test() noexcept
{
    constexpr std::string_view response = "HTTP/1.1 302 Found\r\nContent-Type: text/html;\r\ncharset=utf-8\r\nConnection: keep-alive\r\nBili-Trace-Id: 123456789\r\nLocation: https://www.bilibili.com/video/abcdefg?key1=value1&p=1&key3=value3";

    "get location"_test = [&] {
        // no
        expect(get_location("").empty());
        expect(get_location("HTTP/1.1 302 Found\r\n").empty());
        expect(get_location("Location: ").empty());
        expect(get_location("Location: https://www.").empty());
        expect(get_location("https://www.bilibili.com/video/abcdefg").empty());
        // yes
        expect(get_location(response) == "https://www.bilibili.com/video/abcdefg?p=1");
        expect(get_location("Location: https://www.bilibili.com/video/abcdefg") == "https://www.bilibili.com/video/abcdefg");
    };
}

NAMESPACE_END()

int main()
{
    url_test();
    database_test();
    http_test();
}
