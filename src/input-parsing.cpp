#include "input-parsing.hpp"

SettingStringHash::operator SettingStringHash::type_t() const
{
    return this->value();
}

ProcessStringHash::operator type_t() const
{
    return this->value();
}