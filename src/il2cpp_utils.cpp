#include "il2cpp_utils.hpp"

namespace alpha1 {
    std::map<std::tuple<std::string, std::string>, Il2CppClass *> il2cpp_utils::class_cache;
    std::map<Il2CppClass *, std::map<std::tuple<std::string, int>, const MethodInfo *>> il2cpp_utils::method_cache;
    std::map<Il2CppClass *, std::map<std::string, FieldInfo *>> il2cpp_utils::field_cache;
    std::map<Il2CppClass *, std::map<std::string, const PropertyInfo *>> il2cpp_utils::property_cache;

    Il2CppClass *il2cpp_utils::find_class(std::string namespaze, std::string name) {
        std::tuple<std::string, std::string> key(namespaze, name);
        if (::alpha1::il2cpp_utils::class_cache.contains(key)) {
            return ::alpha1::il2cpp_utils::class_cache[key];
        }

        static Il2CppDomain *domain = ::alpha1::il2cpp::domain_get();

        size_t assembly_count;
        const Il2CppAssembly **assemblies = ::alpha1::il2cpp::domain_get_assemblies(domain, &assembly_count);

        for (size_t assembly_index = 0; assembly_index < assembly_count; assembly_index++) {
            const Il2CppImage *image = ::alpha1::il2cpp::assembly_get_image(assemblies[assembly_index]);

            Il2CppClass *klass = ::alpha1::il2cpp::class_from_name(image, namespaze.c_str(), name.c_str());

            if (klass) {
                ::alpha1::il2cpp_utils::class_cache.emplace(key, klass);
                return klass;
            }
        }

        return nullptr;
    }

    const MethodInfo *il2cpp_utils::find_method(Il2CppClass *klass, std::string name, int args) {
        if (!::alpha1::il2cpp_utils::method_cache.contains(klass)) {
            ::alpha1::il2cpp_utils::method_cache.emplace(klass,
                                                         std::map<std::tuple<std::string, int>, const MethodInfo *>());
        }

        std::tuple<std::string, int> key(name, args);

        std::map<std::tuple<std::string, int>, const MethodInfo *> inner_method_cache
                = ::alpha1::il2cpp_utils::method_cache[klass];

        if (inner_method_cache.contains(key)) {
            return inner_method_cache[key];
        }

        const MethodInfo *method = ::alpha1::il2cpp::class_get_method_from_name(klass, name.c_str(), args);

        if (method) {
            ::alpha1::il2cpp_utils::method_cache[klass].emplace(key, method);
            return method;
        }

        return nullptr;
    }

    const MethodInfo *il2cpp_utils::find_method(std::string namespaze, std::string clazz, std::string name, int args) {
        return ::alpha1::il2cpp_utils::find_method(::alpha1::il2cpp_utils::find_class(namespaze, clazz), name, args);
    }

    FieldInfo *il2cpp_utils::find_field(Il2CppClass *klass, std::string name) {
        if (!::alpha1::il2cpp_utils::field_cache.contains(klass)) {
            ::alpha1::il2cpp_utils::field_cache.emplace(klass, std::map<std::string, FieldInfo *>());
        }

        std::map<std::string, FieldInfo *> inner_field_cache
                = ::alpha1::il2cpp_utils::field_cache[klass];

        if (inner_field_cache.contains(name)) {
            return inner_field_cache[name];
        }

        FieldInfo *field = ::alpha1::il2cpp::class_get_field_from_name(klass, name.c_str());

        if (field) {
            ::alpha1::il2cpp_utils::field_cache[klass].emplace(name, field);
            return field;
        }

        return nullptr;
    }

    FieldInfo *il2cpp_utils::find_field(std::string namespaze, std::string klass, std::string name) {
        return ::alpha1::il2cpp_utils::find_field(::alpha1::il2cpp_utils::find_class(namespaze, klass), name);
    }

    const PropertyInfo *il2cpp_utils::find_property(Il2CppClass *klass, std::string name) {
        if (!::alpha1::il2cpp_utils::property_cache.contains(klass)) {
            ::alpha1::il2cpp_utils::property_cache.emplace(klass, std::map<std::string, const PropertyInfo *>());
        }

        std::map<std::string, const PropertyInfo *> inner_property_cache
                = ::alpha1::il2cpp_utils::property_cache[klass];

        if (inner_property_cache.contains(name)) {
            return inner_property_cache[name];
        }

        const PropertyInfo *property = ::alpha1::il2cpp::class_get_property_from_name(klass, name.c_str());

        if (property) {
            ::alpha1::il2cpp_utils::property_cache[klass].emplace(name, property);
            return property;
        }

        return nullptr;
    }

    const PropertyInfo *il2cpp_utils::find_property(std::string namespaze, std::string klass, std::string name) {
        return ::alpha1::il2cpp_utils::find_property(::alpha1::il2cpp_utils::find_class(namespaze, klass), name);
    }
}