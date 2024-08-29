#pragma once

#include "polynomial-factoring.hpp"
#include "dot-product.hpp"
#include "cross-product.hpp"
#include "matrix-multiplication.hpp"

/*
#pragma once

#include "generate.hpp"

namespace generate
{
    namespace example
    {
        struct parameters
        {
            mprgen::integer max;
            mprgen::integer min;
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

void generate::example::problem_set(const parameters &params, const iterator_range_t &range)
{
    for (generate::problem_iterator_t it = range.begin; it != range.end; it++)
    {
        *it = problem(params);
    }
}
*/