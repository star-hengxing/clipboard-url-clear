rule("module.program")
    on_load(function (target)
        target:set("kind", "binary")
        target:set("rundir", "$(projectdir)")
        if target:is_plat("windows") and target:get("runtimes") == "MT" then
            target:add("packages", "vc-ltl5")
        end
    end)

    after_build(function (target)
        local enabled = target:extraconf("rules", "module.program", "upx")
        if (not enabled) or (not is_mode("release")) then
            return
        end

        local upx = assert(import("lib.detect.find_tool")("upx"), "upx not found!")
        local file = path.join("build", path.filename(target:targetfile()))

        os.tryrm(file)
        os.execv(upx.program, {target:targetfile(), "-o", file})
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
