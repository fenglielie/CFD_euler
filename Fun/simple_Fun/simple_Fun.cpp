#include "simple_Fun.h"

simple_Fun::simple_Fun(/* args */)
{
    set_output_len(1);
}

simple_Fun::~simple_Fun()
{
}

matrix simple_Fun::Fu(vector<double> vars) const
{
    int output_len = get_output_len();
    matrix result = newMatrix(2, output_len);
    result[0][0] = vars[0];
    result[1][0] = 0;

    return result;
}
matrix simple_Fun::get_jacobi_eigenvalues(vector<double> vars) const
{
    int output_len = get_output_len();
    matrix result = newMatrix(2, output_len);
    result[0][0] = 1;
    result[1][0] = 0;

    return result;
}
