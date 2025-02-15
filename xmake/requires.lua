-- dev

if has_config("dev") then
    add_requireconfs("*", {configs = {shared = true}})
end

-- cross-platform clipboard api
add_requires("clip")
-- https
add_requires("cpr", {configs = {ssl = true}})
-- url
add_requires("ada")
-- debug/concat
add_requires("fast_io")

add_requires("cppitertools")

if is_plat("windows") and is_mode("release") then
    add_requires("vc-ltl5")
end

if has_config("test") then
    add_requires("boost_ut")
end

package("fast_io")
    set_kind("library", {headeronly = true})
    set_homepage("https://github.com/cppfastio/fast_io")
    set_description("Significantly faster input/output for C++20")
    set_license("MIT")

    add_urls("https://github.com/cppfastio/fast_io.git")
    add_versions("2024.12.06", "dd78867b7ae27da71c2e6d5d4f543066c301c047")

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

    add_urls("https://github.com/dacap/clip.git")

    add_versions("2025.01.27", "a1a5fd11b420ad321b000eba4f736d53ef557e89")

    if is_plat("windows") then
        add_configs("shared", {description = "Build shared binaries.", default = false, type = "boolean", readonly = true})
        add_syslinks("shlwapi", "ole32", "user32", "advapi32")
        add_defines("CLIP_ENABLE_IMAGE=1")
    end

    on_install(function(package)
        io.writefile("xmake.lua", [[
            add_rules("mode.debug", "mode.release")
            set_languages("c++20")
            target("clip")
                set_kind("$(kind)")
                add_headerfiles("*.h", {prefixdir = "clip"})

                add_files("clip.cpp")
                add_files("image.cpp")
                if is_plat("windows") then
                    add_files("clip_win.cpp")
                    add_files("clip_win_bmp.cpp", "clip_win_wic.cpp")
                    add_defines("CLIP_ENABLE_IMAGE=1")
                end
                if is_plat("windows") then
                    add_syslinks("shlwapi", "ole32", "user32", "advapi32")
                end
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
