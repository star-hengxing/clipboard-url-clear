# Clipboard URL Clear

clear your clipboard link.

Now support platform:

- Windows

Now support link:

- zhihu.com/xxx?yyy -> zhihu.com/xxx
- b23.tv/xxx -> https://www.bilibili.com
- tieba.baidu.com/xxx?yyy -> https://tieba.baidu.com/xxx

# Getting started

## Dependencies

- [xmake](https://xmake.io/#/guide/installation)
- Requires C++20 compiler.

## Setup

Install msvc toolchain.

Recommend use [scoop](https://scoop.sh/) as package manager.

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

# Dependent third-party libraries

- [clip](https://github.com/dacap/clip)
- [ctre](https://github.com/hanickadot/compile-time-regular-expressions)
- [cpr](https://github.com/libcpr/cpr)
- [fast_io](https://github.com/cppfastio/fast_io)
