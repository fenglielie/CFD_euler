#include "simple_triangle_Instance.h"

triangle_Instance::triangle_Instance(/* args */)
{
    set_output_len(1);
}

triangle_Instance::~triangle_Instance()
{
}

void triangle_Instance::config_instance(vector<double> &config_args)
{
    /*   if (config_args.size() < 2) {
           fprintf(stderr, "triangle_Instance::config_instance: config_args.size() < 2 [error]\n");
       }

       _x_num = config_args[0];
       _y_num = config_args[1];
       _xleft = 0;
       _xright = 2;
       _ydown = 0;
       _yup = 2;
   */
    _config_flag = 1;
    return;
}



vector<Cell> triangle_Instance::create_cells()
{
    if (_config_flag == 0) {
        fprintf(stderr, "triangle_Instance::create_cells: you should config_instance before\n");
        exit(1);
    }

//#define MY

#ifdef MY

    const char str_n[] = "D:/codeMath/CFD_euler/data/mesh/amesh/my2.n";
    const char str_e[] = "D:/codeMath/CFD_euler/data/mesh/amesh/my2.e";
    const char str_s[] = "D:/codeMath/CFD_euler/data/mesh/amesh/my2.s";
#endif
#ifndef MY
    const char str_n[] = "D:/codeMath/CFD_euler/data/mesh/amesh/gd0.n";
    const char str_e[] = "D:/codeMath/CFD_euler/data/mesh/amesh/gd0.e";
    const char str_s[] = "D:/codeMath/CFD_euler/data/mesh/amesh/gd0.s";
#endif
    vector<Cell> result = create_triangle_cell_from_file(str_n, str_e, str_s);
#ifndef MY
    period_modify_triangle_cells(result, 0);
#endif
    return result;
}

vector<double> triangle_Instance::value_init(double x, double y) const
{
    double pi = 4 * atan(1);
    index output_len = get_output_len();
    vector<double> result(output_len);

    result[0] = 1 + 0.2 * sin(2*pi * x);
    result = _fun_p->change_to_conversation_vars(result);

    return result;
}

vector<double> triangle_Instance::value_end(double x, double y, double end_time) const
{
    double pi = 4 * atan(1);
    index output_len = get_output_len();
    vector<double> result(output_len);

    result[0] = 1 + 0.2 * sin(2*pi * (x - end_time));

    result = _fun_p->change_to_conversation_vars(result);
    return result;
}