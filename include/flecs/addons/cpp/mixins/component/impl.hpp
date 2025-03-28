/**
 * @file addons/cpp/mixins/component/impl.hpp
 * @brief Component mixin implementation
 */

#pragma once

FLECS_CPP_MODULE namespace flecs {

template <typename T, typename... Args>
inline flecs::component<T> world::component(Args &&... args) const {
    return flecs::component<T>(world_, FLECS_FWD(args)...);
}

template <typename... Args>
inline flecs::untyped_component world::component(Args &&... args) const {
    return flecs::untyped_component(world_, FLECS_FWD(args)...);
}

} // namespace flecs
