set_project("clipboard-url-clear")

set_version("0.0.2")

set_xmakever("2.8.1")

set_warnings("all")
set_languages("c++20")

set_allowedplats("windows")

add_rules("mode.debug", "mode.release")

local package_config = {}

if is_mode("debug") then
    set_policy("build.warning", true)
    package_config.shared = true
end

if is_mode("release") then
    set_optimize("smallest")
end

add_requireconfs("*", {configs = package_config})

if is_plat("windows") then
    set_runtimes(is_mode("debug") and "MDd" or "MT")
    -- support utf-8 on msvc
    add_defines("UNICODE", "_UNICODE")
    add_cxflags("/utf-8", "/permissive-", {tools = "cl"})
end

includes("src", "xmake", "test")
