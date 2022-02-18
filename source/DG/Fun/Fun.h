/*
(1)DG框架层
class Fun 是方程信息的类，
负责F(u) F_hat(u) Jacobi 之类的与方程有关的计算
以及守恒型变量和非守恒型变量的转换

*/
#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

class Fun {
private:
    int _output_len = 0;

public:
    Fun();
    ~Fun();

    void set_output_len(int len);
    int get_output_len() const;

    virtual vector<double> change_to_conversation_vars(vector<double> n_vars) const;
    virtual vector<double> change_to_noconversation_vars(vector<double> c_vars) const;

    virtual matrix Fu(vector<double> vars) const;
    virtual matrix get_jacobi_eigenvalues(vector<double> vars) const;
    virtual matrix Fu_hat(vector<double> vars_inside, vector<double> vars_outside, double alpha) const;
};
