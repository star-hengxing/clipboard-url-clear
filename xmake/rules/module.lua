rule("module.component")
    on_load(function (target)
        if is_mode("debug") then
            target:set("kind", "shared")
            if is_plat("windows") then
                import("core.project.rule")
                local rule = rule.rule("utils.symbols.export_all")
                target:rule_add(rule)
                target:extraconf_set("rules", "utils.symbols.export_all", {export_classes = true})
            end
        elseif is_mode("release") then
            target:set("kind", "static")
        else
            assert(false, "Unknown build kind")
        end

        if is_plat("windows") then
            target:add("defines", "WIN32_LEAN_AND_MEAN")
        end
    end)
rule_end()

rule("module.test")
    on_load(function (target)
        if not has_config("test") then
            target:set("enabled", false)
            return
        end

        target:set("optimize", "none")
        target:set("symbols", "debug")
        target:set("policy", "build.warning", true)
        target:set("rundir", "$(projectdir)")
        target:set("group", "test")

        if is_plat("windows") then
            target:set("runtimes", "MDd")
        end
    end)
rule_end()
