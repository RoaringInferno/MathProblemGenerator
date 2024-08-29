#include "generate/matrix-multiplication.hpp"

#include "math/matrix.hpp"

mprgen::MathProblem generate::matrix_multiplication::problem(const parameters &params)
{
    mprgen::integer result_rows, shared_dim, result_cols;
    result_rows = mprgen::IntegerGen({params.min_result_rows, params.max_result_rows}).generate_nonzero();
    shared_dim = mprgen::IntegerGen({params.min_shared_dim, params.max_shared_dim}).generate_nonzero();
    result_cols = mprgen::IntegerGen({params.min_result_cols, params.max_result_cols}).generate_nonzero();

    mprgen::IntegerGen cell_gen({params.min_cell_value, params.max_cell_value});
    Matrix a(result_rows, shared_dim, cell_gen);
    Matrix b(shared_dim, result_cols, cell_gen);

    Matrix result = a * b;

    std::string problem, solution;

    problem = "Multiply matricies\n"; // Add a newline to separate the problem from the rest of the text
    std::vector<std::vector<std::string>> justified_matricies = get_justified_matricies({a, b});
    const size_t row_count = justified_matricies[0].size();
    for (size_t i = 0; i < row_count; i++)
    {
        for (size_t j = 0; j < 2; j++) // Print the first two matricies
        {
            problem += justified_matricies[j][i];
            problem += "\t";
        }
        problem.pop_back(); // Remove the last tab
        problem += "\n";
    }
    problem.pop_back(); // Remove the last newline

    solution = "\n"; // Add a newline to separate the solution from the rest of the text
    std::vector<std::string> justified_result_matrix = get_justified_matricies({result})[0];
    for (auto &row : justified_result_matrix)
    {
        solution += row;
        solution += "\n";
    }
    solution.pop_back(); // Remove the last newline

    return mprgen::MathProblem(problem, solution);
}

void generate::matrix_multiplication::problem_set(const parameters &params, const iterator_range_t &range)
{
    for (generate::problem_iterator_t it = range.begin; it != range.end; it++)
    {
        *it = problem(params);
    }
}