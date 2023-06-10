# Clipboard URL Clear

Now support platform:

- Windows

Now support link:

- zhihu.com/aaa?bbb -> zhihu.com/aaa
- b23.tv/aaa -> https://www.bilibili.com/bbb
- tieba.baidu.com/aaa?bbb -> https://tieba.baidu.com/aaa

# Getting started

## Prerequisites

- [xmake](https://xmake.io/#/guide/installation)
- Requires C++20 compiler.

## Setup

- [Visual Studio](https://visualstudio.microsoft.com)(If you just want to build without developing, download the [Microsoft C++ Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools))

- Recommend use [scoop](https://scoop.sh) as package manager on Windows.

```sh
scoop install xmake
```

## Build

Clone repo, then try

```sh
xmake -y
```

After build, try

```sh
xmake run
```

## Test

```sh
xmake f -m debug --test=y
xmake build -g test
xmake run -g test
```

# Credits

- [clip](https://github.com/dacap/clip)
- [cpr](https://github.com/libcpr/cpr)
- [ada](https://github.com/ada-url/ada)
- [fast_io](https://github.com/cppfastio/fast_io)
- [VC-LTL5](https://github.com/Chuyu-Team/VC-LTL5)
