includes("@builtin/xpack")

xpack("clear")
    set_formats("zip")
    set_extension(".7z")
    set_basename("clear-v$(version)")
    
    add_targets("clear")

    set_prefixdir("clear")

    set_bindir("")
    add_installfiles(path.join(os.projectdir(), "clear_domains.csv"))
