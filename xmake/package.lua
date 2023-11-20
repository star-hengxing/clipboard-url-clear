-- dev

if is_mode("debug") then
    add_requireconfs("*", {configs = {shared = true}})
end

package("fast_io")
    set_kind("library", {headeronly = true})
    set_homepage("https://github.com/cppfastio/fast_io")
    set_description("Significantly faster input/output for C++20")
    set_license("MIT")

    add_urls("https://github.com/cppfastio/fast_io.git")
    add_versions("2023.11.06", "804d943e30df0da782538d508da6ea6e427fc2cf")

    on_install("windows", "linux", "macosx", "msys", "mingw", function (package)
        os.cp("include", package:installdir())
    end)

    on_test(function (package)
        assert(package:check_cxxsnippets({test = [[
            #include <fast_io.h>
            void test() {
                fast_io::io::print("Hello, fast_io world!\n");
            }
        ]]}, {configs = {languages = "c++20"}}))
    end)
package_end()

-- cross-platform clipboard api
add_requires("clip 1.5")
-- https
add_requires("cpr 1.10.3", {configs = {ssl = true}})
-- url
add_requires("ada v2.6.7")
-- debug/concat
add_requires("fast_io")

add_requires("cppitertools")

if is_plat("windows") and is_mode("release") then
    add_requires("vc-ltl5 5.0.7")
end

-- test

add_requires("boost_ut v1.1.9", {optional = true})
