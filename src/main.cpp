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
        auto generate_term_string = [](const mprgen::integer& coeff, const uint32_t& order) -> std::string
        {
            if (coeff == 0)
            {
                return "";
            }
            if (coeff == 1)
            {
                if (order == 0)
                {
                    return "1";
                }
                if (order == 1)
                {
                    return "x";
                }
                return "x^" + std::to_string(order);
            }
            std::string coeff_str = std::to_string(std::abs(coeff));
            if (order == 0)
            {
                return coeff_str;
            }
            if (order ==1)
            {
                return coeff_str + "x";
            }
            return coeff_str + "x^" + std::to_string(order);
        };
        auto generate_sign_string = [](const mprgen::integer& coeff) -> std::string
        {
            return coeff >= 0 ? " + " : " - ";
        };

        std::string solution;
        std::unordered_map<mprgen::integer, uint32_t> factor_map;
        for (uint64_t i = 0; i < factor_count; i++)
        {
            factor_map[factors[i]]++;
        }
        for (auto& factor : factor_map)
        {
            solution += "(x" + generate_sign_string(factor.first) + std::to_string(std::abs(factor.first)) + ")";
            if (factor.second > 1)
            {
                solution += "^" + std::to_string(factor.second);
            }
        }
        std::string problem = generate_term_string(coefficients[factor_count], factor_count);
        for (uint32_t i = factor_count-1; i > 0; i--)
        {
            if (coefficients[i] == 0) { continue; }
            std::string coeff_str = generate_sign_string(coefficients[i])+ generate_term_string(coefficients[i], i);
            problem += coeff_str;
        }
        problem += generate_sign_string(coefficients[0]) + generate_term_string(coefficients[0], 0);

        return mprgen::MathProblem(problem, solution);
    };
} // namespace generate

int main()
{
    const uint32_t factor_count = 2;
    const uint32_t problem_count = 50;
    std::vector<mprgen::MathProblem> problems(problem_count);

    for (uint32_t i = 0; i < problem_count; i++)
    {
        problems[i] = generate::polynomial_factoring(factor_count);
    }

    ask(problems);
    return 0;
}