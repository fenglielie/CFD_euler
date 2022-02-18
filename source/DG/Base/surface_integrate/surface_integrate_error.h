#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "DG/Cell/Cell.h"
#include "DG/Instance/Instance.h"

#include "DG/Base/basefunction/basefunction.h"
#include "DG/Base/basefunction/values_table.h"

// error 部分

// 在单元内部的面积分，用于计算error
double SurfaceIntegrate_error(index gauss_k, const Instance *the_instance_p, index value_index,
                              const Cell &the_cell, const vector<base_fun_type_2d> &base_funs, const vector<double> &u,
                              index error_kind, double time_now);
