#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

//表明当前完成的多项式个数，不是最大指标
extern const index base_fun_2d_len;

//暴露的三个函数向量
typedef double (*base_fun_type_2d)(double x, double y);
extern const vector<base_fun_type_2d> base_fun_2d;
extern const vector<base_fun_type_2d> base_fun_2d_x;
extern const vector<base_fun_type_2d> base_fun_2d_y;

// 针对base_funs的求值
// 这里(x,y)是局部坐标
double base_fun_2d_evalue(const vector<base_fun_type_2d> &base_funs,const vector<double> &u, double x, double y);
