#include "daemon.hpp"

#include <iostream>

// Defining all setting values
#define H SettingStringHash::hash_function

const std::unordered_map<SettingStringHash::type_t, Daemon_settings::int_value_t> all_int_settings = {
    // Polynomial Factoring
    {H("polyfac-front-factor-max"), 2}, // The largest number that will appear as the front coefficient in any factor
    {H("polyfac-front-factor-min"), -2}, // The smallest number that will appear as the front coefficient in any factor
    {H("polyfac-factor-max"), 10}, // The largest number that will appear as the loose number in any factor
    {H("polyfac-factor-min"), -10}, // The smallest number that will appear as the loose number in any factor
    {H("polyfac-factor-count"), 2}, // The number of factors each problem will have (and thus the order of the problem)

    // Dot Product
    {H("dotprod-component-max"), 9}, // The largest number that will appear as a vector component
    {H("dotprod-component-min"), -9}, // The smallest number that will appear as a vector component
    {H("dotprod-vector-dimension"), 3}, // The number of components per vector

    // Threading Thresholds
    // The minimum number of problems being generated that the daemon will spawn a thread in parallel mode instead of series
    {H("polyfac-threading-threshold"), 50},
    {H("dotprod-threading-threshold"), 50},

    // General Settings (I put them at the bottom so I wouldn't have to worry about commas)
    {H("problem-count"), 10} // The amount of problems that are created every batch
};
const std::unordered_map<SettingStringHash::type_t, Daemon_settings::bool_value_t> all_bool_settings = {
    {H("force-threaded"), false}, // Forces the program to generate in parallel. Conflicts with "force-unthreaded"
    {H("force-unthreaded"), false}, // Forces the program to generate in series. Conflicts with "force-threaded"
    
    {H("verbose"), false}, // Short: 'v'. The program will output a parse message for each argument
    {H("output-to-file"), true} // Short: 'f'. The program will output questions to 2 separate text files
};

#undef H

Daemon_settings::Daemon_settings() :
    int_settings(all_int_settings),
    bool_settings(all_bool_settings)
{
}

void Daemon_settings::print_verbose(std::string_view text)
{
    if (this->bool_settings.at(SettingStringHash::hash_function("verbose"))) { std::cout << text << std::endl; };
}

Daemon_settings::int_value_t Daemon_settings::get_int_setting(std::string_view setting_signature) const
{
    return this->int_settings.at(SettingStringHash::hash_function(setting_signature));
}

void Daemon_settings::set_int_setting(std::string_view setting_signature, const Daemon_settings::int_value_t &value)
{
    print_verbose("Setting \"" + std::string(setting_signature) + "\" to " + std::to_string(value));
    this->int_settings.at(SettingStringHash::hash_function(setting_signature)) = value;
}

Daemon_settings::bool_value_t Daemon_settings::get_bool_setting(std::string_view setting_signature) const
{
    return this->bool_settings.at(SettingStringHash::hash_function(setting_signature));
}

void Daemon_settings::toggle_bool_setting(std::string_view setting_signature)
{
    const auto bool_to_string = [](const bool value) -> std::string
    {
        if (value) { return  "true"; }
        return "false";
    };

    bool_value_t& setting = this->bool_settings.at(SettingStringHash::hash_function(setting_signature));
    setting = !setting;
    print_verbose("Toggling setting \"" + std::string(setting_signature) + "\" to " + bool_to_string(setting));
}

bool Daemon_settings::is_setting(std::string_view setting_signature) const
{
    return is_bool_setting(setting_signature) || is_int_setting(setting_signature);
}

bool Daemon_settings::is_bool_setting(std::string_view setting_signature) const
{
    if (bool_settings.find(SettingStringHash::hash_function(setting_signature)) != bool_settings.end()) { return true; }
    return false;
}

bool Daemon_settings::is_int_setting(std::string_view setting_signature) const
{
    if (int_settings.find(SettingStringHash::hash_function(setting_signature)) != int_settings.end()) { return true; }
    return false;
}