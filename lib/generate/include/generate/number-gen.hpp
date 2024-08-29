#pragma once

#include "number.hpp"

#include <random>

namespace mprgen
{
    class Generator
    {
    private:
        typedef std::mt19937 gen_type;
    protected:
        gen_type gen;
    public:
        Generator();

        gen_type& get_gen();
    };

    class IntegerGen : public Generator
    {
    private:
        typedef std::uniform_int_distribution<integer> dist_type;
    public:
        struct params
        {
            integer min;
            integer max;
        };
    private:
        const params& p;
        dist_type dist;
    public:
        static integer generate(const params& _p);

        IntegerGen(const params& _p);
        integer generate();
        integer generate_nonzero();
        const params& get_params() const;
    };

    class DecimalGen : public Generator
    {
    private:
        typedef std::uniform_real_distribution<decimal> dist_type;
    public:
        struct params
        {
            decimal min;
            decimal max;
        };
    private:
        const params& p;
        dist_type dist;
    public:
        static decimal generate(const params& _p);

        DecimalGen(const params& _p);
        decimal generate();
        decimal generate_nonzero();
        const params& get_params() const;
    };
} // namespace mprb