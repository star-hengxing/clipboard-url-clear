if is_plat("windows") then
    add_defines("WIN32_LEAN_AND_MEAN")
end

target("component")
    set_kind("$(kind)")
    add_rules("module.component")
    add_files("*.cpp|main.cpp")
    add_headerfiles("*.hpp")

    add_cxxflags("cl::-wd4003")

    add_packages("clip", "cpr", "ada", "fast_io", "cppitertools")

target("clear")
    add_rules("module.program")
    set_values("upx.flags", "--best")

    add_files("main.cpp")

    if is_plat("windows") then
        add_syslinks("user32")
    end

    add_deps("component")
