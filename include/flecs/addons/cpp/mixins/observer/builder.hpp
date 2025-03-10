/**
 * @file addons/cpp/mixins/observer/builder.hpp
 * @brief Observer builder.
 */

#pragma once

#include "../../utils/node_builder.hpp"
#include "builder_i.hpp"

FLECS_CPP_MODULE namespace flecs {
namespace _ {
    template <typename ... Components>
    using observer_builder_base = node_builder<
        observer, ecs_observer_desc_t, observer_builder<Components...>, 
        observer_builder_i, Components ...>;
}

/** Observer builder.
 * 
 * @ingroup cpp_observers
 */
template <typename ... Components>
struct observer_builder final : _::observer_builder_base<Components...> {
    observer_builder(flecs::world_t* world, const char *name = nullptr)
        : _::observer_builder_base<Components...>(world, name)
    {
        _::sig<Components...>(world).populate(this);
    }
};

}
