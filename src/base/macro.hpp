#pragma once

#ifndef NAMESPACE_BEGIN
#define NAMESPACE_BEGIN(name) namespace name {
#endif

#ifndef NAMESPACE_END
#define NAMESPACE_END(name) }
#endif

#ifdef _MSC_VER
#define ALWAYS_INLINE __forceinline
#else
#define ALWAYS_INLINE [[gnu::always_inline]]
#endif

#if defined(LIBRARY_DLL)
    #if defined(_WIN32) || defined(__CYGWIN__)
        #ifdef __GNUC__
            #define LIBRARY_EXPORT __attribute__(dllexport)
            #define LIBRARY_IMPORT __attribute__(dllimport)
        #else
            #define LIBRARY_EXPORT __declspec(dllexport)
            #define LIBRARY_IMPORT __declspec(dllimport)
        #endif
    #elif defined(__GNUC__) || defined(__clang__)
        #define LIBRARY_EXPORT __attribute__((visibility ("default")))
        #define LIBRARY_IMPORT __attribute__((visibility ("default")))
    #endif
#else
#define LIBRARY_EXPORT
#define LIBRARY_IMPORT
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define LIBRARY_DEBUG
#else
#define LIBRARY_RELEASE
#endif

// https://stackoverflow.com/questions/32432450/what-is-standard-defer-finalizer-implementation-in-c
struct defer_dummy{};

template <typename F>
struct deferrer
{
    F f;
    ~deferrer()
    {
        f();
    }
};

template <typename F>
auto operator * (defer_dummy, F f) noexcept -> deferrer<F>
{
    return {f};
}

#define DEFER_CONCAT(LINE) scope_guard_##LINE
#define DEFER_LINE(LINE) DEFER_CONCAT(LINE)
/**
* golang-style operation, RAII wrapper for third-party c library
* example: defer { free(ptr); };
*/
#define defer auto DEFER_LINE(__LINE__) = ::defer_dummy{} * [&]()
