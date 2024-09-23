#include <stdexcept>

#include "math/matrix.hpp"

#include "generate/number-gen.hpp"


Matrix::Matrix(mprgen::integer _rows, mprgen::integer _cols)
    : rows(_rows), cols(_cols), data(_rows, std::vector<mprgen::integer>(_cols))
{
}
Matrix::Matrix(mprgen::integer _rows, mprgen::integer _cols, mprgen::IntegerGen& gen)
    : rows(_rows), cols(_cols), data(_rows, std::vector<mprgen::integer>(_cols))
{
    for (mprgen::integer i = 0; i < rows; i++)
    {
        for (mprgen::integer j = 0; j < cols; j++)
        {
            data[i][j] = gen.generate();
        }
    }
}

mprgen::integer Matrix::get(mprgen::integer i, mprgen::integer j) const
{
    return data[i][j];
}

mprgen::integer Matrix::get_row_count() const
{
    return rows;
}
mprgen::integer Matrix::get_col_count() const
{
    return cols;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    if (cols != other.rows)
    {
        throw std::invalid_argument("Matrix dimensions are not compatible for multiplication");
    }

    Matrix result(rows, other.cols);

    for (mprgen::integer i = 0; i < rows; i++)
    {
        for (mprgen::integer j = 0; j < other.cols; j++)
        {
            mprgen::integer sum = 0;
            for (mprgen::integer k = 0; k < cols; k++)
            {
                sum += data[i][k] * other.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }

    return result;
}

std::vector<std::vector<std::string>> Matrix::to_string_justified_cells() const
{
    // Get largest cell value
    mprgen::integer largest_cell_value = 0;
    for (mprgen::integer i = 0; i < rows; i++)
    {
        for (mprgen::integer j = 0; j < cols; j++)
        {
            largest_cell_value = std::max(largest_cell_value, data[i][j]);
        }
    }

    // Get the number of digits in the largest cell value
    mprgen::integer largest_cell_value_digits = 0;
    for (mprgen::integer temp = largest_cell_value; temp > 0; temp /= 10)
    {
        largest_cell_value_digits++;
    }

    auto justify = [largest_cell_value_digits](mprgen::integer cell_value) -> std::string
    {
        std::string str = std::to_string(cell_value);
        while (str.length() < largest_cell_value_digits + 1) // Add 1 to account for the negative sign
        {
            str = " " + str;
        }
        return str;
    };

    // Create the justified rows
    std::vector<std::vector<std::string>> justified_rows(rows, std::vector<std::string>(cols));
    for (mprgen::integer i = 0; i < rows; i++)
    {
        for (mprgen::integer j = 0; j < cols; j++)
        {
            justified_rows[i][j] = justify(data[i][j]);
        }
    }

    return justified_rows;
}

void pop_string_back(std::string &str, std::string_view to_remove)
{
    str.erase(str.length()-to_remove.length());
}

std::vector<std::vector<std::string>> get_justified_matricies(const std::vector<Matrix> &matricies, const JustifiedMatrixFormatting& formatting)
{

    // Get the formatting
    const std::string &cell_spacer = formatting.cell_spacer;
    const std::string &row_start_delimiter = formatting.row_start_delimiter;
    const std::string &row_end_delimiter = formatting.row_end_delimiter;
    const size_t matrix_count = matricies.size();

    // Get the justified rows for each matrix
    std::vector<std::vector<std::vector<std::string>>> justified_rows(matrix_count);
    for (size_t i = 0; i < matrix_count; i++)
    {
        justified_rows.at(i) = matricies.at(i).to_string_justified_cells();
    }

    // Get the maximum cell length for each matrix, will be used to create the spacers for empty rows
    std::vector<size_t> max_cell_lengths(matrix_count);
    for (size_t i = 0; i < matrix_count; i++)
    {
        for (size_t j = 0; j < justified_rows.at(i).size(); j++)
        {
            for (size_t k = 0; k < justified_rows.at(i).at(j).size(); k++)
            {
                max_cell_lengths.at(i) = std::max(max_cell_lengths.at(i), justified_rows.at(i).at(j).at(k).length());
            }
        }
    }

    // Get the maximum row count for all matricies
    size_t max_row_count = 0;
    for (size_t i = 0; i < matrix_count; i++)
    {
        max_row_count = std::max(max_row_count, justified_rows.at(i).size());
    }

    // Hot Loop
    std::vector<std::vector<std::string>> justified_matricies(matrix_count);
    for (size_t i = 0; i < matrix_count; i++)
    {
        justified_matricies.at(i) = std::vector<std::string>(max_row_count);
        const std::vector<std::vector<std::string>> &cell_separated_matrix = justified_rows.at(i); // The matrix of justified cells
        const size_t row_count = cell_separated_matrix.size(); // The number of rows in the matrix
        const size_t &max_cell_length = max_cell_lengths.at(i); // The maximum cell length for the matrix
        std::vector<std::string> &result_matrix = justified_matricies.at(i); // The matrix of justified rows
        const size_t cell_count = cell_separated_matrix.at(0).size(); // The number of cells in the row
        const size_t result_row_length = // The length of the row
            (
                max_cell_length // The justified cell length
                +cell_spacer.size() // The size of the cell spacer
            )
                *cell_count // For each cell
            -cell_spacer.size() // Remove the last cell spacer
            +row_start_delimiter.size() // The size of the row start delimiter
            +row_end_delimiter.size() // The size of the row end delimiter
        ;

        // Create the justified matrix
        size_t j = 0;
        for (; j < row_count; j++) // For each row
        {
            const std::vector<std::string> &cell_separated_row = cell_separated_matrix.at(j); // The row of justified cells
            std::string &result_row = result_matrix.at(j); // The result row string

            result_row = row_start_delimiter; // Add the row start delimiter
            for (size_t k = 0; k < cell_count; k++)
            {
                result_row += cell_separated_row.at(k); // Add the cell
                result_row += cell_spacer; // Add the cell spacer
            }
            pop_string_back(result_row, cell_spacer); // Remove the last cell spacer
            result_row += row_end_delimiter; // Add the row end delimiter
        }
        for (; j < max_row_count; j++) // Fill the rest of the rows with spacers
        {
            std::string &result_row = result_matrix.at(j);

            result_row = std::string(result_row_length, ' ');
        }
    }

    return justified_matricies;
}