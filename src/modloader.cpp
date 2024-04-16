#include "modloader.hpp"

#include <map>
#include <algorithm>

namespace alpha1 {
    void add_mod(::alpha1::mod_metadata metadata) {
        modloader::loaded_mods.push_back(metadata);
    }

    void add_library(::alpha1::library_metadata metadata) {
        modloader::loaded_libraries.push_back(metadata);
    }

    void add_failed_mod(::alpha1::failed_library mod) {
        modloader::failed_mods.push_back(mod);
    }

    void add_failed_library(::alpha1::failed_library library) {
        modloader::failed_libraries.push_back(library);
    }

    std::vector<::alpha1::mod_metadata> modloader::loaded_mods;
    std::vector<::alpha1::library_metadata> modloader::loaded_libraries;
    std::vector<::alpha1::failed_library> modloader::failed_mods;
    std::vector<::alpha1::failed_library> modloader::failed_libraries;

    bool modloader::get_mod_info(std::string mod_name, ::alpha1::mod_metadata *metadata) {
        static std::map<std::string, ::alpha1::mod_metadata> cache;

        if (cache.contains(mod_name)) {
            *metadata = cache[mod_name];
            return true;
        }

        auto it = std::find_if(::alpha1::modloader::loaded_mods.begin(), ::alpha1::modloader::loaded_mods.end(),
                               [mod_name](::alpha1::mod_metadata metadata) -> bool {
            return metadata.info.name == mod_name;
        });

        if (it != std::end(modloader::loaded_mods)) {
            cache.emplace(std::make_pair(mod_name, *it));
            *metadata = *it;
            return true;
        }

        return false;
    }

    std::vector<::alpha1::mod_metadata> modloader::get_mods() {
        return ::alpha1::modloader::loaded_mods;
    }

    std::vector<::alpha1::library_metadata> modloader::get_libraries() {
        return ::alpha1::modloader::loaded_libraries;
    }

    std::vector<::alpha1::failed_library> modloader::get_failed_mods() {
        return ::alpha1::modloader::failed_mods;
    }

    std::vector<::alpha1::failed_library> modloader::get_failed_libraries() {
        return ::alpha1::modloader::failed_libraries;
    }

}

