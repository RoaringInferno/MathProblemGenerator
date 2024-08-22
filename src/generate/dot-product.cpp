#include "generate/dot-product.hpp"

#include "mprgen/number-gen.hpp"
#include "generate/dot-product.hpp"

#include <iostream>

mprgen::MathProblem generate::dot_product::problem(const parameters &params)
{
    std::vector<mprgen::integer> v(params.vector_dimension), w(params.vector_dimension);
    mprgen::integer solution_value = 0;
    std::string v_string, w_string, problem, solution;

    mprgen::IntegerGen generator({params.component_min, params.component_max});

    // Generate values and strings
    v_string = "<";
    w_string = "<";
    for (vector_dimension_t i = 0; i < params.vector_dimension; i++)
    {
        v[i] = generator.generate_nonzero();
        w[i] = generator.generate_nonzero();
        solution_value += v[i] * w[i];

        v_string += std::to_string(v[i]) + ", ";
        w_string += std::to_string(w[i]) + ", ";
    }
    v_string.pop_back(); // Remove ' '
    v_string.pop_back(); // Remove ','
    w_string.pop_back(); // Remove ' '
    w_string.pop_back(); // Remove ','

    v_string += '>';
    w_string += '>';

    problem = v_string + " dot " + w_string;
    solution = std::to_string(solution_value);

    return mprgen::MathProblem(problem, solution);
}

void generate::dot_product::problem_set(const parameters &params, const iterator_range_t &range)
{
    for (generate::problem_iterator_t it = range.begin; it != range.end; it++)
    {
        *it = problem(params);
    }
}
