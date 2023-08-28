-- dev

if is_mode("debug") then
    add_requireconfs("*", {configs = {shared = true}})
end

-- cross-platform clipboard api
add_requires("clip 1.5")
-- https
add_requires("cpr 1.10.3", {configs = {ssl = true}})
-- url
add_requires("ada e22331885ce864d27ea78ff9b2d5ce917ef09a69")
-- debug/concat
add_requires("fast_io 2023.1.28")

if is_plat("windows") and is_mode("release") then
    add_requires("vc-ltl5 5.0.7")
end

-- test

if has_config("test") then
    add_requires("boost_ut v1.1.9")
end
