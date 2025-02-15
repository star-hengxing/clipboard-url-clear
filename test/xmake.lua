add_rules("module.test")

target("test")
    add_tests("default")
    add_files("test.cpp")
    add_deps("component")
