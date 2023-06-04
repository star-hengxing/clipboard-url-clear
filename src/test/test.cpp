#include <string>

#include <boost/ut.hpp>

#include <clipboard.hpp>

using namespace boost::ut;

int main()
{
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
        const auto src = std::string{"https://tieba.baidu.com/aaa?bbb"};
        const auto dst = std::string_view{"https://tieba.baidu.com/aaa"};
        for (auto c : {' ', '\n', '"'})
        {
            expect(get_clear_url(src + c + "abcd") == dst);
        }
    };
}
