#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "DG/Fun/Fun.h"

class model_Fun : public Fun {
private:
    /* data */
public:
    model_Fun(/* args */);
    ~model_Fun();

    matrix Fu(vector<double> vars) const;
    matrix get_jacobi_eigenvalues(vector<double> vars) const;
};
