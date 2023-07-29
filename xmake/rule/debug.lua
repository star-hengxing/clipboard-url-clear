rule("debug.asan")
    on_load(function (target)
        target:add("cxflags", "-fsanitize=address")
        target:add("ldflags", "-fsanitize=address")

        local msvc = target:toolchain("msvc")
        if target:kind() == "binary" and msvc then
            local cl = assert(import("lib.detect.find_tool")("cl", {envs = msvc:runenvs()}), "cl not found!")
            target:add("runenvs", "Path", path.directory(cl.program))
        end
    end)
