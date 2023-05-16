-- dev

-- cross-platform clipboard api
add_requires("clip")
-- regex match
add_requires("ctre")
-- https
add_requires("cpr 1.10.3", {configs = {ssl = true}})
-- url
add_requires("ada")
-- debug/concat
add_requires("fast_io")

if is_mode("release") then
    add_requires("vc-ltl5")
end

-- test
if has_config("test") then
    add_requires("boost_ut")
end
