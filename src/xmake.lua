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

    add_packages("clip", "ada", "zxing-cpp", "fast_io", "cppitertools")
    if get_config("http_backend") == "cpr" then
        add_defines("HTTP_BACKEND_CPR")
        add_packages("cpr")
    else
        add_packages("cpp-httplib")
    end

target("clear")
    add_rules("module.program")
    add_files("main.cpp")

    if is_plat("windows") then
        add_syslinks("user32")
    end

    add_deps("component")
