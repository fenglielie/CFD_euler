#include "translate.h"

void change_to_local(double &x, double &y, Cell the_cell)
{
    char cellKind = the_cell.get_cellKind();
    double x_old = x;
    double y_old = y;
    if (cellKind == 4) {
        // 矩形单元
        matrix points = the_cell.get_nodes_list();
        x = -1 + 2 * (x_old - points[0][0]) / (points[1][0] - points[0][0]);
        y = -1 + 2 * (y_old - points[0][1]) / (points[3][1] - points[0][1]);
        return;
    }
    else if (cellKind == 3) {
        // 三角单元全局坐标变为局部坐标
        matrix points = the_cell.get_nodes_list();
        // (x,y)=(x0,y0)+x'(x1-x0,y1-y0)+y'(x2-x0,y2-y0)
        // matrix ((x1-x0,x2-x0),(y1-y0,y2-y0))
        // inverse
        matrix mar_old = newMatrix(2, 2);
        vector<double> b = newVector(2, 0);

        mar_old[0][0] = points[1][0] - points[0][0];
        mar_old[0][1] = points[2][0] - points[0][0];
        mar_old[1][0] = points[1][1] - points[0][1];
        mar_old[1][1] = points[2][1] - points[0][1];

        b[0] = x_old - points[0][0];
        b[1] = y_old - points[0][1];

        double det = mar_old[0][0] * mar_old[1][1] - mar_old[0][1] * mar_old[1][0];

        matrix mar_new = newMatrix(2, 2);
        mar_new[0][0] = mar_old[1][1];
        mar_new[1][1] = mar_old[0][0];
        mar_new[0][1] = -mar_old[0][1];
        mar_new[1][0] = -mar_old[0][1];

        mar_new = (1.0 / det) * mar_new;

        b = mar_new * b;
        x = b[0];
        y = b[1];
        return;
    }
    else {
        fprintf(stderr, "change_to_local: 未知的cellKind\n");
    }
    return;
}

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
