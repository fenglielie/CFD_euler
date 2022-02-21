#include "update.h"

supermatrix update(const Instance *the_instance_p, const supermatrix &the_datas, vector<Cell> &the_cells, vector<double> &update_args)
{
    // 只是套了一层rk3
    supermatrix the_datas_1 = the_datas;
    supermatrix the_datas_2 = the_datas;
    supermatrix the_datas_new = the_datas;
    the_datas_1 = update_kernel(the_instance_p, the_datas, the_cells, update_args);
    the_datas_2 = 1.0 / 4 * (3 * the_datas + update_kernel(the_instance_p, the_datas_1, the_cells, update_args));
    the_datas_new = 2.0 / 3 * (0.5 * the_datas + update_kernel(the_instance_p, the_datas_2, the_cells, update_args));

    return the_datas_new;
}

// 欧拉向前，已经加上了增量
supermatrix update_kernel(const Instance *the_instance_p, const supermatrix &the_datas, vector<Cell> &the_cells, vector<double> &update_args)
{
    supermatrix the_datas_new = the_datas;
    index len = the_datas.size();

    for (index i = 0; i < len; i++) { // 按照cell拆解
        the_datas_new[i] = update_kernel_cell(the_instance_p, the_datas, the_cells, i, update_args);
    }

    return the_datas_new;
}


// 拆解到cell层面
matrix update_kernel_cell(const Instance *the_instance_p, const supermatrix &the_datas, vector<Cell> &the_cells, index cell_index, vector<double> &update_args)
{

    // 解析update_args
    // 第一个是k
    // 第二个是dt
    // 第三个是gauss_k
    index k = update_args[0];
    index k_2d = (k + 1) * (k + 2) / 2;
    double dt = update_args[1];
    index gauss_k = update_args[2];
    index output_len = the_instance_p->get_output_len();


    matrix item_main = newMatrix(output_len, k_2d);
    matrix item_Fu = newMatrix(output_len, k_2d);
    matrix item_edge = newMatrix(output_len, k_2d);

    // 按照输出的分量无法进行拆解，因为F(u)把它们混杂在了一起
    // 在一个测试函数的作用下，得到的量应该是一个向量
    vector<double> testfun(k_2d, 0);
    for (index i = 0; i < k_2d; i++) {
        testfun[i] = 1;
        for (index j = 0; j < output_len; j++) {
            item_main[j][i] = SurfaceIntegrate_update_main(gauss_k, the_datas[cell_index], the_cells[cell_index], j, testfun);
            item_Fu[j][i] = SurfaceIntegrate_update_Fu(gauss_k, the_instance_p->_fun_p, the_datas[cell_index], the_cells[cell_index], j, testfun); // 要对测试函数求导
            item_edge[j][i] = CurveIntegrate_update_edge(gauss_k, the_instance_p->_fun_p, the_datas, the_cells, cell_index, j, testfun);           //需要全部数据
        }
        testfun[i] = 0;
    }

    // 以上给出了对于所有分量上的测试函数返回的结果，据此进行计算增量
    // 此后可以拆解各个分量进行

    matrix A = the_cells[cell_index].get_A_matrix();

    matrix result = the_datas[cell_index];
    vector<double> b(k_2d, 0);
    for (index i = 0; i < output_len; i++) {
        printf("h\n");
        readVector(item_main[i]);
        readVector(item_Fu[i]);
        readVector(item_edge[i]);
        b = item_main[i] + dt * (item_Fu[i] - item_edge[i]);
        result[i] = Gauss_Elimination(A, b);
    }

    return result;
}