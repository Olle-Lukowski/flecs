/**
 * @file api_defines.h
 * @brief Supporting defines for the public API.
 *
 * This file contains constants / macro's that are typically not used by an
 * application but support the public API, and therefore must be exposed. This
 * header should not be included by itself.
 */

#ifndef FLECS_API_DEFINES_H
#define FLECS_API_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Standard library dependencies */
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

/* Non-standard but required. If not provided by platform, add manually. If
 * flecs is built by bake, stdint.h from bake is included. */
#ifndef __BAKE__
#include <stdint.h>
#endif

/* Contains macro's for importing / exporting symbols */
#include "flecs/bake_config.h"

#ifdef __BAKE_LEGACY__
#define FLECS_LEGACY
#endif


////////////////////////////////////////////////////////////////////////////////
//// Language support defines
////////////////////////////////////////////////////////////////////////////////

/* The API uses the native bool type in C++, or a custom one in C */
#ifndef __cplusplus
#undef bool
#undef true
#undef false
typedef char bool;
#define false 0
#define true !false
#endif

/* Use alignof in C++, or a trick in C. */
#ifdef __cplusplus
#define ECS_ALIGNOF(T) alignof(T)
#elif defined(_MSC_VER)
#define ECS_ALIGNOF(T) __alignof(T)
#else
#define ECS_ALIGNOF(T) ((size_t)&((struct { char c; T d; } *)0)->d)
#endif

/* Simple utility for determining the max of two values */
#define ECS_MAX(a, b) ((a > b) ? a : b)


////////////////////////////////////////////////////////////////////////////////
//// Reserved component ids
////////////////////////////////////////////////////////////////////////////////

/** Builtin component ids */
#define FLECS__EEcsComponent (1)
#define FLECS__EEcsComponentLifecycle (2)
#define FLECS__EEcsType (3)
#define FLECS__EEcsName (6)

/** System module component ids */
#define FLECS__EEcsTrigger (4)
#define FLECS__EEcsSystem (5)
#define FLECS__EEcsTickSource (7)
#define FLECS__EEcsSignatureExpr (8)
#define FLECS__EEcsSignature (9)
#define FLECS__EEcsQuery (10)
#define FLECS__EEcsIterAction (11)
#define FLECS__EEcsContext (12)

/** Pipeline module component ids */
#define FLECS__EEcsPipelineQuery (13)

/** Timer module component ids */
#define FLECS__EEcsTimer (14)
#define FLECS__EEcsRateFilter (15)


////////////////////////////////////////////////////////////////////////////////
//// Convert between C typenames and variables
////////////////////////////////////////////////////////////////////////////////

/** Translate C type to type variable. */
#define ecs_type(T) FLECS__T##T

/** Translate C type to entity variable. */
#define ecs_entity(T) FLECS__E##T

/** Translate C type to module struct. */
#define ecs_module(T) FLECS__M##T

/** Translate C type to module struct. */
#define ecs_module_ptr(T) FLECS__M##T##_ptr

/** Translate C type to module struct. */
#define ecs_iter_action(T) FLECS__F##T


////////////////////////////////////////////////////////////////////////////////
//// Convenience macro's for ctor, dtor, move and copy
////////////////////////////////////////////////////////////////////////////////

/* Constructor / destructor convenience macro */
#define ECS_XTOR_IMPL(type, postfix, var, ...)\
    void type##_##postfix(\
        ecs_world_t *world,\
        ecs_entity_t component,\
        const ecs_entity_t *entity_ptr,\
        void *_ptr,\
        size_t size,\
        int32_t count,\
        void *ctx)\
    {\
        (void)world;\
        (void)component;\
        (void)entity_ptr;\
        (void)_ptr;\
        (void)size;\
        (void)count;\
        (void)ctx;\
        for (int32_t i = 0; i < count; i ++) {\
            ecs_entity_t entity = entity_ptr[i];\
            type *var = &((type*)_ptr)[i];\
            (void)entity;\
            (void)var;\
            __VA_ARGS__\
        }\
    }

/* Copy convenience macro */
#define ECS_COPY_IMPL(type, dst_var, src_var, ...)\
    void type##_##copy(\
        ecs_world_t *world,\
        ecs_entity_t component,\
        const ecs_entity_t *dst_entities,\
        const ecs_entity_t *src_entities,\
        void *_dst_ptr,\
        const void *_src_ptr,\
        size_t size,\
        int32_t count,\
        void *ctx)\
    {\
        (void)world;\
        (void)component;\
        (void)dst_entities;\
        (void)src_entities;\
        (void)_dst_ptr;\
        (void)_src_ptr;\
        (void)size;\
        (void)count;\
        (void)ctx;\
        for (int32_t i = 0; i < count; i ++) {\
            ecs_entity_t dst_entity = dst_entities[i];\
            ecs_entity_t src_entity = src_entities[i];\
            type *dst_var = &((type*)_dst_ptr)[i];\
            type *src_var = &((type*)_src_ptr)[i];\
            (void)dst_entity;\
            (void)src_entity;\
            (void)dst_var;\
            (void)src_var;\
            __VA_ARGS__\
        }\
    }

/* Move convenience macro */
#define ECS_MOVE_IMPL(type, dst_var, src_var, ...)\
    void type##_##move(\
        ecs_world_t *world,\
        ecs_entity_t component,\
        const ecs_entity_t *dst_entities,\
        const ecs_entity_t *src_entities,\
        void *_dst_ptr,\
        void *_src_ptr,\
        size_t size,\
        int32_t count,\
        void *ctx)\
    {\
        (void)world;\
        (void)component;\
        (void)dst_entities;\
        (void)src_entities;\
        (void)_dst_ptr;\
        (void)_src_ptr;\
        (void)size;\
        (void)count;\
        (void)ctx;\
        for (int32_t i = 0; i < count; i ++) {\
            ecs_entity_t dst_entity = dst_entities[i];\
            ecs_entity_t src_entity = src_entities[i];\
            type *dst_var = &((type*)_dst_ptr)[i];\
            type *src_var = &((type*)_src_ptr)[i];\
            (void)dst_entity;\
            (void)src_entity;\
            (void)dst_var;\
            (void)src_var;\
            __VA_ARGS__\
        }\
    }

#ifdef __cplusplus
}
#endif

#endif
