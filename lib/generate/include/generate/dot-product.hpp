#pragma once

#include "generate.hpp"

#include "mprgen/math-problem.hpp"
#include "mprgen/number.hpp"

namespace generate
{
    namespace dot_product
    {
        typedef unsigned short vector_dimension_t;

        struct parameters
        {
            mprgen::integer component_max;
            mprgen::integer component_min;
            vector_dimension_t vector_dimension;
        };

        mprgen::MathProblem problem(
            const parameters& params = {9, -9, 3}
        );

        void problem_set(
            const parameters& params,
            const iterator_range_t& range
        );
    };
}