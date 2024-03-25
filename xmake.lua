add_rules("mode.debug", "mode.release")

target("proxy")
    set_kind("shared")
    set_languages("cxx20")

    add_files("proxy/src/*.cpp")
    add_includedirs("proxy/include")

    set_basename("winhttp") -- override output name
    set_prefixname("")
    set_extension(".dll")

    add_cxxflags("-stdlib=libc++") -- use llvm stl
    add_shflags("-static") -- static link with libc++
target_end()
