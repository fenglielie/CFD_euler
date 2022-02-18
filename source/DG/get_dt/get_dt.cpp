#include "get_dt.h"

double get_dt(const Instance *the_instance_p, const supermatrix &the_datas, const vector<Cell> &the_cells, vector<double> &dt_args)
{
    // dt_args参数解析，留到下一层进行解析
    double result = MACHINE_LARGE;
    double temp_dt = 0;
    index cell_num = the_cells.size();

    for (index i = 0; i < cell_num; i++) {
        temp_dt = get_dt_cell(the_instance_p, the_datas[i], the_cells[i], dt_args);
        result = (temp_dt < result) ? temp_dt : result;
    }

    return result;
}

double get_dt_cell(const Instance *the_instance_p, const matrix &data, const Cell &cell, vector<double> &dt_args)
{
    int output_len = the_instance_p->get_output_len();
    double result = 0;
    if (cell.get_cellKind() == 4) {
        // 矩形单元
        vector<double> values(output_len);
        for (int j = 0; j < output_len; j++) {
            values[j] = base_fun_2d_evalue(base_fun_2d, data[j], 0, 0); //(0,0)标准矩形的中心
        }

        matrix jacobis = the_instance_p->_fun_p->get_jacobi_eigenvalues(values);
        double lambda_x = norm_inf(jacobis[0]);
        double lambda_y = norm_inf(jacobis[1]);
        // 对于矩形单元
        // 第一个参数c1
        // 第二个参数k   c1/(2k+1)

        double cfl = dt_args[0];
        double k = dt_args[1];
        matrix cellnodes = cell.get_nodes_list();
        double dx = cellnodes[1][0] - cellnodes[0][0];
        double dy = cellnodes[2][1] - cellnodes[1][1];


        result = cfl / (2 * k + 1) * (dx + dy) / (lambda_x + lambda_y);// TODO
    }
    else {
        // TODO
    }
    return result;
}