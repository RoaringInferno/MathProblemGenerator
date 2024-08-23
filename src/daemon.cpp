#include "daemon.hpp"

#include "generate/math-problem.hpp"

#include <iostream>
#include <string_view>
#include <fstream>

// Dialogues
const std::string output_file_directory = "output/";
const std::string problem_output_file_name = "problems";
const std::string solution_output_file_name = "solutions";
const std::string output_file_extension = ".txt";

const std::string parallel_generation_verbose_dialogue = "\tSpawning parallel process...";
const std::string series_generation_verbose_dialogue = "\tGenerating in series...";

using namespace std::literals::string_literals; // To get access to the ""s operator
using namespace std::literals::string_view_literals; // To get access to the ""sv operator

generate::iterator_range_t Daemon::generate_spawn_range(const generate::problem_count_t &problem_count)
{
    generate::vector_t* generated_range = new generate::vector_t(problem_count);
    problem_sets.push_back(generated_range);
    return generate::iterator_range(*generated_range);
}

bool Daemon::should_thread(std::string_view process_signature, const generate::problem_count_t &problem_count)
{
    bool force_threaded = settings.get_bool_setting("force-threaded"sv);
    bool force_unthreaded = settings.get_bool_setting("force-unthreaded"sv);
    if (force_threaded ^ force_unthreaded) // If they are different, then parse for which one is on
    {
        if (force_threaded) {
            settings.print_verbose(parallel_generation_verbose_dialogue + "(force_threaded)");
            return true;
        }
        if (force_unthreaded) {
            settings.print_verbose(series_generation_verbose_dialogue + "(force_unthreaded)");
            return false;
        }
    }
    // If the settings are the same, then ignore them
    if (problem_count > settings.get_int_setting(std::string(process_signature) + "-threading-threshold")) {
        settings.print_verbose(parallel_generation_verbose_dialogue);
        return true;
    }
    settings.print_verbose(series_generation_verbose_dialogue);
    return false;
}

void Daemon::cleanup_spawn()
{
    // Join all the threads
    for (spawn& thread : spawns)
    {
        thread.join();
    }
}

void Daemon::ask()
{
    generate::problem_count_t total_problem_count = 0;
    for (generate::vector_t* problem_set_pointer : problem_sets)
    {
        total_problem_count += problem_set_pointer->size();
    }
    generate::vector_t total_problem_set(total_problem_count);
    generate::problem_iterator_t it = total_problem_set.begin();
    for (generate::vector_t* problem_set_pointer : problem_sets)
    {
        for (const mprgen::MathProblem& problem : *problem_set_pointer)
        {
            *it = problem;
            it++;
        }
    }

    // TODO: Implement file push system if the setting is enabled
    if (!settings.get_bool_setting("output-to-file")) {
        mprgen::ask(total_problem_set);
    }
    else {
        std::filesystem::create_directory(output_file_directory);

        std::string problem_output_file_path = output_file_directory + problem_output_file_name + settings.get_file_timestamp().get_datetimestamp() + output_file_extension;
        std::string solution_output_file_path = output_file_directory + problem_output_file_name + settings.get_file_timestamp().get_datetimestamp() + output_file_extension;

        std::ofstream problem_output_file, solution_output_file;
        // Create a file called "problems"
        problem_output_file.open(problem_output_file_path, std::ios::trunc);
        // And a file called "solutions"
        solution_output_file.open(solution_output_file_path, std::ios::trunc);
        // If either already exist, wipe them first
        // Write problems and solutions
        for (const mprgen::MathProblem& problem : total_problem_set)
        {
            problem_output_file << problem.get_problem() << "\n";
            solution_output_file << problem.get_solution() << "\n";
        }

        settings.print_verbose("Wrote output to files " + problem_output_file_path + " and " + solution_output_file_path);
    }
}

void Daemon::execute(const std::vector<std::string> &arguments)
{
    struct {
        std::string_view signature{""sv};
        bool primed{false};

        void prime(std::string_view new_signature)
        {
            primed = true;
            signature = new_signature;
        }
    } argument_cache;

    // Parse the command line arguments
    for (const std::string& argument : arguments)
    {
        const std::string_view argument_view(argument);

        if (argument_cache.primed)
        {
            settings.set_int_setting(argument_cache.signature, stoi(std::string(argument_view)));
            argument_cache.primed = false;
            continue;
        }

        // As you encounter them, change settings
        if (argument_view[0] == '-')
        {
            if (argument_view[1] == '-')
            {
                // Parse Long Options
                const std::string_view setting_signature = argument_view.substr(2);
                if (settings.is_bool_setting(setting_signature))
                {
                    settings.toggle_bool_setting(setting_signature);
                    continue;
                }
                if (settings.is_int_setting(setting_signature))
                {
                    argument_cache.prime(setting_signature);
                    continue;
                }
                const std::string error_message = "Unrecognized option \""s + std::string(setting_signature) + "\", ignoring...\n"s;
                std::cout << error_message << std::flush;
                continue;
            }
            // Parse Short Options
            for (std::string::size_type i = 1; i < argument_view.length(); i++) // This loop fails if the argument's length is equal to the maximum length that can be stored by std::string::size_type
            {
                switch (argument_view[i]) // Parse Short Options
                {
                case 'v': // Verbose
                    settings.toggle_bool_setting("verbose"sv);
                    break;
                case 'f': // File
                    settings.toggle_bool_setting("output-to-file"sv);
                    break;
                };
            }
            continue;
        }
        // If you encounter a process, spawn it
        spawn_process(argument_view);
    }
}