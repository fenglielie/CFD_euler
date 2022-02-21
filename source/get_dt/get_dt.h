/*
(2)核心函数层
获取时间步长在get_dt子文件夹
get_dt.h 声明函数
get_dt.cpp 实现具体的获取时间步长功能
*/
#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "Cell/Cell.h"
#include "Instance/Instance.h"
#include "Fun/Fun.h"

#include "Base/basefunction/basefunction.h"

double get_dt(const Instance *the_instance_p, const supermatrix &the_datas, const vector<Cell> &the_cells, vector<double> &dt_args);

double get_dt_cell(const Instance *the_instance_p, const matrix &data, const Cell &cell, vector<double> &dt_args);