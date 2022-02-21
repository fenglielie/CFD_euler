#include "curve_integrate_update.h"

double CurveIntegrate_update_edge(index gauss_k, const Fun *fun_p, const supermatrix &the_datas, vector<Cell> &the_cells,
                                  index cell_index, index value_index, const vector<double> &u)
{
    index cellkind = the_cells[cell_index].get_cellKind();
    index output_len = the_datas[cell_index].size();

    // 首先需要获取内层的边对应外侧单元的第几条边
    vector<int> sides = the_cells[cell_index].get_sides_list();
    vector<int> neighbors = the_cells[cell_index].get_neighbors_list();
    vector<int> neighbors_side_local_index = sides;
    vector<int> temp_sides = sides;



    int j = 0;
    for (index i = 0; i < cellkind; i++) {
        temp_sides = the_cells[neighbors[i]].get_sides_list();
        for (j = 0; j < cellkind; j++) {
            if (temp_sides[j] == sides[i]) break;
        }
        neighbors_side_local_index[i] = j;
    }

    // 获取当前cell的单位外法向
    matrix out_directions = the_cells[cell_index].get_outside_vector();
    vector<double> side_lengths = the_cells[cell_index].get_sides_length();



    // 然后对每一条边，获得内侧的u值和外侧的u值
    supermatrix inside_values = newSuperMatrix(cellkind, output_len, gauss_k);
    supermatrix outside_values = newSuperMatrix(cellkind, output_len, gauss_k);
    matrix values_2 = newMatrix(cellkind, gauss_k);
    double alpha = 0;
    for (index i = 0; i < cellkind; i++) {
        for (index j = 0; j < output_len; j++) {
            inside_values[i][j] = get_side_values_table(gauss_k, the_cells[cell_index], i, base_fun_2d, the_datas[cell_index][j]);
            outside_values[i][j] = get_side_values_table(gauss_k, the_cells[neighbors[i]], neighbors_side_local_index[i],
                                                         base_fun_2d, the_datas[neighbors[i]][j]); // 尚未进行转向
        }
        values_2[i] = get_side_values_table(gauss_k, the_cells[cell_index], i, base_fun_2d, u);
    }

    // 基于边的两侧的u值，获取F(u)，得到F_hat(u)
    matrix values_1 = newMatrix(cellkind, gauss_k);
    vector<double> inside_temp(output_len);
    vector<double> outside_temp(output_len);


    matrix temp_Fu;
    for (index i = 0; i < cellkind; i++) {
        for (index j = 0; j < gauss_k; j++) {
            // 注意这一层是gauss_k
            for (index j2 = 0; j2 < output_len; j2++) {
                inside_temp[j2] = inside_values[i][j2][j];
                outside_temp[j2] = outside_values[i][j2][gauss_k - 1 - j]; //外侧反向错位
            }
            // 设置alpha
            alpha = 0;
            temp_Fu = fun_p->Fu_hat(inside_temp, outside_temp, alpha);
            //temp_Fu = fun_p->Fu(inside_temp);
            values_1[i][j] = temp_Fu[0][value_index] * out_directions[i][0] + temp_Fu[1][value_index] * out_directions[i][1];
        }
    }

    double result = 0;
    double side_result = 0;
    vector<double> weights;
    for (index i = 0; i < cellkind; i++) {
        side_result = 0;
        weights = get_side_gaussweights(gauss_k, cellkind);
        for (index j = 0; j < gauss_k; j++) {
            side_result = side_result + weights[j] * values_1[i][j] * values_2[i][j];
        }
        side_result = side_result * (side_lengths[i] / 2);

        result = result + side_result;
    }

    return result;
}