#include "mprgen/math-problem.hpp"
#include "mprgen/number-gen.hpp"

#include "generate.hpp"
#include "polynomial-factoring.hpp"
#include "daemon.hpp"

void polynomial(const generate::iterator_range_t& range)
{
    const uint32_t factor_count = 2;
    const mprgen::integer factor_max = 10;
    const mprgen::integer factor_min = -10;
    const mprgen::integer front_factor_max = 2;
    const mprgen::integer front_factor_min = -2;
    generate::polynomial_factoring::parameters params = {factor_max, factor_min, front_factor_max, front_factor_min, factor_count};
    

    generate::polynomial_factoring::problem_set(params, range);
}

generate::iterator_range_t reserve(std::vector<generate::vector_t*>& problems, generate::problem_count_t count)
{
    generate::vector_t* problem_set = new generate::vector_t(count);
    problems.push_back(problem_set);
    return generate::iterator_range(*problem_set);
}

int main(int argc, char** argv)
{
    std::vector<std::string> arguments(argc-1);
    for (unsigned int i = 1; i < argc; i++)
    {
        arguments[i-1] = std::string(argv[i]);
    }
    
    Daemon master;
    master.execute(arguments);
    master.cleanup_spawn();
    master.ask();

    /*
    const uint32_t problem_count = 10;

    std::vector<generate::vector_t*> problems;

    generate::iterator_range_t range = reserve(problems, problem_count);
    polynomial(range);

    for (const generate::vector_t* problem_set : problems)
    {
        ask(*problem_set);
    }*/
    return 0;
}