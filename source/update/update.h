/*
(2)核心函数层
更新在update子文件夹
update.h 声明函数
update.cpp 实现具体的更新功能
*/
#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"
#include "MyLinearSolve/LinearSolve.h"

#include "Cell/Cell.h"
#include "Instance/Instance.h"
#include "Fun/Fun.h"

#include "Base/curve_integrate/curve_integrate_update.h"
#include "Base/surface_integrate/surface_integrate_update.h"


supermatrix update(const Instance *the_instance_p, const supermatrix &the_datas, vector<Cell> &the_cells, vector<double> &update_args);

supermatrix update_kernel(const Instance *the_instance_p, const supermatrix &the_datas, vector<Cell> &the_cells, vector<double> &update_args);

matrix update_kernel_cell(const Instance *the_instance_p, const supermatrix &the_datas, vector<Cell> &the_cells, index cell_index, vector<double> &update_args);