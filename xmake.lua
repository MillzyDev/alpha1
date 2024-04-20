add_rules("mode.debug", "mode.release")
add_rules("c++.unity_build")

add_requires("microsoft-detours")

target("proxy")
    set_kind("shared")
    set_languages("cxx20")

    add_files("proxy/src/*.cpp")
    add_includedirs("proxy/include")

    set_basename("winhttp") -- override output name
    set_prefixname("")

    add_shflags("-static") -- static link with stl

    add_rules("c++.unity_build")
target_end()

target("alpha1")
    set_kind("shared")
    set_languages("cxx20")

    add_files("src/*.cpp")
    add_includedirs("include")
    add_includedirs("shared")

    add_packages("microsoft-detours")

    add_shflags("-static")
    add_shflags("-fdeclspec")

    set_prefixname("")
    add_defines("ALPHA1_DO_EXPORTS")
    add_rules("c++.unity_build")

    add_includedirs("libil2cpp")
target_end()
