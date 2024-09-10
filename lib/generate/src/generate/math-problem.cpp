#include "generate/math-problem.hpp"

#include <iostream>

mprgen::MathProblem::MathProblem(const std::string &_problem, const std::string &_solution) :
    problem(_problem),
    solution(_solution)
{
}

const std::string &mprgen::MathProblem::get_problem() const
{
    return problem;
}

const std::string &mprgen::MathProblem::get_solution() const
{
    return solution;
}

void mprgen::ask(const MathProblem &mp)
{
    std::cout << mp.get_problem() << std::endl;
    std::cin.ignore();
    std::cout << mp.get_solution() << std::endl;
}

void mprgen::ask(const std::vector<MathProblem> &mps)
{
    // Ask every question
    std::cout << "Problems:\n";
    for (int i = 0; i < mps.size(); i++) {
        std::cout << i + 1 << ". " << mps[i].get_problem() << std::endl;
    }

    // Collect user input
    std::cin.ignore();

    // Display all solutions
    std::cout << "Solutions:\n";
    for (int i = 0; i < mps.size(); i++) {
        std::cout << i + 1 << ". " << mps[i].get_solution() << std::endl;
    }
}
