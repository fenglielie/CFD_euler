#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "Cell/Cell.h"

// 把局部坐标映射到全局坐标
void change_to_global(double &x, double &y, Cell the_cell);