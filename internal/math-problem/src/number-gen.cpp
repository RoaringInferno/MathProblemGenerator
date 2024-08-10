#include "mprgen/number-gen.hpp"

mprgen::Generator::Generator() :
    gen(std::random_device()())
{
}

mprgen::Generator::gen_type &mprgen::Generator::get_gen()
{
    return gen;
}

mprgen::integer mprgen::IntegerGen::generate(const params &_p)
{
    dist_type dist(_p.min, _p.max);
    return dist(Generator().get_gen());
}

mprgen::IntegerGen::IntegerGen(const params &_p) :
    p(_p),
    dist(p.min, p.max),
    Generator()
{
}

mprgen::integer mprgen::IntegerGen::generate()
{
    return this->dist(this->gen);
}

mprgen::decimal mprgen::DecimalGen::generate(const params &_p)
{
    dist_type dist(_p.min, _p.max);
    return dist(Generator().get_gen());
}

mprgen::DecimalGen::DecimalGen(const params &_p) :
    p(_p),
    dist(p.min, p.max),
    Generator()
{
}

mprgen::decimal mprgen::DecimalGen::generate()
{
    return this->dist(this->gen);
}
