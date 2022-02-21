/*
(2)核心函数层
误差计算在error子文件夹
error.h 声明函数
error.cpp 实现具体的误差计算功能
*/
#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "Cell/Cell.h"
#include "Instance/Instance.h"

#include "Base/basefunction/basefunction.h"
#include "Base/surface_integrate/surface_integrate_error.h"

vector<double> error(const Instance *the_instance_p, const supermatrix &the_datas, const vector<Cell> &the_cells, vector<double> &error_args);

double error_cell(const Instance *the_instance_p, const vector<double> &data, const Cell &the_cell,
                  index value_index, index error_kind, index gauss_k, double time_now);