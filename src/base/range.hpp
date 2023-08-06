#pragma once

#ifdef USE_MODULES
import <ranges>;
#else
#include <ranges>
#endif

#include "basic_type.hpp"

template <std::integral T>
struct range
{
private:
    T start, stop, step;

private:
    struct range_iterator
    {
    private:
        T value, step;

    public:
        constexpr range_iterator(T value, T step) : value(value), step(step) {}
        T& operator * () { return value; }
        range_iterator& operator ++ () { value += step; return *this; }
        bool operator != (const range_iterator& other) { return value < other.value; }
    };

public:
    constexpr range(T start, T stop, T step = 1) : start(start), stop(stop), step(step) {}
    constexpr range(T stop) : range(0, stop) {}
    constexpr range_iterator begin() { return range_iterator(start, step); }
    constexpr range_iterator end() { return range_iterator(stop, step); }

    range() = delete;
};

constexpr auto split(const std::string_view& sv, const std::string_view& delim)
{
    return sv
        | std::ranges::views::split(delim)
        | std::ranges::views::transform([](auto&& rng)
    {
        return std::string_view(std::addressof(*rng.begin()), std::ranges::distance(rng));
    });
}

#if defined(__clang__)

template <typename T>
struct Enumerate
{
private:
    using value = T;
    using self = Enumerate;

private:
    T it;
    usize index;
    const usize step;
    decltype(std::begin(it)) begin_;
    const decltype(std::end(it)) end_;

public:
    Enumerate(value it, usize step) : it(it), index(0), step(step),
        begin_(std::begin(it)), end_(std::end(it)) {}

    auto begin() -> self& { return *this; }
    auto end()   -> self&   { return *this; }

    auto operator != (const Enumerate&) const -> bool
    {
        return begin_ != end_;
    }

    auto operator ++ ()
    {
        begin_++;
        index  += step;
    }

    auto operator * () const -> std::pair<usize, decltype(*begin_)>
    {
        return {index, *begin_};
    }
};

template <std::ranges::range T>
auto enumerate(T& it, usize step = 1) -> Enumerate<T>
{
    return {std::forward<T>(it), step};
}

#else

template <typename T>
struct enumerated_element
{
    usize index;
    T& element;
};

template <std::ranges::range T>
constexpr auto enumerate(T& range, usize step = 1)
{
    return range | std::views::transform(
        [index = usize{}, step](auto& element) mutable
        {
            const auto tmp = index;
            index += step;
            return enumerated_element{tmp, element};
        }
    );
}

#endif // defined(__clang__)
