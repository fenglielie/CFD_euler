#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "Fun/Fun.h"

class simple_Fun : public Fun {
private:
    /* data */
public:
    simple_Fun(/* args */);
    ~simple_Fun();

    matrix Fu(vector<double> vars) const;
    matrix get_jacobi_eigenvalues(vector<double> vars) const;
};
