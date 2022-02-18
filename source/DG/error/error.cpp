#include "error.h"

vector<double> error(const Instance *the_instance_p, const supermatrix &the_datas, const vector<Cell> &the_cells, vector<double> &error_args)
{
    int output_len = the_instance_p->get_output_len();
    index cell_num = the_cells.size();

    // error_args解析
    // 第一个是error类型
    // 第二个是gauss_k
    // 第三个是end_time现在时间
    int error_kind = error_args[0];
    index gauss_k = error_args[1];
    double time_now = error_args[2];

    matrix errors = newMatrix(cell_num, output_len);

    for (index i = 0; i < cell_num; i++) {
        for (int j = 0; j < output_len; j++) {
            errors[i][j] = error_cell(the_instance_p, the_datas[i][j], the_cells[i], j, error_kind, gauss_k, time_now);
        }
    }

    // 把矩阵errors计算得到向量版的error
    vector<double> result(output_len, 0);

    for (int j = 0; j < output_len; j++) {
        for (int i = 0; i < cell_num; i++) {
            if (error_kind == 0) {
                result[j] = (errors[i][j] > result[j]) ? errors[i][j] : result[j];
            }
            else if (error_kind == 1) {
                result[j] += errors[i][j];
            }
            else if (error_kind == 2) {
                result[j] += errors[i][j];
            }
            else {
            }
        }

        if (error_kind == 2) {
            result[j] = sqrt(result[j]);
        }
    }

    return result;
}

double error_cell(const Instance *the_instance_p, const vector<double> &data, const Cell &the_cell,
                  index value_index, index error_kind, index gauss_k, double time_now)
{
    return SurfaceIntegrate_error(gauss_k, the_instance_p, value_index, the_cell, base_fun_2d, data, error_kind, time_now);
}