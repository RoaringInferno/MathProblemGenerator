#pragma once

#include "generate/number.hpp"
#include "generate/number-gen.hpp"

#include <vector>
#include <string>

class Matrix
{
private:
    std::vector<std::vector<mprgen::integer>> data;

    mprgen::integer rows, cols;
public:
    Matrix(mprgen::integer _rows, mprgen::integer _cols);
    Matrix(mprgen::integer _rows, mprgen::integer _cols, mprgen::IntegerGen& gen);

    mprgen::integer get(mprgen::integer i, mprgen::integer j) const;

    mprgen::integer get_row_count() const;
    mprgen::integer get_col_count() const;

    Matrix operator*(const Matrix& other) const;

    void scramble(const unsigned int opcount, mprgen::IntegerGen& factor_gen);

    std::vector<std::vector<std::string>> to_string_justified_cells() const;
};


struct JustifiedMatrixFormatting
{
    std::string cell_spacer = ", ";
    std::string row_start_delimiter = "[";
    std::string row_end_delimiter = "]";
};
/**
 * First vector separates matrices
 * Second vector separates rows
 * The strings are the rows of the matricies, including brackets and commas
 * 
 * Every vector in the second vector should have the same size
 * Rows out of bounds are strings with spaces equivalent to the size of the other rows, to facilitate inline printing
 */
std::vector<std::vector<std::string>> get_justified_matricies(const std::vector<Matrix>& matricies, const JustifiedMatrixFormatting& formatting = JustifiedMatrixFormatting());