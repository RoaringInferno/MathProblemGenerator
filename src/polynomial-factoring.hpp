#pragma once

#include "mprgen/math-problem.hpp"
#include "mprgen/number.hpp"

namespace generate
{
    mprgen::MathProblem polynomial_factoring(
        mprgen::integer factor_max,
        mprgen::integer factor_min,
        mprgen::integer front_factor_max,
        mprgen::integer front_factor_min,
        uint32_t factor_count
    );
}