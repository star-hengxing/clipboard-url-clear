-- dev

if is_mode("debug") then
    add_requireconfs("*", {configs = {shared = true}})
end

-- cross-platform clipboard api
add_requires("clip")
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

package("clip")
    set_homepage("https://github.com/dacap/clip")
    set_description("Library to copy/retrieve content to/from the clipboard/pasteboard.")
    set_license("MIT")

    add_urls("https://github.com/dacap/clip/archive/refs/tags/$(version).tar.gz",
             "https://github.com/dacap/clip.git")

    add_versions("v1.7", "f494d306f3425e984368cbd94ffb213e0a3b3d44c3ab169e5134788d3342535c")

    if is_plat("windows") then
        add_syslinks("shlwapi", "ole32", "user32")
    end

    on_install("windows", function(package)
        io.writefile("xmake.lua", [[
            add_rules("mode.debug", "mode.release")
            set_languages("c++11")
            target("clip")
                set_kind("$(kind)")
                add_files("clip.cpp", "image.cpp")
                add_files("clip_win.cpp")
                add_headerfiles("*.h", {prefixdir = "clip"})
                if is_plat("windows") and is_kind("shared") then
                    add_rules("utils.symbols.export_all", {export_classes = true})
                end
        ]])
        import("package.tools.xmake").install(package)
    end)

    on_test(function(package)
        assert(package:check_cxxsnippets({ test = [[
              #include <clip/clip.h>
              #include <string>
              void test() { clip::set_text("foo"); }
          ]]}
        ))
    end)
