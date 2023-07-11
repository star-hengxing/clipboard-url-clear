if is_plat("windows") then
    add_defines("WIN32_LEAN_AND_MEAN")
end

target("component")
    set_kind("$(kind)")
    add_rules("module.component")
    add_files("*.cpp")
    remove_files("main.cpp")
    add_headerfiles("*.hpp")

    add_packages("clip", "cpr", "ada", "fast_io")

target("clear")
    add_rules("module.program")
    add_files("main.cpp")

    if is_plat("windows") then
        add_syslinks("user32")
    end

    add_deps("component")

    after_build(function (target)
        import("lib.detect.find_tool")

        if not is_mode("release") then
            return
        end

        local upx = assert(find_tool("upx"), "upx not found!")
        local exe = path.join("build", path.filename(target:targetfile()))

        os.tryrm(exe)
        os.execv(upx.program, {target:targetfile(), "-o", exe})
    end)
