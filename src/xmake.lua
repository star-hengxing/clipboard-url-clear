if is_plat("windows") then
    add_defines("WIN32_LEAN_AND_MEAN")
end

if is_mode("release") then
    add_packages("vc-ltl5")
end

target("component")
    set_kind("$(kind)")
    add_rules("module.component")
    add_files("*.cpp")
    remove_files("main.cpp")
    add_headerfiles("*.hpp")

    add_packages("clip", "ctre", "cpr", "ada", "fast_io")

target("clear")
    set_kind("binary")
    add_files("main.cpp")

    if is_plat("windows") then
        add_syslinks("user32")
    end

    add_deps("component")
