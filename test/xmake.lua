target("test")
    set_kind("binary")
    set_default(false)
    add_tests("default")
    
    add_files("test.cpp")
    add_includedirs(path.join("$(projectdir)", "src"))

    add_cxxflags("cl::-wd4003")

    add_deps("component")
    add_packages("fast_io", "boost_ut")
