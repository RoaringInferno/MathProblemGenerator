#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "generate/all-problems.hpp"

void profile(
    std::string_view process_name,
    std::function<void()> function,
    unsigned int iterations = 100000
)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (unsigned int i = 0; i < iterations; i++)
    {
        function();
    }
    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << process_name << ", over " << iterations << " iterations, took " << duration << "ms";
    std::cout << "(" << duration/iterations << " ms per iteration)" << std::endl;
};

int main()
{
    profile("Polynomial Factoring", [](){
        mprgen::MathProblem temp = generate::polynomial_factoring::problem();
    });

    profile("Dot Product", [](){
        mprgen::MathProblem temp = generate::dot_product::problem();
    });

    profile("Cross Product", [](){
        mprgen::MathProblem temp = generate::cross_product::problem();
    });

    profile("Matrix Multiplication", [](){
        mprgen::MathProblem temp = generate::matrix_multiplication::problem();
    });

    std::vector<std::thread> threads;
    profile("Thread Spawning", [&threads](){
        threads.push_back(std::thread([](){}));
    }, 1000);

    profile("Thread Joining", [&threads](){
        for (auto& thread : threads)
        {
            thread.join();
        }
    }, 1);

    return 0;
}