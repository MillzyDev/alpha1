add_rules("mode.debug", "mode.release")

target("proxy")
    set_kind("shared")
    set_languages("cxx20")

    add_files("proxy/src/*.cpp")
    add_includedirs("proxy/include")

    set_basename("winhttp") -- override output name
    set_prefixname("")

    add_shflags("-static") -- static link with stl
target_end()

target("alpha1")
    set_kind("shared")
    set_languages("cxx20")

    add_files("src/*.cpp")
    add_includedirs("include")
    add_includedirs("shared")

    add_shflags("-static")

    set_prefixname("")
target_end()
