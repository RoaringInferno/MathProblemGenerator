#include "input_parsing.hpp"

SettingStringHash::operator SettingStringHash::type_t() const
{
    return this->value();
}
