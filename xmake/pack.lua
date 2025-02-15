includes("@builtin/xpack")

-- build/xpack/clear/clear.7z
xpack("clipboard-url-clear")
    set_formats("zip")
    set_extension(".7z")
    set_basename("clear")

    add_targets("clear")

    set_prefixdir("clipboard-url-clear")

    set_bindir("")
    add_installfiles(path.join(os.projectdir(), "clear_domains.csv"))
