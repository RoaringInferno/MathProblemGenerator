#pragma once

#include "generate.hpp"
#include "input_parsing.hpp"

#include <vector>
#include <thread>
#include <unordered_map>
#include <string>

class daemon_settings
{
public:
    typedef int value_t;
    typedef bool bool_value_t;
private:
    std::unordered_map<SettingStringHash::type_t, value_t> settings;
    std::unordered_map<SettingStringHash::type_t, bool_value_t> bool_settings;
public:
    daemon_settings();

    value_t get_setting(const std::string& setting_signature) const;
    void set_setting(const std::string& setting_signature, const value_t& value);
    bool_value_t get_bool_setting(const std::string& setting_signature) const;
    void toggle_bool_setting(const std::string& setting_signature);
};

class daemon
{
public:
    typedef std::thread spawn;
private:
    std::vector<spawn> spawns;
    daemon_settings settings;
public:
    daemon() = default;

    void execute(int argc, char** argv);

    void spawn_process(const std::string& process_signature);
};