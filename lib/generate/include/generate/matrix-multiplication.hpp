#pragma once

#include "generate.hpp"

namespace generate
{
    namespace matrix_multiplication
    {
        struct parameters
        {
            mprgen::integer max_result_rows;
            mprgen::integer min_result_rows;
            mprgen::integer max_shared_dim;
            mprgen::integer min_shared_dim;
            mprgen::integer max_result_cols;
            mprgen::integer min_result_cols;
            mprgen::integer max_cell_value;
            mprgen::integer min_cell_value;
        };

        mprgen::MathProblem problem(
            const parameters& params = {
                3, 1,
                3, 1,
                3, 1,
                9, -9
            }
        );

        void problem_set(
            const parameters& params,
            const iterator_range_t& range
        );
    };
}