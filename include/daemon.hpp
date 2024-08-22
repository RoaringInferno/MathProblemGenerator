#pragma once

#include "generate.hpp"
#include "input_parsing.hpp"

#include <vector>
#include <thread>
#include <unordered_map>
#include <string>

class Daemon_settings
{
public:
    typedef int int_value_t;
    typedef bool bool_value_t;
private:
    std::unordered_map<SettingStringHash::type_t, int_value_t> int_settings;
    std::unordered_map<SettingStringHash::type_t, bool_value_t> bool_settings;
public:
    Daemon_settings();

    int_value_t get_int_setting(std::string_view setting_signature) const;
    void set_int_setting(std::string_view setting_signature, const int_value_t& value);
    bool_value_t get_bool_setting(std::string_view setting_signature) const;
    void toggle_bool_setting(std::string_view setting_signature);

    bool is_setting(std::string_view setting_signature) const;
    bool is_bool_setting(std::string_view setting_signature) const;
    bool is_int_setting(std::string_view setting_signature) const;
public: // Utility Functions
    void print_verbose(std::string_view text);
};

class Daemon
{
public:
    typedef std::thread spawn;
private: // Dialogues
    const std::string problem_output_file_path = "problems.txt";
    const std::string solution_output_file_path = "solutions.txt";

    const std::string parallel_generation_verbose_dialogue = "Spawning parallel process...";
    const std::string series_generation_verbose_dialogue = "Generating in series...";
private:
    std::vector<spawn> spawns;
    std::vector<generate::vector_t*> problem_sets;
    Daemon_settings settings;
private:
    generate::iterator_range_t generate_spawn_range(const generate::problem_count_t& problem_count);
    bool should_thread(std::string_view process_signature, const generate::problem_count_t& problem_count);
public:
    Daemon() = default;

    void execute(const std::vector<std::string>& arguments);

    void spawn_process(std::string_view process_signature);
    void cleanup_spawn();

    void ask();
};