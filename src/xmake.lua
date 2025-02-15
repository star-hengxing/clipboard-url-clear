if is_plat("windows") then
    add_defines("WIN32_LEAN_AND_MEAN")
end

target("component")
    if has_config("dev") then
        set_kind("shared")
    else
        set_kind("$(kind)")
    end

    add_rules("module.component")
    add_files("*.cpp|main.cpp")
    add_includedirs(os.scriptdir(), {interface = true})
    add_headerfiles("*.hpp")

    add_cxxflags("cl::-wd4003", {public = true})

    add_packages("clip", "cpr", "ada", "zxing-cpp", "fast_io", "cppitertools")

target("clear")
    add_rules("module.program")
    add_files("main.cpp")

    if is_plat("windows") then
        add_syslinks("user32")
    end

    add_deps("component")
