/*
(2)核心函数层
初始化在init子文件夹
init.h 声明函数
init.cpp 实现具体的init功能
*/
#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"
#include "MyLinearSolve/Gauss_Elimination.h"

#include "Cell/Cell.h"
#include "Instance/Instance.h"

#include "Base/basefunction/basefunction.h"
#include "Base/surface_integrate/surface_integrate_init.h"

supermatrix init(const Instance *the_instance_p, vector<Cell> &the_cells, vector<double> &init_args);

// 在一个cell上的针对一个分量的初始化
vector<double> init_cell(const Instance *the_instance_p, Cell &the_cell, int value_index, index k_2d, index gauss_k);