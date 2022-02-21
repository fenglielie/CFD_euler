#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"
#include "Cell.h"

// 基于尺寸信息，创建矩形单元的cells
// 不负责修正边界项，只是把边界单元的相邻单元编号记作-1
vector<Cell> create_rectangle_cell(int x_num, int y_num, double xleft, double xright, double ydown, double yup);

// 具体设置单个矩形的cell
Cell create_rectangle_cell_base(int i, int j, double x1, double x2, double y1, double y2, int x_num, int y_num);

// 周期性修正，作为友元函数直接修改底层
void period_modify_rectangle_cells(vector<Cell> &the_cells, int x_num, int y_num);
