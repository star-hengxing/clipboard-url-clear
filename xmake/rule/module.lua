rule("module.program")
    on_load(function (target)
        target:set("kind", "binary")
        if not target:get("rundir") then
            target:set("rundir", os.projectdir())
        end

        if is_mode("release") then
            if target:is_plat("windows") and target:has_runtime("MT") then
                target:add("packages", "vc-ltl5")
            end
        end
    end)

rule("module.component")
    on_load(function (target)
        if target:is_static() then
            target:add("defines", "LIBRARY_STATIC", {public = true})
        elseif target:is_shared() then
            target:add("defines", "LIBRARY_BUILDING")
        end
    end)

rule("module.test")
    on_load(function (target)
        target:set("default", false)
        target:set("kind", "binary")
        if not target:get("rundir") then
            target:set("rundir", os.projectdir())
        end

        target:add("packages", "boost_ut")
    end)
