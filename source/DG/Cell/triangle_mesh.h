#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"
#include "Cell.h"

// 从文件中读取三角单元信息，创建cells
// 不负责修正边界项，只是把边界单元的相邻单元编号记作-1
vector<Cell> create_triangle_cell_from_file(const char *nodefile_name, const char *elementfile_name, const char *sidefile_name);

matrix read_matrix_from_file(const char *str, index len);


