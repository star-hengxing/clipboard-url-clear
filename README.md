# Clipboard URL Clear

Now support platform:

- Windows

# Feature

- Anti tracker.

```
bad:  https://www.zhihu.com/aaa?bbb
good: https://www.zhihu.com/aaa

bad:  https://tieba.baidu.com/aaa?bbb
good: https://tieba.baidu.com/aaa
```

We can customize domain in the `clear_domains.csv` file.

format:

```
domain0,key1,key2
domain1,key1,key2
```

> `clear_domains.csv` must be in the same directory as the program.

- Convert bilibili short url.

```
https://b23.tv/aaa -> https://www.bilibili.com/bbb
```

# Getting started

Download the program from the release page and run it directly in the command line.

# Build

## Prerequisites

- [xmake](https://xmake.io/#/guide/installation)
- Requires C++20 compiler.

## Setup

- [Visual Studio](https://visualstudio.microsoft.com)(If you just want to build without developing, download the [Microsoft C++ Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools))

- Recommend use [scoop](https://scoop.sh) as package manager on Windows.

```sh
scoop install xmake
```

Clone repo, then build and run.

```sh
xmake -y
xmake run
```

## Test

```sh
xmake test
```

# Credits

- [clip](https://github.com/dacap/clip)
- [cpr](https://github.com/libcpr/cpr)
- [ada](https://github.com/ada-url/ada)
- [fast_io](https://github.com/cppfastio/fast_io)
- [VC-LTL5](https://github.com/Chuyu-Team/VC-LTL5)
