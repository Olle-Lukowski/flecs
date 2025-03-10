/**
 * @file addons/cpp/mixins/pipeline/builder_i.hpp
 * @brief Pipeline builder interface.
 */

#pragma once

#include "../query/builder_i.hpp"

FLECS_CPP_MODULE namespace flecs {

/** Pipeline builder interface.
 * 
 * @ingroup cpp_pipelines
 */
template<typename Base>
struct pipeline_builder_i : query_builder_i<Base> {
    pipeline_builder_i(ecs_pipeline_desc_t *desc, int32_t term_index = 0) 
        : query_builder_i<Base>(&desc->query, term_index)
        , desc_(desc) { }

private:
    ecs_pipeline_desc_t *desc_;
};

}
