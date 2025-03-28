/**
 * @file addons/cpp/mixins/query/builder.hpp
 * @brief Query builder.
 */

#pragma once

#include "../../utils/builder.hpp"
#include "builder_i.hpp"

FLECS_CPP_MODULE namespace flecs {
namespace _ {
    template <typename ... Components>
    using query_builder_base = builder<
        query, ecs_query_desc_t, query_builder<Components...>, 
        query_builder_i, Components ...>;
}

/** Query builder.
 * 
 * @ingroup cpp_core_queries
 */
template <typename ... Components>
struct query_builder final : _::query_builder_base<Components...> {
    query_builder(flecs::world_t* world, flecs::entity query_entity)
        : _::query_builder_base<Components...>(world)
    {
        _::sig<Components...>(world).populate(this);
        this->desc_.entity = query_entity.id();
    }

    query_builder(flecs::world_t* world, const char *name = nullptr)
        : _::query_builder_base<Components...>(world)
    {
        _::sig<Components...>(world).populate(this);
        if (name != nullptr) {
            ecs_entity_desc_t entity_desc = {};
            entity_desc.name = name;
            entity_desc.sep = "::";
            entity_desc.root_sep = "::";
            this->desc_.entity = ecs_entity_init(world, &entity_desc);
        }
    }

    template <typename Func>
    void each(Func&& func) {
        this->build().each(FLECS_FWD(func));
    }
};

}
