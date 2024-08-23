#include "generate/cross-product.hpp"

#include "generate/number-gen.hpp"

mprgen::MathProblem generate::cross_product::problem(const parameters &params)
{
    std::array<mprgen::integer, 3> a, b, c;

    mprgen::IntegerGen gen({params.component_min, params.component_max});

    // Generate Vector A
    a[0] = gen.generate_nonzero();
    a[1] = gen.generate_nonzero();
    a[2] = gen.generate_nonzero();

    // Generate Vector B
    b[0] = gen.generate_nonzero();
    b[1] = gen.generate_nonzero();
    b[2] = gen.generate_nonzero();

    // Compute Cross Product
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[3] - a[1] * b[0];

    std::string problem, solution;
    // Generate Problem
    problem = "<" + std::to_string(a[0]) + ", " + std::to_string(a[1]) + ", " + std::to_string(a[2]) + "> cross <" + std::to_string(b[0]) + ", " + std::to_string(b[1]) + ", " + std::to_string(b[2]) + ">";
    // Generate Solution
    solution = "<" + std::to_string(c[0]) + ", " + std::to_string(c[1]) + ", " + std::to_string(c[2]) + ">";

    return mprgen::MathProblem(problem, solution);
}

void generate::cross_product::problem_set(const parameters &params, const iterator_range_t &range)
{
    for (generate::problem_iterator_t it = range.begin; it != range.end; it++)
    {
        *it = problem(params);
    }
}
