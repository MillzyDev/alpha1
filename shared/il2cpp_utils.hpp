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
        static std::map<Il2CppClass *, std::map<std::string, FieldInfo *>> field_cache;
        static std::map<Il2CppClass *, std::map<std::string, const PropertyInfo *>> property_cache;

    public:
        /**
        * Searches all IL2CPP assemblies for a class.
        * @param namespaze The namespace that the class is in.
        * @param name The name of the class.
        * @return A pointer to the found Il2CppClass instance. Is nullptr if the class was not found.
        */
        static Il2CppClass *find_class(std::string namespaze, std::string name);

        /**
        * Finds the info of a method in an IL2CPP class.
        * @param klass The class in which to search for the method.
        * @param name The original C# name of the method.
        * @param args The number of parameters that the method has, not including "this" or any runtime method info.
        * @return A MethodInfo pointer for the corresponding method. Is nullptr if the method was not found.
        */
        static const MethodInfo *find_method(Il2CppClass *klass, std::string name, int args);

        /**
        * Finds the info of a method in the namespace and class name provided.
        * @param namespaze The namespace that the class is in.
        * @param klass The name of the class that the method is in.
        * @param name The original C# name of the method.
        * @param args The number of parameters that the method had, not including "this" or any runtime method info.
        * @return A MethodInfo pointer for the corresponding method. Is nullptr if the method or class was not found.
        */
        static const MethodInfo *find_method(std::string namespaze, std::string klass, std::string name, int args);

        /**
        * Finds the info of a field in an IL2CPP class.
        * @param klass The class that contains the field.
        * @param name The name of the field.
        * @return A FieldInfo pointer for the corresponding field. Is nullptr if the field was not found.
        */
        static FieldInfo *find_field(Il2CppClass *klass, std::string name);

        /**
        * Finds the info of a field in the namespace and class name provided.
        * @param namespaze The namespace that the class is in.
        * @param klass The name of the class that contains the field.
        * @param name The name of the field.
        * @return A FieldInfo pointer for the corresponding field. Is nullptr if the field or class was not found.
        */
        static FieldInfo *find_field(std::string namespaze, std::string klass, std::string name);

        /**
        * Finds the info of a property in an IL2CPP class.
        * @param klass The class in which contains the property.
        * @param name The name of the property.
        * @return A PropertyInfo pointer for the corresponding property. Is nullptr if the property was not found.
        */
        static const PropertyInfo *find_property(Il2CppClass *klass, std::string name);

        /**
        * Finds the info of a property in the namespace and class name provided.
        * @param namespaze The namespace that the class is in.
        * @param klass The name of the class that contains the property.
        * @param name The name of the property.
        * @return A PropertyInfo pointer for the corresponding property. Is nullptr if the property or class was not found.
        */
        static const PropertyInfo *find_property(std::string namespaze, std::string klass, std::string name);
    };
}

#undef ALPHA1_EXPORT