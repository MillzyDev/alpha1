#pragma once

#include <windows.h>

#include "logger.hpp"

#define IL2CPP_TARGET_CUSTOM 1
#define IL2CPP_TARGET_WINDOWS 1
#define IL2CPP_TARGET_WINDOWS_DESKTOP 1

#define IL2CPP_PLATFORM_SUPPORTS_SYSTEM_CERTIFICATES 1
#define IL2CPP_PLATFORM_SUPPORTS_CPU_INFO 1

#define _UNICODE 1
#define UNICODE 1
#define STRICT 1

#include "il2cpp-api-types.h"
#include "il2cpp-class-internals.h"

#include "il2cpp_pointer_types.hpp"

#ifdef ALPHA1_DO_EXPORTS
#define ALPHA1_EXPORT __declspec(dllexport)
#else
#define ALPHA1_EXPORT
#endif

#define IL2CPP_FUNC(name) static il2cpp_##name##_t name

namespace alpha1 {
    void load_il2cpp_funcs();

    class ALPHA1_EXPORT il2cpp {
        friend void load_il2cpp_funcs(::alpha1::logger &logger);

    private:
        static void init_il2cpp();

    public:
        IL2CPP_FUNC(init);
        IL2CPP_FUNC(init_utf16);
        IL2CPP_FUNC(shutdown);
        IL2CPP_FUNC(set_config_dir);
        IL2CPP_FUNC(set_data_dir);
        IL2CPP_FUNC(set_temp_dir);
        IL2CPP_FUNC(set_commandline_arguments);
        IL2CPP_FUNC(set_commandline_arguments_utf16);
        IL2CPP_FUNC(set_config_utf16);
        IL2CPP_FUNC(set_config);
        IL2CPP_FUNC(set_memory_callbacks);
        IL2CPP_FUNC(get_corlib);
        IL2CPP_FUNC(add_internal_call);
        IL2CPP_FUNC(resolve_icall);
        IL2CPP_FUNC(alloc);
        IL2CPP_FUNC(free);
        IL2CPP_FUNC(array_class_get);
        IL2CPP_FUNC(array_length);
        IL2CPP_FUNC(array_get_byte_length);
        IL2CPP_FUNC(array_new);
        IL2CPP_FUNC(array_new_specific);
        IL2CPP_FUNC(bounded_array_class_get);
        IL2CPP_FUNC(array_element_size);
        IL2CPP_FUNC(assembly_get_image);
        IL2CPP_FUNC(class_for_each);
        IL2CPP_FUNC(class_enum_basetype);
        IL2CPP_FUNC(class_is_generic);
        IL2CPP_FUNC(class_is_inflated);
        IL2CPP_FUNC(class_is_assignable_from);
        IL2CPP_FUNC(class_is_subclass_of);
        IL2CPP_FUNC(class_has_parent);
        IL2CPP_FUNC(class_from_il2cpp_type);
        IL2CPP_FUNC(class_from_name);
        IL2CPP_FUNC(class_from_system_type);
        IL2CPP_FUNC(class_get_element_class);
        IL2CPP_FUNC(class_get_events);
        IL2CPP_FUNC(class_get_fields);
        IL2CPP_FUNC(class_get_nested_types);
        IL2CPP_FUNC(class_get_interfaces);
        IL2CPP_FUNC(class_get_properties);
        IL2CPP_FUNC(class_get_property_from_name);
        IL2CPP_FUNC(class_get_field_from_name);
        IL2CPP_FUNC(class_get_methods);
        IL2CPP_FUNC(class_get_method_from_name);
        IL2CPP_FUNC(class_get_name);
        IL2CPP_FUNC(type_get_name_chunked);
        IL2CPP_FUNC(class_get_namespace);
        IL2CPP_FUNC(class_get_parent);
        IL2CPP_FUNC(class_get_declaring_type);
        IL2CPP_FUNC(class_instance_size);
        IL2CPP_FUNC(class_num_fields);
        IL2CPP_FUNC(class_is_valuetype);
        IL2CPP_FUNC(class_value_size);
        IL2CPP_FUNC(class_is_blittable);
        IL2CPP_FUNC(class_get_flags);
        IL2CPP_FUNC(class_is_abstract);
        IL2CPP_FUNC(class_is_interface);
        IL2CPP_FUNC(class_array_element_size);
        IL2CPP_FUNC(class_from_type);
        IL2CPP_FUNC(class_get_type);
        IL2CPP_FUNC(class_get_type_token);
        IL2CPP_FUNC(class_has_attribute);
        IL2CPP_FUNC(class_has_references);
        IL2CPP_FUNC(class_is_enum);
        IL2CPP_FUNC(class_get_image);
        IL2CPP_FUNC(class_get_assemblyname);
        IL2CPP_FUNC(class_get_rank);
        IL2CPP_FUNC(class_get_data_size);
        IL2CPP_FUNC(class_get_static_field_data);
        IL2CPP_FUNC(class_get_bitmap_size);
        IL2CPP_FUNC(class_get_bitmap);
        IL2CPP_FUNC(stats_dump_to_file);
        IL2CPP_FUNC(stats_get_value);
        IL2CPP_FUNC(domain_get);
        IL2CPP_FUNC(domain_assembly_open);
        IL2CPP_FUNC(domain_get_assemblies);
        IL2CPP_FUNC(raise_exception);
        IL2CPP_FUNC(exception_from_name_msg);
        IL2CPP_FUNC(get_exception_argument_null);
        IL2CPP_FUNC(format_exception);
        IL2CPP_FUNC(format_stack_trace);
        IL2CPP_FUNC(unhandled_exception);
        IL2CPP_FUNC(native_stack_trace);
        IL2CPP_FUNC(field_get_flags);
        IL2CPP_FUNC(field_get_name);
        IL2CPP_FUNC(field_get_parent);
        IL2CPP_FUNC(field_get_offset);
        IL2CPP_FUNC(field_get_type);
        IL2CPP_FUNC(field_get_value);
        IL2CPP_FUNC(field_get_value_object);
        IL2CPP_FUNC(field_has_attribute);
        IL2CPP_FUNC(field_set_value);
        IL2CPP_FUNC(field_static_get_value);
        IL2CPP_FUNC(field_static_set_value);
        IL2CPP_FUNC(field_set_value_object);
        IL2CPP_FUNC(field_is_literal);
        IL2CPP_FUNC(gc_collect);
        IL2CPP_FUNC(gc_collect_a_little);
        IL2CPP_FUNC(gc_start_incremental_collection);
        IL2CPP_FUNC(gc_disable);
        IL2CPP_FUNC(gc_enable);
        IL2CPP_FUNC(gc_is_disabled);
        IL2CPP_FUNC(gc_set_mode);
        IL2CPP_FUNC(gc_get_max_time_slice_ns);
        IL2CPP_FUNC(gc_set_max_time_slice_ns);
        IL2CPP_FUNC(gc_is_incremental);
        IL2CPP_FUNC(gc_get_used_size);
        IL2CPP_FUNC(gc_get_heap_size);
        IL2CPP_FUNC(gc_wbarrier_set_field);
        IL2CPP_FUNC(gc_has_strict_wbarriers);
        IL2CPP_FUNC(gc_set_external_allocation_tracker);
        IL2CPP_FUNC(gc_set_external_wbarrier_tracker);
        IL2CPP_FUNC(gc_foreach_heap);
        IL2CPP_FUNC(stop_gc_world);
        IL2CPP_FUNC(start_gc_world);
        IL2CPP_FUNC(gc_alloc_fixed);
        IL2CPP_FUNC(gc_free_fixed);
        IL2CPP_FUNC(gchandle_new);
        IL2CPP_FUNC(gchandle_new_weakref);
        IL2CPP_FUNC(gchandle_get_target);
        IL2CPP_FUNC(gchandle_free);
        IL2CPP_FUNC(gchandle_foreach_get_target);
        IL2CPP_FUNC(object_header_size);
        IL2CPP_FUNC(array_object_header_size);
        IL2CPP_FUNC(offset_of_array_length_in_array_object_header);
        IL2CPP_FUNC(offset_of_array_bounds_in_array_object_header);
        IL2CPP_FUNC(allocation_granularity);
        IL2CPP_FUNC(unity_liveness_allocate_struct);
        IL2CPP_FUNC(unity_liveness_calculation_from_root);
        IL2CPP_FUNC(unity_liveness_calculation_from_statics);
        IL2CPP_FUNC(unity_liveness_finalize);
        IL2CPP_FUNC(unity_liveness_free_struct);
        IL2CPP_FUNC(method_get_return_type);
        IL2CPP_FUNC(method_get_declaring_type);
        IL2CPP_FUNC(method_get_name);
        IL2CPP_FUNC(method_get_from_reflection);
        IL2CPP_FUNC(method_get_object);
        IL2CPP_FUNC(method_is_generic);
        IL2CPP_FUNC(method_is_inflated);
        IL2CPP_FUNC(method_is_instance);
        IL2CPP_FUNC(method_get_param_count);
        IL2CPP_FUNC(method_get_class);
        IL2CPP_FUNC(method_has_attribute);
        IL2CPP_FUNC(method_get_flags);
        IL2CPP_FUNC(method_get_token);
        IL2CPP_FUNC(method_get_param_name);
        IL2CPP_FUNC(profiler_install);
        IL2CPP_FUNC(profiler_set_events);
        IL2CPP_FUNC(profiler_install_enter_leave);
        IL2CPP_FUNC(profiler_install_allocation);
        IL2CPP_FUNC(profiler_install_gc);
        IL2CPP_FUNC(profiler_install_fileio);
        IL2CPP_FUNC(profiler_install_thread);
        IL2CPP_FUNC(property_get_flags);
        IL2CPP_FUNC(property_get_get_method);
        IL2CPP_FUNC(property_get_set_method);
        IL2CPP_FUNC(property_get_name);
        IL2CPP_FUNC(property_get_parent);
        IL2CPP_FUNC(object_get_class);
        IL2CPP_FUNC(object_get_size);
        IL2CPP_FUNC(object_get_virtual_method);
        IL2CPP_FUNC(object_new);
        IL2CPP_FUNC(object_unbox);
        IL2CPP_FUNC(value_box);
        IL2CPP_FUNC(monitor_enter);
        IL2CPP_FUNC(monitor_try_enter);
        IL2CPP_FUNC(monitor_exit);
        IL2CPP_FUNC(monitor_pulse);
        IL2CPP_FUNC(monitor_pulse_all);
        IL2CPP_FUNC(monitor_wait);
        IL2CPP_FUNC(monitor_try_wait);
        IL2CPP_FUNC(runtime_invoke);
        IL2CPP_FUNC(runtime_invoke_convert_args);
        IL2CPP_FUNC(runtime_class_init);
        IL2CPP_FUNC(runtime_object_init);
        IL2CPP_FUNC(runtime_object_init_exception);
        IL2CPP_FUNC(runtime_unhandled_exception_policy_set);
        IL2CPP_FUNC(string_length);
        IL2CPP_FUNC(string_chars);
        IL2CPP_FUNC(string_new);
        IL2CPP_FUNC(string_new_len);
        IL2CPP_FUNC(string_new_utf16);
        IL2CPP_FUNC(string_new_wrapper);
        IL2CPP_FUNC(string_intern);
        IL2CPP_FUNC(string_is_interned);
        IL2CPP_FUNC(thread_current);
        IL2CPP_FUNC(thread_attach);
        IL2CPP_FUNC(thread_detach);
        IL2CPP_FUNC(thread_get_all_attached_threads);
        IL2CPP_FUNC(is_vm_thread);
        IL2CPP_FUNC(current_thread_walk_frame_stack);
        IL2CPP_FUNC(thread_walk_frame_stack);
        IL2CPP_FUNC(current_thread_get_top_frame);
        IL2CPP_FUNC(thread_get_top_frame);
        IL2CPP_FUNC(current_thread_get_frame_at);
        IL2CPP_FUNC(thread_get_frame_at);
        IL2CPP_FUNC(current_thread_get_stack_depth);
        IL2CPP_FUNC(thread_get_stack_depth);
        IL2CPP_FUNC(override_stack_backtrace);
        IL2CPP_FUNC(type_get_object);
        IL2CPP_FUNC(type_get_type);
        IL2CPP_FUNC(type_get_class_or_element_class);
        IL2CPP_FUNC(type_get_name);
        IL2CPP_FUNC(type_is_byref);
        IL2CPP_FUNC(type_get_attrs);
        IL2CPP_FUNC(type_equals);
        IL2CPP_FUNC(type_get_assembly_qualified_name);
        IL2CPP_FUNC(type_is_static);
        IL2CPP_FUNC(type_is_pointer_type);
        IL2CPP_FUNC(image_get_assembly);
        IL2CPP_FUNC(image_get_name);
        IL2CPP_FUNC(image_get_filename);
        IL2CPP_FUNC(image_get_entry_point);
        IL2CPP_FUNC(image_get_class_count);
        IL2CPP_FUNC(image_get_class);
        IL2CPP_FUNC(capture_memory_snapshot);
        IL2CPP_FUNC(free_captured_memory_snapshot);
        IL2CPP_FUNC(set_find_plugin_callback);
        IL2CPP_FUNC(register_log_callback);
        IL2CPP_FUNC(debugger_set_agent_options);
        IL2CPP_FUNC(is_debugger_attached);
        IL2CPP_FUNC(register_debugger_agent_transport);
        IL2CPP_FUNC(debug_get_method_info);
        IL2CPP_FUNC(unity_install_unitytls_interface);
        IL2CPP_FUNC(custom_attrs_from_class);
        IL2CPP_FUNC(custom_attrs_from_method);
        IL2CPP_FUNC(custom_attrs_get_attr);
        IL2CPP_FUNC(custom_attrs_has_attr);
        IL2CPP_FUNC(custom_attrs_construct);
        IL2CPP_FUNC(class_set_userdata);
        IL2CPP_FUNC(class_get_userdata_offset);
        IL2CPP_FUNC(set_default_thread_affinity);
    };
}

#undef IL2CPP_FUNC