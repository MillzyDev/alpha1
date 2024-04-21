#pragma once

#include <map>
#include <string>

#include "il2cpp.hpp"

#ifdef ALPHA1_DO_EXPORTS
#define ALPHA1_EXPORT __declspec(dllexport)
#else
#define ALPHA1_EXPORT
#endif

namespace alpha1 {
    class ALPHA1_EXPORT il2cpp_utils {
    private:
        static std::map<std::tuple<std::string, std::string>, Il2CppClass *> class_cache;
        static std::map<Il2CppClass *, std::map<std::tuple<std::string, int>, const MethodInfo *>> method_cache;
        static std::map<Il2CppClass *, std::map<std::string, const FieldInfo *>> field_cache;
        static std::map<Il2CppClass *, std::map<std::string, const PropertyInfo *>> property_cache;

    public:
        static Il2CppClass *find_class(std::string namespaze, std::string name);
        static const MethodInfo *find_method(Il2CppClass *klass, std::string name, int args);
        static const MethodInfo *find_method(std::string namespaze, std::string clazz, std::string name, int args);
    };
}

#undef ALPHA1_EXPORT