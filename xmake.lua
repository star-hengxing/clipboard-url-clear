set_project("clipboard-url-clear")

set_version("0.0.2")

set_xmakever("2.8.1")

set_allowedplats("windows")

set_languages("c++20")

set_warnings("all")
add_rules("mode.debug", "mode.release")

if is_mode("debug") then
    set_policy("build.warning", true)
elseif is_mode("release") then
    set_optimize("smallest")
end

if is_plat("windows") then
    set_runtimes(is_mode("debug") and "MDd" or "MT")
    -- support utf-8 on msvc
    add_defines("UNICODE", "_UNICODE")
    add_cxflags("/utf-8", "/permissive-", {tools = "cl"})
end

includes("src", "xmake", "test")
