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

rule("module.program")
    on_load(function (target)
        target:set("kind", "binary")
        target:set("rundir", "$(projectdir)")
        if target:is_plat("windows") and target:get("runtimes") == "MT" then
            target:add("packages", "vc-ltl5")
        end
    end)

rule("module.component")
    on_load(function (target)
        if is_mode("debug") then
            target:set("kind", "shared")
            if target:is_plat("windows") then
                import("core.project.rule")
                local rule = rule.rule("utils.symbols.export_all")
                target:rule_add(rule)
                target:extraconf_set("rules", "utils.symbols.export_all", {export_classes = true})
            end
        elseif is_mode("release") then
            target:set("kind", "static")
        else
            raise("Unknown build kind")
        end
    end)

rule("module.test")
    on_load(function (target)
        if not has_config("test") then
            target:set("enabled", false)
            return
        end

        target:set("policy", "build.warning", true)
        target:set("rundir", os.projectdir())
        target:set("group", "test")
        target:add("packages", "boost_ut")
    end)

    after_build(function (target)
        os.exec("xmake run -g test")
    end)
