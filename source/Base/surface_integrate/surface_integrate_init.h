#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "Cell/Cell.h"
#include "Instance/Instance.h"

#include "Base/basefunction/basefunction.h"
#include "Base/basefunction/values_table.h"

// init 部分

// 在单元内部的面积分，用于计算模的平方，用于init
double SurfaceIntegrate_init_inner_product(index gauss_k, const Cell &the_cell,
                                  const vector<base_fun_type_2d> &base_funs1, const vector<double> &u1,
                                  const vector<base_fun_type_2d> &base_funs2, const vector<double> &u2);

// 在单元内部的面积分，用于计算初值和测试函数的内积，用于init
double SurfaceIntegrate_init_inner_product(index gauss_k, index value_index, const Instance *the_instance_p, const Cell &the_cell,
                                           const vector<base_fun_type_2d> &base_funs, const vector<double> &u);
