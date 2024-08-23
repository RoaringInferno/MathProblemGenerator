#pragma once

#pragma once

#include "generate.hpp"

namespace generate
{
    namespace cross_product
    {
        struct parameters
        {
            mprgen::integer component_max;
            mprgen::integer component_min;
        };

        mprgen::MathProblem problem(
            const parameters& params = {9, -9}
        );

        void problem_set(
            const parameters& params,
            const iterator_range_t& range
        );
    };
}