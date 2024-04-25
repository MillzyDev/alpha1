#include <cmath>

#include "modloader.hpp"
#include "logger.hpp"
#include "il2cpp.hpp"
#include "hooking.hpp"
#include "il2cpp_utils.hpp"

static ::alpha1::mod_info mod_info("Example Mod", "0.1.0", "Me");
static ::alpha1::logger logger(mod_info);

typedef void (*update_t)(Il2CppObject *self, const MethodInfo *runtime_method);
static update_t cube_update_orig = nullptr;

struct UnityEngine_Color {
    float r;
    float g;
    float b;
    float a;
};

UnityEngine_Color hsv_to_color(float h, float s, float v) {
    UnityEngine_Color color = {1.0f, 1.0f, 1.0f, 1.0f};
    if (s == 0.0f) {
        color.r = v;
        color.g = v;
        color.b = v;
    }
    else if (v == 0.0f) {
        color.r = 0.0f;
        color.g = 0.0f;
        color.b = 0.0f;
    }
    else {
        color.r = 0.0f;
        color.g = 0.0f;
        color.b = 0.0f;

        float num1 = s;
        float num2 = v;
        float f = h * 6.0f;
        int num3 = std::floorf(f);
        float num4 = f - num3;
        float num5 = num2 * (1.0f - num1);
        float num6 = num2 * (1.0f - num1 * num4);
        float num7 = num2 * (1.0f - num1 * (1.0f - num4));

        switch (num3) {
            case -1:
                color.r = num2;
                color.g = num5;
                color.b = num6;
                break;
            case 0:
                color.r = num2;
                color.g = num7;
                color.b = num5;
                break;
            case 1:
                color.r = num6;
                color.g = num2;
                color.b = num5;
                break;
            case 2:
                color.r = num5;
                color.g = num2;
                color.b = num7;
                break;
            case 3:
                color.r = num5;
                color.g = num6;
                color.b = num2;
                break;
            case 4:
                color.r = num7;
                color.g = num5;
                color.b = num2;
                break;
            case 5:
                color.r = num2;
                color.g = num5;
                color.b = num6;
                break;
            case 6:
                color.r = num2;
                color.g = num7;
                color.b = num5;
                break;
        }
    }
    return color;
}

void cube_update_detour(Il2CppObject *self, const MethodInfo *runtime_method) {
    cube_update_orig(self, runtime_method);

    Il2CppException *exp = nullptr;

    static bool firstRun = true;
    static Il2CppClass *color_class; // we need this for boxing our colour value, and the HSV to RGB conversions
    static const MethodInfo *color_setter;
    static Il2CppObject *material;

    if (firstRun) {
        color_class = ::alpha1::il2cpp_utils::find_class("UnityEngine", "Color");
        Il2CppClass *material_class = ::alpha1::il2cpp_utils::find_class("UnityEngine", "Material");
        Il2CppClass *mesh_renderer_class = ::alpha1::il2cpp_utils::find_class("UnityEngine", "MeshRenderer");

        FieldInfo *mesh_renderer_field = ::alpha1::il2cpp_utils::find_field(self->klass, "_meshRenderer");
        const PropertyInfo *material_property = ::alpha1::il2cpp_utils::find_property(mesh_renderer_class, "material");
        const PropertyInfo * color_property = ::alpha1::il2cpp_utils::find_property(material_class, "color");

        const MethodInfo *material_getter = ::alpha1::il2cpp::property_get_get_method(material_property);
        color_setter = ::alpha1::il2cpp::property_get_set_method(color_property);

        Il2CppObject *mesh_renderer = ::alpha1::il2cpp::field_get_value_object(mesh_renderer_field, self);

        material = ::alpha1::il2cpp::runtime_invoke(material_getter, mesh_renderer, nullptr, &exp);

        firstRun = false;
    }

    static float hue;
    static UnityEngine_Color color(1.0f, 0.0f, 0.0f, 1.0f); // red

    hue += 0.01f;

    color = hsv_to_color(std::fmod(hue, 1.0f), 1.0f, 1.0f);

    void *color_args[] = {&color};
    (void)::alpha1::il2cpp::runtime_invoke(color_setter, material, color_args, &exp);
}

extern "C" __declspec(dllexport) void get_info(::alpha1::mod_info *info) {
    *info = mod_info;
}

extern "C" __declspec(dllexport) void load() {
    logger.info("Hello! The mod loaded :)");

    const MethodInfo *cube_update_info = ::alpha1::il2cpp_utils::find_method("", "TheCube", "Update", 0);
    cube_update_orig = reinterpret_cast<update_t>(cube_update_info->methodPointer);
    ::alpha1::hook(reinterpret_cast<void **>(&cube_update_orig), reinterpret_cast<void *>(cube_update_detour));
}
