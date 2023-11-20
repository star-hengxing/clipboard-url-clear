set_project("clipboard-url-clear")

set_version("0.0.3")

set_xmakever("2.8.5")

set_allowedplats("windows")
set_allowedmodes("debug", "release")

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
    add_defines("UNICODE", "_UNICODE")
    add_cxflags("/permissive-", {tools = "cl"})
end

set_encodings("utf-8")

includes("src", "xmake", "test")
