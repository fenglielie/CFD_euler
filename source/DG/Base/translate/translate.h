#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "DG/Cell/Cell.h"

// 具体实现积分计算，包括线积分和面积分

// 把全局坐标映射到局部坐标
// 这里对于矩形单元，映射到[-1,1]^2标准单元
// 对于三角形单元，映射到(0,0)-(1,0)-(0,1)作为三角形标准单元
void change_to_local(double &x, double &y, Cell the_cell);

// 把局部坐标映射到全局坐标
void change_to_global(double &x, double &y, Cell the_cell);