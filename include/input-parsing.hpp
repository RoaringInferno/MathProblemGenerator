#pragma once

#include <string>

class SettingStringHash
{
public:
    //typedef unsigned char type_t;
    typedef std::string type_t;
public:
    static constexpr inline type_t hash_function(std::string_view option);
private:
    type_t hash;
public:
    constexpr SettingStringHash(std::string_view option);

    constexpr inline type_t value() const;
    operator type_t() const;
};

enum process : unsigned char
{
    polynomial_factoring
};

inline static const std::string PROCESS_SIGNATURE[] = {
    "polyfac"
};

class ProcessStringHash
{
public:
    typedef process type_t;
public:
    static constexpr inline type_t hash_function(std::string_view option);
private:
    type_t hash;
public:
    constexpr ProcessStringHash(std::string_view option);

    constexpr inline type_t value() const;
    operator type_t() const;
};

// Inline Definitions
inline constexpr SettingStringHash::type_t SettingStringHash::hash_function(std::string_view option)
{
    return std::string(option);
    /*
    // TODO: Implement a modular hashing function for this
    if (option == "polyfac-front-factor-max") return 0;
    if (option == "polyfac-front-factor-min") return 1;
    if (option == "polyfac-factor-max") return 2;
    if (option == "polyfac-factor-min") return 3;
    if (option == "polyfac-factor-count") return 4;
    if (option == "polyfac-threading-threshold") return 5;
    if (option == "problem-count") return 6;
    return 0;
    */
}

constexpr SettingStringHash::SettingStringHash(std::string_view option) : hash(hash_function(option))
{
}

inline constexpr SettingStringHash::type_t SettingStringHash::value() const
{
    return this->hash;
}

inline constexpr ProcessStringHash::type_t ProcessStringHash::hash_function(std::string_view option)
{
    return polynomial_factoring;
}

constexpr ProcessStringHash::ProcessStringHash(std::string_view option) : hash(hash_function(option))
{
}

inline constexpr ProcessStringHash::type_t ProcessStringHash::value() const
{
    return this->hash;
}