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
    end)
rule_end()

rule("module.test")
    on_load(function (target)
        if not has_config("test") then
            target:set("enabled", false)
            return
        end

        target:set("policy", "build.warning", true)
        target:set("rundir", "$(projectdir)")
        target:set("group", "test")
        target:add("packages", "boost_ut")
    end)
rule_end()
