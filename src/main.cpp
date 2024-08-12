#include "mprgen/math-problem.hpp"
#include "mprgen/number-gen.hpp"

namespace generate
{
    mprgen::MathProblem polynomial_factoring(uint32_t factor_count)
    {
        const mprgen::integer factor_max = 10;
        const mprgen::integer factor_min = -1*factor_max;
        const mprgen::integer front_factor_max = 3;
        const mprgen::integer front_factor_min = -1*front_factor_max;

        mprgen::IntegerGen factor_gen({factor_min, factor_max});
        mprgen::integer factors[factor_count];
        for (uint64_t i = 0; i < factor_count; i++)
        {
            do // Ensure that the factor is not 0
            {
                factors[i] = factor_gen.generate();
            } while (factors[i] == 0);
        }
        mprgen::IntegerGen front_factor_gen({front_factor_min, front_factor_max});
        mprgen::integer front_factors[factor_count];
        for (uint64_t i = 0; i < factor_count; i++)
        {
            do // Ensure that the factor is not 0
            {
                front_factors[i] = front_factor_gen.generate();
            } while (front_factors[i] == 0);
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
                    coeff *= front_factors[i]; // Multiply the coefficient by the front factor
                    ++order;
                    if (carry) // Trample the carry bit
                    {
                        x_multiplied[i] = false;
                    }
                }
            }
            coefficients[order] += coeff; // Add to the coefficient
        } while (!carry); // If the carry bit is set left over

        // Helper functions
        auto generate_term_string = [](const mprgen::integer& coeff, const uint32_t& order) -> std::string // Generates a string for a term
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
        auto generate_sign_string = [](const mprgen::integer& coeff) -> std::string // Generates a sign string
        {
            return coeff >= 0 ? " + " : " - ";
        };

        // Constructing the solution
        std::string solution;
        struct factor_pair // Represents a factor and its front factor
        {
            mprgen::integer front_factor;
            mprgen::integer factor;
        };
        auto generate_factor_string = [&](const factor_pair& factor) -> std::string // Generates a string for a factor pair
        {
            std::string fstr = "";
            if (factor.front_factor == 1) { fstr += "x"; }
            else if (factor.front_factor == -1) { fstr += "-x"; }
            else if (factor.front_factor == 0) {  }
            else { fstr += std::to_string(factor.front_factor) + "x"; }
            if (factor.factor == 0) {  }
            else { fstr += generate_sign_string(factor.factor) + std::to_string(std::abs(factor.factor)); }
            return fstr;
        };
        std::unordered_map<std::string, uint32_t> factor_map; // Maps factor strings to their exponents
        for (uint64_t i = 0; i < factor_count; i++) // Construct the factor map
        {
            factor_map[generate_factor_string({front_factors[i], factors[i]})]++;
        }
        for (auto& factor : factor_map) // Stitch the solution string
        {
            solution += "(" + factor.first + ")";
            if (factor.second > 1)
            {
                solution += "^" + std::to_string(factor.second);
            }
        }
        // Constructing the problem
        std::string problem = generate_term_string(coefficients[factor_count], factor_count);
        for (uint32_t i = factor_count-1; i > 0; i--) // Construct the problem string
        {
            if (coefficients[i] == 0) { continue; } // Skip if the coefficient is 0
            std::string coeff_str = generate_sign_string(coefficients[i])+ generate_term_string(coefficients[i], i); // Generate the term string
            problem += coeff_str; // Append the term string
        }
        problem += generate_sign_string(coefficients[0]) + generate_term_string(coefficients[0], 0); // Append the constant term

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