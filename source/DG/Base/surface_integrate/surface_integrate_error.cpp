#include "surface_integrate_error.h"

double SurfaceIntegrate_error(index gauss_k, const Instance *the_instance_p, index value_index,
                              const Cell &the_cell, const vector<base_fun_type_2d> &base_funs, const vector<double> &u,
                              index error_kind, double time_now)
{
    index cellkind = the_cell.get_cellKind();
    vector<double> weights = get_cell_gaussweights(gauss_k, cellkind);
    index len = weights.size();
    vector<double> values_1 = get_cell_values_table_end(gauss_k, the_cell, the_instance_p, value_index, time_now);
    vector<double> values_2 = get_cell_values_table(gauss_k, the_cell, base_funs, u);

    double temp = 0;
    double result = 0;
    for (index i = 0; i < len; i++) {
        if (error_kind == 0) {
            temp = fabs(values_1[i] - values_2[i]);
            result = (temp > result) ? temp : result;
        }
        else if (error_kind == 1) {
            result = result + weights[i] * fabs(values_1[i] - values_2[i]);
        }
        else if (error_kind == 2) {
            result = result + weights[i] * (values_1[i] - values_2[i]) * (values_1[i] - values_2[i]);
        }
        else {
        }
    }


    if (error_kind == 0) {
        return result; //无穷误差不需要
    }
    else {
        result = jacobi_det_fabs(the_cell) * result;
        return result;
    }
}
