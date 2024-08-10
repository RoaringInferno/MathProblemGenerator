#include "mprgen/math-problem.hpp"
#include "mprgen/number-gen.hpp"

namespace generate
{
    mprgen::MathProblem polynomial_factoring(uint32_t factor_count)
    {
        const mprgen::integer factor_max = 10;
        const mprgen::integer factor_min = -1*factor_max;

        mprgen::IntegerGen ig({factor_min, factor_max});
        
        mprgen::integer factors[factor_count];
        for (uint64_t i = 0; i < factor_count; i++)
        {
            do // Ensure that the factor is not 0
            {
                factors[i] = ig.generate();
            } while (factors[i] == 0);
        }

        // Setting coefficients
        mprgen::integer coefficients[factor_count+1];
        for (uint64_t i = 0; i < factor_count+1; i++)
        {
            coefficients[i] = 0;
        }
        bool x_multiplied[factor_count]; // Tracks which factors have used x and which haven't
        bool carry; // Binary adding, but manual TODO: (find a way to do this with addition later)
        do
        {
            mprgen::integer coeff = 1;
            carry = true;
            uint32_t order = 0;
            for (uint64_t i = 0; i < factor_count; i++)
            {
                if (!x_multiplied[i])
                {
                    coeff *= factors[i]; // Multiply the coefficient by the factor
                    if (carry) // Drop the carry bit
                    {
                        x_multiplied[i] = true;
                        carry = false;
                    }
                }
                else
                {
                    ++order;
                    if (carry) // Trample the carry bit
                    {
                        x_multiplied[i] = false;
                    }
                }
            }
            coefficients[order] += coeff; // Add to the coefficient
        } while (!carry); // If the carry bit is set left over

        // Constructing the problem
        std::string solution;
        for (uint64_t i = 0; i < factor_count; i++)
        {
            std::string factor_str = "(x " + (std::string)(factors[i] > 0 ? "+" : "-") + " " + std::to_string(std::abs(factors[i])) + ")";
            solution += factor_str;
        }
        std::string problem = (coefficients[factor_count] > 0 ? "" : "-") + std::to_string(coefficients[factor_count]) + "x^" + std::to_string(factor_count);
        for (uint32_t i = factor_count-1; i > 0; i++)
        {
            std::string coeff_str = (coefficients[i] > 0 ? " + " : " - ") + std::to_string(coefficients[i]) + "x^" + std::to_string(i);
            problem += coeff_str;
        }
        problem += (coefficients[0] > 0 ? " + " : " - ") + std::to_string(coefficients[0]);

        return mprgen::MathProblem(problem, solution);
    };
} // namespace generate

int main()
{
    const uint32_t factor_count = 2;
    const uint32_t problem_count = 50;
    std::vector<mprgen::MathProblem> problems(problem_count);
    /*
    for (uint32_t i = 0; i < problem_count; i++)
    {
        problems[i] = generate::polynomial_factoring(factor_count);
    }
    */


    mprgen::IntegerGen ig({-20, 20});
    auto generate = [&ig]() -> mprgen::integer
    {
        mprgen::integer x = ig.generate();
        while (x == 0)
        {
            x = ig.generate();
        }
        return x;
    };

    auto generatesign = [](mprgen::integer x) -> std::string
    {
        return x > 0 ? "+" : "-";
    };
    auto printstring = [&generatesign](mprgen::integer x) -> std::string
    {
        return std::string(" " +generatesign(x) + " " + std::to_string(std::abs(x)));
    };
    for (uint32_t i = 0; i < problem_count; i++)
    {
        mprgen::integer x1 = generate();
        mprgen::integer x2 = generate();
        mprgen::integer c = x1*x2;
        mprgen::integer b = x1+x2;
        problems[i] = mprgen::MathProblem(
            "x^2" + printstring(b) + "x" + printstring(c),
            "(x" + printstring(x1) + ")(x" + printstring(x2) + ")"
        );
    }
    ask(problems);
    return 0;
}