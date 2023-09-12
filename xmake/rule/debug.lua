rule("debug.asan")
    on_load(function (target)
        if not is_mode("debug") then
            return
        end

        import("lib.detect.find_tool")
        import("core.base.semver")

        target:add("cxflags", "-fsanitize=address")
        target:add("mxflags", "-fsanitize=address")
        target:add("ldflags", "-fsanitize=address")
        target:add("shflags", "-fsanitize=address")

        if not target:get("symbols") then
            target:set("symbols", "debug")
        end

        if target:is_plat("windows") and target:is_binary() then
            local msvc = target:toolchain("msvc")
            if msvc then
                local envs = msvc:runenvs()
                local vscmd_ver = envs and envs.VSCMD_VER
                if vscmd_ver and semver.match(vscmd_ver):ge("17.7") then
                    local cl = assert(find_tool("cl", {envs = envs}), "cl not found!")
                    target:add("runenvs", "Path", path.directory(cl.program))
                end
            end
        end
    end)
