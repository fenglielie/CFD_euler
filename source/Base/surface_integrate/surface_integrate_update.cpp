#include "surface_integrate_update.h"

double SurfaceIntegrate_update_main(index gauss_k, const matrix &the_data, Cell &the_cell, index value_index,
                                    const vector<double> &u)
{
    index cellkind = the_cell.get_cellKind();
    vector<double> weights = get_cell_gaussweights(gauss_k, cellkind);
    index len = weights.size();

    vector<double> values1 = get_cell_values_table(gauss_k, the_cell, base_fun_2d, the_data[value_index]);
    vector<double> values2 = get_cell_values_table(gauss_k, the_cell, base_fun_2d, u);

    double result = 0;
    for (index i = 0; i < len; i++) {
        result = result + weights[i] * values1[i] * values2[i];
    }

    result = result * jacobi_det_fabs(the_cell);

    return result;
}

double SurfaceIntegrate_update_Fu(index gauss_k, const Fun *fun_p, const matrix &the_data, Cell &the_cell, index value_index,
                                  const vector<double> &u)
{
    index cellkind = the_cell.get_cellKind();
    vector<double> weights = get_cell_gaussweights(gauss_k, cellkind);
    index len = weights.size();
    index output_len = fun_p->get_output_len();

    matrix values1_pre = newMatrix(output_len, len);
    for (index i = 0; i < output_len; i++) {
        values1_pre[i] = get_cell_values_table(gauss_k, the_cell, base_fun_2d, the_data[i]);
    }

    // Fu 输出尺寸2*output_len
    supermatrix values1_Fu = newSuperMatrix(len, 2, output_len);
    matrix values1 = newMatrix(len, 2);
    vector<double> temp(output_len);
    for (index i = 0; i < len; i++) {
        for (index j = 0; j < output_len; j++) {
            temp[j] = values1_pre[j][i];
        }
        values1_Fu[i] = fun_p->Fu(temp);

        // 这里只挑出来了value_index对应分量
        values1[i][0] = values1_Fu[i][0][value_index];
        values1[i][1] = values1_Fu[i][1][value_index];
    }

    vector<double> values2_x = get_cell_values_table(gauss_k, the_cell, base_fun_2d_x, u);
    vector<double> values2_y = get_cell_values_table(gauss_k, the_cell, base_fun_2d_y, u);

    values2_x = coeff_for_dx(the_cell) * values2_x;
    values2_y = coeff_for_dy(the_cell) * values2_y;

    double result = 0;
    for (index i = 0; i < len; i++) {
        result = result + weights[i] * (values1[i][0] * values2_x[i] + values1[i][1] * values2_y[i]);
    }

    result = result * jacobi_det_fabs(the_cell);

    return result;
}
