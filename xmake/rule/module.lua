rule("module.program")
    on_load(function (target)
        target:set("kind", "binary")
        target:set("rundir", "$(projectdir)")
        if target:is_plat("windows") and target:get("runtimes") == "MT" then
            target:add("packages", "vc-ltl5")
        end
    end)

    after_link(function (target)
        local enabled = target:extraconf("rules", "module.program", "upx")
        if (not enabled) or (not is_mode("release")) then
            return
        end

        import("core.project.depend")
        import("lib.detect.find_tool")

        local targetfile = target:targetfile()
        depend.on_changed(function ()
            local file = path.join("build", path.filename(targetfile))
            local upx = assert(find_tool("upx"), "upx not found!")

            os.tryrm(file)

            local argv = table.wrap(target:values("upx.flags"))
            table.insert(argv, targetfile)
            table.insert(argv, "-o")
            table.insert(argv, file)
            os.vrunv(upx.program, argv)
        end, {files = targetfile})
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
        end
    end)

rule("module.test")
    on_load(function (target)
        target:set("default", false)
        target:set("policy", "build.warning", true)
        target:set("rundir", os.projectdir())
        target:set("group", "test")
        target:add("packages", "boost_ut")
    end)
