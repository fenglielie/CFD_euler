#include "init.h"

supermatrix init(const Instance *the_instance_p, vector<Cell> &the_cells, vector<double> &init_args)
{
    int output_len = the_instance_p->get_output_len();
    index cell_num = the_cells.size();

    // 从init_args解析参数
    // 第一个参数k,由于是二维的，自动转换为k2
    // 第二个参数gauss_k
    index k = init_args[0];
    index k_2d = (k + 1) * (k + 2) / 2;
    index gauss_k = init_args[1];

    matrix temp(output_len);
    supermatrix result(cell_num, temp);

    for (index i = 0; i < cell_num; i++) {
        for (int j = 0; j < output_len; j++)
            result[i][j] = init_cell(the_instance_p, the_cells[i], j, k_2d, gauss_k);
    }

    return result;
}


vector<double> init_cell(const Instance *the_instance_p, Cell &the_cell, int value_index, index k_2d, index gauss_k)
{
    vector<double> result(k_2d, 0);
    vector<double> u1(k_2d, 0);
    vector<double> u2(k_2d, 0);

    matrix A = newMatrix(k_2d, k_2d);
    // 基函数相互内积
    for (index i = 0; i < k_2d; i++) {
        u1[i] = 1;
        for (index j = 0; j < k_2d; j++) {
            u2[j] = 1;
            A[i][j] = SurfaceIntegrate_init_inner_product(gauss_k, the_cell, base_fun_2d, u1, base_fun_2d, u2);
            u2[j] = 0;
        }
        u1[i] = 0;
    }
    the_cell.set_A_matrix(A);

    // 在这里基于这个单元,绑定它需要的Cell

    vector<double> b(k_2d, 0);
    for (index i = 0; i < k_2d; i++) {
        u1[i] = 1;
        b[i] = SurfaceIntegrate_init_inner_product(gauss_k, value_index, the_instance_p, the_cell, base_fun_2d, u1);
        u1[i] = 0; //清除
    }

    result = Gauss_Elimination(A, b);
    return result;
}