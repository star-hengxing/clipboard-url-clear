set_kind("binary")
set_default(false)
set_rundir("$(projectdir)")
add_packages("boost_ut")

target("test")
    add_tests("default")
    
    add_files("test.cpp")
    add_includedirs(path.join("$(projectdir)", "src"))

    add_cxxflags("cl::-wd4003")

    add_deps("component")
