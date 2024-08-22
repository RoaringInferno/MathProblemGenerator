#include "generate.hpp"

generate::iterator_range_t generate::iterator_range(vector_t &range)
{
    return {range.begin(), range.end()};
}