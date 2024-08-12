#include "mprgen/math-problem.hpp"
#include "mprgen/number-gen.hpp"

#include "polynomial-factoring.hpp"

int main()
{
    const uint32_t factor_count = 2;
    const uint32_t problem_count = 50;
    std::vector<mprgen::MathProblem> problems(problem_count);

    for (uint32_t i = 0; i < problem_count; i++)
    {
        problems[i] = generate::polynomial_factoring(
            mprgen::integer(10),
            mprgen::integer(-10),
            mprgen::integer(2),
            mprgen::integer(-2),
            factor_count
        );
    }

    ask(problems);
    return 0;
}