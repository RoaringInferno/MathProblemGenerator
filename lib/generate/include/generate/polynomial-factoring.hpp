#pragma once

#include "generate.hpp"

namespace generate
{
    namespace polynomial_factoring
    {
        typedef unsigned short factor_count_t;

        struct parameters
        {
            mprgen::integer factor_max;
            mprgen::integer factor_min;
            mprgen::integer front_factor_max;
            mprgen::integer front_factor_min;
            factor_count_t factor_count;
        };

        mprgen::MathProblem problem(
            const parameters& params = {9, -9, 2, -2, 2}
        );

        void problem_set(
            const parameters& params,
            const iterator_range_t& range
        );
    };
}