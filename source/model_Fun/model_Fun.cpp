#include "model_Fun.h"

model_Fun::model_Fun(/* args */)
{
    set_output_len(2);
}

model_Fun::~model_Fun()
{
}

matrix model_Fun::Fu(vector<double> vars) const
{
    int output_len = get_output_len();
    matrix result = newMatrix(2, output_len);
    result[0][0] = vars[0];
    result[1][1] = vars[1];

    return result;
}
matrix model_Fun::get_jacobi_eigenvalues(vector<double> vars) const
{
    int output_len = get_output_len();
    matrix result = newMatrix(2, output_len);
    result[0][0] = 1;
    result[1][1] = 1;

    return result;
}
