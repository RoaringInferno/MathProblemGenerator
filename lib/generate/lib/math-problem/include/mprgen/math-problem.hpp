#pragma once

#include <string>
#include <vector>

namespace mprgen
{
    class MathProblem
    {
    private:
        std::string problem;
        std::string solution;
    public:
        MathProblem() = default;
        MathProblem(const std::string& _problem, const std::string& _solution);
        const std::string& get_problem() const;
        const std::string& get_solution() const;
    };

    void ask(const MathProblem& mp);
    void ask(const std::vector<MathProblem>& mps);
} // namespace mprgen
