/**
 * @file addons/cpp/mixins/system/decl.hpp
 * @brief System module declarations.
 */

#pragma once

FLECS_CPP_MODULE namespace flecs {

/**
 * @defgroup cpp_addons_systems Systems
 * @ingroup cpp_addons
 * Systems are a query + function that can be ran manually or by a pipeline.
 *
 * @{
 */

using TickSource = EcsTickSource;

struct system;

template<typename ... Components>
struct system_builder;

namespace _ {

void system_init(flecs::world& world);

/** @} */

} // namespace _
} // namespace flecs
