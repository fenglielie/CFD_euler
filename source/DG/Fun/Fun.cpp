#include "Fun.h"

Fun::Fun(/* args */)
{
}

Fun::~Fun()
{
}

void Fun::set_output_len(int len)
{
    _output_len = len;
    return;
}

int Fun::get_output_len() const
{
    return _output_len;
}

vector<double> Fun::change_to_conversation_vars(vector<double> n_vars) const
{
    return n_vars;
}

vector<double> Fun::change_to_noconversation_vars(vector<double> c_vars) const
{
    return c_vars;
}


matrix Fun::Fu(vector<double> vars) const
{
    matrix result = newMatrix(2, _output_len);
    fprintf(stderr, "Fun::Fu: this should not be uesd\n");
    return result;
}

matrix Fun::get_jacobi_eigenvalues(vector<double> vars) const
{
    matrix result = newMatrix(2, _output_len);
    fprintf(stderr, "Fun::get_jacobi_eigenvalues: this should not be uesd\n");
    return result;
}

matrix Fun::Fu_hat(vector<double> vars_inside, vector<double> vars_outside, double alpha) const
{
    matrix result = newMatrix(2, _output_len);
    matrix temp1 = Fu(vars_inside);
    matrix temp2 = Fu(vars_outside);

    result = 0.5 * (temp1 + temp2) - alpha / 2 * (temp2 - temp1);

    return result;
}
