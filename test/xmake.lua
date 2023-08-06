add_rules("module.test")

add_includedirs(path.join("$(projectdir)", "src"))

target("test")
    set_kind("binary")
    add_files("test.cpp")

    add_cxxflags("cl::-wd4003")

    add_deps("component")
    add_packages("fast_io")
