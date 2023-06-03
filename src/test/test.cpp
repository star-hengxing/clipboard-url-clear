#include <boost/ut.hpp>

#include <clipboard.hpp>

using namespace boost::ut;

int main()
{
    "bilibili"_test = [] {
        expect(get_clear_url("https://www.bilibili.com/video/aaa?bbb") == "https://www.bilibili.com/video/aaa");
    };

    "tieba"_test = [] {
        expect(get_clear_url("https://tieba.baidu.com/aaa?bbb") == "https://tieba.baidu.com/aaa");
    };

    "zhihu"_test = [] {
        expect(get_clear_url("https://www.zhihu.com/question/aaa/answer/bbb?ccc") == "https://www.zhihu.com/question/aaa/answer/bbb");
        expect(get_clear_url("https://zhuanlan.zhihu.com/p/aaa?bbb") == "https://zhuanlan.zhihu.com/p/aaa");
    };

    "random"_test = [] {
        expect(get_clear_url("a\nhttps://tieba.baidu.com/aaa?bbb") == "https://tieba.baidu.com/aaa");
    };
}
