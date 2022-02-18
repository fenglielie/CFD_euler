/*
(2)核心函数层
信息输出在output子文件夹
output.h 声明函数
output.cpp 实现具体的信息输出功能
*/
#pragma once
#include "MyHead.h"

#include "DG/Cell/Cell.h"
#include "DG/Instance/Instance.h"

#include "DG.h" //因为要DG_STR_LEN长度的宏定义

void output(const Instance *the_instance_p, const supermatrix &the_datas, const vector<Cell> &the_cells,
            vector<double> &output_args, const char output_strs[][DG_STR_LEN]);