set_project("clipboard-url-clear")

set_version("0.1.0")

set_xmakever("2.9.8")

set_allowedplats("windows")
set_allowedmodes("debug", "release")

set_policy("compatibility.version", "3.0")

set_warnings("all")
set_languages("c++20")
add_rules("mode.debug", "mode.release")

if is_mode("release") then
    set_optimize("smallest")
end

if is_plat("windows") then
    set_runtimes("MD")
    add_defines("UNICODE", "_UNICODE")
    add_cxflags("/permissive-", {tools = "cl"})
end

set_encodings("utf-8")

includes("src", "xmake", "test")
