#pragma once

#include <cstdint>

typedef struct MethodInfo // we only need the name, rest is to make sure the type is the right size
{
    void *methodPointer;
    void *virtualMethodPointer;
    void *invoker_method;
    const char* name;
    void *klass;
    const void *return_type;
    const void** parameters;

    union
    {
        const void* rgctx_data;
        void *methodMetadataHandle;
    };

    union
    {
        const void *genericMethod;
        void *genericContainerHandle;
    };

    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint8_t parameters_count;
    uint8_t is_generic : 1;
    uint8_t is_inflated : 1;
    uint8_t wrapper_type : 1;
    uint8_t has_full_generic_sharing_signature : 1;
    uint8_t indirect_call_via_invokers : 1;
} MethodInfo;