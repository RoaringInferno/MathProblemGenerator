#include "daemon.hpp"

// Defining all setting values
#define H SettingStringHash::hash_function

const std::unordered_map<SettingStringHash::type_t, daemon_settings::value_t> all_settings = {
    // Polynomial Factoring
    {H(ProcessStringHash::PROCESS_NAME[ProcessStringHash::polynomial_factoring] + "-front-factor-max"), 2}, // The largest number that will appear as the front coefficient in any factor
    {H(ProcessStringHash::PROCESS_NAME[ProcessStringHash::polynomial_factoring] + "-front-factor-min"), -2}, // The smallest number that will appear as the front coefficient in any factor
    {H(ProcessStringHash::PROCESS_NAME[ProcessStringHash::polynomial_factoring] + "-factor-max"), 10}, // The largest number that will appear as the loose number in any factor
    {H(ProcessStringHash::PROCESS_NAME[ProcessStringHash::polynomial_factoring] + "-factor-min"), -10}, // The smallest number that will appear as the loose number in any factor
    {H(ProcessStringHash::PROCESS_NAME[ProcessStringHash::polynomial_factoring] + "-factor-count"), 2}, // The number of factors each problem will have (and thus the order of the problem)

    // Threading Thresholds
    // The minimum number of problems being generated that the daemon will spawn a thread in parallel mode instead of series
    {H(ProcessStringHash::PROCESS_NAME[ProcessStringHash::polynomial_factoring] + "-threading-threshold"), 100},

    // General Settings (I put them at the bottom so I wouldn't have to worry about commas ngl)
    {H("problem-count"), 10} // The amount of problems that are created every batch
};
const std::unordered_map<SettingStringHash::type_t, daemon_settings::bool_value_t> all_bool_settings = {
    {H("force-threaded"), false}, // Forces the program to generate in parallel. Conflicts with "force-unthreaded"
    {H("force-unthreaded"), false} // Forces the program to generate in series. Conflicts with "force-threaded"
};

#undef H

daemon_settings::daemon_settings() :
    settings(all_settings),
    bool_settings(all_bool_settings)
{
}

daemon_settings::value_t daemon_settings::get_setting(const std::string &setting_signature) const
{
    return this->settings.at(SettingStringHash(setting_signature).value());
}

void daemon_settings::set_setting(const std::string &setting_signature, const daemon_settings::value_t &value)
{
    this->settings.at(SettingStringHash(setting_signature).value()) = value;
}

daemon_settings::bool_value_t daemon_settings::get_bool_setting(const std::string &setting_signature) const
{
    return this->bool_settings.at(SettingStringHash(setting_signature).value());
}

void daemon_settings::toggle_bool_setting(const std::string &setting_signature)
{
    bool_value_t& setting = this->bool_settings.at(SettingStringHash(setting_signature).value());
    setting = !setting;
}

void daemon::execute(int argc, char **argv)
{
    // TODO
}

void daemon::spawn_process(const std::string &process_signature)
{
    // TODO
}
