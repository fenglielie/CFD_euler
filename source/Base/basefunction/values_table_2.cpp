#include "values_table.h"

vector<double> get_cell_values_table(index gauss_k, const Cell &the_cell, const vector<base_fun_type_2d> &base_funs, const vector<double> &u)
{
    index cellkind = the_cell.get_cellKind();
    matrix points = get_cell_gausspoints(gauss_k, cellkind);
    index len = points.size();

    vector<double> result(len, 0);
    for (index i = 0; i < len; i++) {
        result[i] = base_fun_2d_evalue(base_funs, u, points[i][0], points[i][1]);
    }

    return result;
}

// 基于instance的初值函数
vector<double> get_cell_values_table_init(index gauss_k, const Cell &the_cell, const Instance *the_instance_p, index out_index)
{
    index cellkind = the_cell.get_cellKind();
    matrix points = get_cell_gausspoints(gauss_k, cellkind);
    index len = points.size();
    double x, y;

    vector<double> result(len, 0);
    for (index i = 0; i < len; i++) {
        x = points[i][0];
        y = points[i][1];
        change_to_global(x, y, the_cell);
        result[i] = the_instance_p->value_init(x, y)[out_index];
    }

    return result;
}

// 基于instance的精确值函数
vector<double> get_cell_values_table_end(index gauss_k, const Cell &the_cell, const Instance *the_instance_p, index out_index, double time_now)
{
    index cellkind = the_cell.get_cellKind();
    matrix points = get_cell_gausspoints(gauss_k, cellkind);
    index len = points.size();
    double x, y;

    vector<double> result(len, 0);
    for (index i = 0; i < len; i++) {
        x = points[i][0];
        y = points[i][1];
        change_to_global(x, y, the_cell);
        result[i] = the_instance_p->value_end(x, y, time_now)[out_index];
    }

    return result;
}



// 产生cell的指定第几条边的高斯点的值的table，用于后续的线积分

// 基于指定的基函数的线性组合
vector<double> get_side_values_table(index gauss_k, const Cell &the_cell, int side_loc, const vector<base_fun_type_2d> &base_funs, const vector<double> &u)
{
    index cellkind = the_cell.get_cellKind();
    matrix points = get_side_gausspoints(gauss_k, cellkind, side_loc);
    index len = points.size();

    vector<double> result(len);
    for (index i = 0; i < len; i++) {
        result[i] = base_fun_2d_evalue(base_funs, u, points[i][0], points[i][1]);
    }

    return result;
}

// 基于instance的初值函数
vector<double> get_side_values_table_init(index gauss_k, const Cell &the_cell, int side_loc, const Instance *the_instance_p, index out_index)
{
    index cellkind = the_cell.get_cellKind();
    matrix points = get_side_gausspoints(gauss_k, cellkind, side_loc);
    index len = points.size();
    double x, y;

    vector<double> result(len, 0);
    for (index i = 0; i < len; i++) {
        x = points[i][0];
        y = points[i][1];
        change_to_global(x, y, the_cell);
        result[i] = the_instance_p->value_init(x, y)[out_index];
    }

    return result;
}

// 基于instance的精确值函数
vector<double> get_side_values_table_end(index gauss_k, const Cell &the_cell, int side_loc, const Instance *the_instance_p, index out_index, double time_now)
{
    index cellkind = the_cell.get_cellKind();
    matrix points = get_side_gausspoints(gauss_k, cellkind, side_loc);
    index len = points.size();
    double x, y;

    vector<double> result(len, 0);
    for (index i = 0; i < len; i++) {
        x = points[i][0];
        y = points[i][1];
        change_to_global(x, y, the_cell);
        result[i] = the_instance_p->value_end(x, y, time_now)[out_index];
    }

    return result;
}
