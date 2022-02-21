#include "surface_integrate_init.h"

double SurfaceIntegrate_init_inner_product(index gauss_k, const Cell &the_cell,
                                  const vector<base_fun_type_2d> &base_funs1, const vector<double> &u1,
                                  const vector<base_fun_type_2d> &base_funs2, const vector<double> &u2)
{
    index cellkind = the_cell.get_cellKind();
    vector<double> weights = get_cell_gaussweights(gauss_k, cellkind);
    index len = weights.size();
    vector<double> values1 = get_cell_values_table(gauss_k, the_cell, base_funs1, u1);
    vector<double> values2 = get_cell_values_table(gauss_k, the_cell, base_funs2, u2);

    double result = 0;
    for (index i = 0; i < len; i++) {
        result = result + weights[i] * values1[i] * values2[i];
    }

    result = result * jacobi_det_fabs(the_cell);

    return result;
}

double SurfaceIntegrate_init_inner_product(index gauss_k, index value_index, const Instance *the_instance_p, const Cell &the_cell,
                                           const vector<base_fun_type_2d> &base_funs, const vector<double> &u)
{
    index cellkind = the_cell.get_cellKind();
    vector<double> weights = get_cell_gaussweights(gauss_k, cellkind);
    index len = weights.size();
    vector<double> values_1 = get_cell_values_table_init(gauss_k, the_cell, the_instance_p, value_index);
    vector<double> values_2 = get_cell_values_table(gauss_k, the_cell, base_funs, u);

    double result = 0;
    for (index i = 0; i < len; i++) {
        result = result + weights[i] * values_1[i] * values_2[i];
    }

    result = result * jacobi_det_fabs(the_cell);

    return result;
}