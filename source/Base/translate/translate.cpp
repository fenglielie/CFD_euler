#include "translate.h"

void change_to_global(double &x, double &y, Cell the_cell)
{
    char cellKind = the_cell.get_cellKind();
    double x_old = x;
    double y_old = y;
    if (cellKind == 4) {
        // 矩形单元
        matrix points = the_cell.get_nodes_list();
        x = points[0][0] + (points[1][0] - points[0][0]) * (x_old + 1) / 2;
        y = points[0][1] + (points[3][1] - points[0][1]) * (y_old + 1) / 2;
        return;
    }
    else if (cellKind == 3) {
        // 三角形单元
        matrix points = the_cell.get_nodes_list();
        // [OP] = [OA] + x_old [AB] + y_old [AC];
        x = points[0][0] + x_old * (points[1][0] - points[0][0]) + y_old * (points[2][0] - points[0][0]);
        y = points[0][1] + x_old * (points[1][1] - points[0][1]) + y_old * (points[2][1] - points[0][1]);
        return;
    }
    else {
        fprintf(stderr, "change_to_global: 未知的cellKind\n");
    }
    return;
}
