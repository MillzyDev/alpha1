#pragma once

#include <cstdint>

typedef struct MethodInfo // we only need the name, rest is to make sure the type is the right size
{
    [[maybe_unused]] void *methodPointer;
    [[maybe_unused]] void *virtualMethodPointer;
    [[maybe_unused]] void *invoker_method;
    const char* name;
    [[maybe_unused]] void *klass;
    [[maybe_unused]] const void *return_type;
    [[maybe_unused]] const void** parameters;

    union
    {
        [[maybe_unused]] const void* rgctx_data;
        [[maybe_unused]] void *methodMetadataHandle;
    };

    union
    {
        [[maybe_unused]] const void *genericMethod;
        [[maybe_unused]] void *genericContainerHandle;
    };

    [[maybe_unused]] uint32_t token;
    [[maybe_unused]] uint16_t flags;
    [[maybe_unused]] uint16_t iflags;
    [[maybe_unused]] uint16_t slot;
    [[maybe_unused]] uint8_t parameters_count;
    [[maybe_unused]] uint8_t is_generic : 1;
    [[maybe_unused]] uint8_t is_inflated : 1;
    [[maybe_unused]] uint8_t wrapper_type : 1;
    [[maybe_unused]] uint8_t has_full_generic_sharing_signature : 1;
    [[maybe_unused]] uint8_t indirect_call_via_invokers : 1;
} MethodInfo;