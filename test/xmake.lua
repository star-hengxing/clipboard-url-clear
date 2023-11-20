add_rules("module.test")

target("test")
    set_kind("binary")
    add_tests("default")
    
    add_files("test.cpp")
    add_includedirs(path.join("$(projectdir)", "src"))

    add_cxxflags("cl::-wd4003")

    add_deps("component")
