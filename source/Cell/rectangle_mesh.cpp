#include "rectangle_mesh.h"


vector<Cell> create_rectangle_cell(int x_num, int y_num, double xleft, double xright, double ydown, double yup)
{
    double dx = (xright - xleft) / x_num;
    double dy = (yup - ydown) / y_num;

    int node_num = x_num * y_num;

    // 创建cell的vector，最终返回
    vector<Cell> cells(node_num);

    double node_x_base;
    double node_y_base;

    int count = 0;
    // i行j列
    for (int j = 0; j < y_num; ++j) {
        for (int i = 0; i < x_num; ++i) {
            node_x_base = xleft + i * dx;
            node_y_base = ydown + j * dy; // 记录矩形单元左下角的基准位置

            cells[count] = create_rectangle_cell_base(i, j, node_x_base, node_x_base + dx, node_y_base, node_y_base + dy, x_num, y_num);
            // i行j列的矩形单元，添加4个顶点以及相关内容

            ++count;
        }
    }

    return cells;
}


Cell create_rectangle_cell_base(int i, int j, double x1, double x2, double y1, double y2, int x_num, int y_num)
{
    Cell result;
    int celltype = 4;
    result.set_cellKind_init(celltype);
    result.set_location_flag_init(0);
    result.set_visit_flag(0);

    // 四个顶点之间通过x1 x2 y1 y2 获取，不需要顶点编号

    // 四个相邻单元的编号
    int cell_now = j * x_num + i;
    int cell_left = cell_now - 1;
    int cell_right = cell_now + 1;
    int cell_down = cell_now - x_num;
    int cell_up = cell_now + x_num;

    // 边界单元的编号记作-1修正
    if (i == 0) cell_left = -1;
    if (i == x_num - 1) cell_right = -1;
    if (j == 0) cell_down = -1;
    if (j == y_num - 1) cell_up = -1;

    // 以x_num=4 y_num=3为例
    // 对于边的编号，先横边来一遍，(x_num)*(y_num+1)=16
    // 12 13 14 15
    //  8  9 10 11
    //  4  5  6  7
    //  0  1  2  3
    // 再竖边来一遍 (x_num+1)*(y_num)=15 都+16
    //  2  5  8 11 14
    //  1  4  7 10 13
    //  0  3  6  9 12

    // 四个边的编号
    int side_down = j * x_num + i;
    int side_up = side_down + x_num;
    int side_left = i * y_num + j;
    int side_right = side_left + y_num;
    // 竖边的编号直接加上(x_num)*(y_num+1)
    side_left = side_left + x_num * (y_num + 1);
    side_right = side_right + x_num * (y_num + 1);

    result.set_neighbor_init(cell_down, side_down, x1, y1);
    result.set_neighbor_init(cell_right, side_right, x2, y1);
    result.set_neighbor_init(cell_up, side_up, x2, y2);
    result.set_neighbor_init(cell_left, side_left, x1, y2);

    result.set_outsides_vector();
    result.set_sides_length();

    return result;
}

void period_modify_rectangle_cells(vector<Cell> &the_cells, int x_num, int y_num)
{
    int up_index_base = (y_num - 1) * x_num;
    // 重点是完善边界信息的配置
    // 上下边界的拼接
    for (int i = 0; i < x_num; i++) {
        if (the_cells[i]._neighbors[0] == -1) {
            the_cells[i]._neighbors[0] = up_index_base + i;
            the_cells[up_index_base + i]._neighbors[2] = i;
            // 把最上层的边的编号换成最下层边的编号
            the_cells[up_index_base + i]._sides[2] = the_cells[i]._sides[0];
        }
    }
    // 左右边界的拼接
    for (int j = 0; j < y_num; j++) {
        if (the_cells[j * x_num]._neighbors[3] == -1) {
            the_cells[j * x_num]._neighbors[3] = (j + 1) * x_num - 1;
            the_cells[(j + 1) * x_num - 1]._neighbors[1] = j * x_num;
            // 把最右侧的边的编号换成最左侧的编号
            the_cells[(j + 1) * x_num - 1]._sides[1] = the_cells[j * x_num]._sides[3];
        }
    }

    return;
}