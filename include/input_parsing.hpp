#pragma once

#include <string>

class SettingStringHash
{
public:
    typedef unsigned char type_t;
public:
    static constexpr inline type_t hash_function(const std::string& option);
private:
    type_t hash;
public:
    constexpr SettingStringHash(const std::string& option);

    constexpr inline type_t value() const;
    operator type_t() const;
};

class ProcessStringHash
{
public:
    enum process_types : unsigned char
    {
        polynomial_factoring
    };

    inline static const std::string PROCESS_NAME[] = {
        "polyfac"
    };
public:
    typedef process_types type_t;
public:
    static constexpr inline type_t hash_function(const std::string& option);
private:
    type_t hash;
public:
    constexpr ProcessStringHash(const std::string& option);

    constexpr inline type_t value() const;
    operator type_t() const;
};

// Inline Definitions
inline constexpr SettingStringHash::type_t SettingStringHash::hash_function(const std::string &option)
{
    return 0;
}

constexpr SettingStringHash::SettingStringHash(const std::string &option) : hash(hash_function(option))
{
}

inline constexpr SettingStringHash::type_t SettingStringHash::value() const
{
    return this->hash;
}