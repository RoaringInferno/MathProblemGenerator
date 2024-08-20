#pragma once

#include "generate.hpp"

#include "mprgen/math-problem.hpp"
#include "mprgen/number.hpp"

#include <vector>

namespace generate
{
    namespace polynomial_factoring
    {
        struct parameters
        {
            mprgen::integer factor_max;
            mprgen::integer factor_min;
            mprgen::integer front_factor_max;
            mprgen::integer front_factor_min;
            problem_count_t factor_count;
        };

        mprgen::MathProblem problem(
            const parameters& params
        );

        void problem_set(
            const parameters& params,
            const iterator_range_t& range
        );
    };
}