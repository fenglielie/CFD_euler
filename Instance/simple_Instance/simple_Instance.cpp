#include "simple_Instance.h"

simple_Instance::simple_Instance(/* args */)
{
    set_output_len(1);
}

simple_Instance::~simple_Instance()
{
}

void simple_Instance::config_instance(vector<double> &config_args)
{
    if (config_args.size() < 2) {
        fprintf(stderr, "simple_Instance::config_instance: config_args.size() < 2 [error]\n");
    }

    _x_num = config_args[0];
    _y_num = config_args[1];
    _xleft = 0;
    _xright = 2;
    _ydown = 0;
    _yup = 2;

    _config_flag = 1;
    return;
}



vector<Cell> simple_Instance::create_cells()
{
    if (_config_flag == 0) {
        fprintf(stderr, "simple_Instance::create_cells: you should config_instance before\n");
        exit(1);
    }
    vector<Cell> result = create_rectangle_cell(_x_num, _y_num, _xleft, _xright, _ydown, _yup);
    period_modify_rectangle_cells(result, _x_num, _y_num);
    return result;
}

vector<double> simple_Instance::value_init(double x, double y) const
{
    double pi = 4 * atan(1);
    index output_len = get_output_len();
    vector<double> result(output_len);

    result[0] = 1 + 0.2 * sin(pi * x);
    result = _fun_p->change_to_conversation_vars(result);

    return result;
}

vector<double> simple_Instance::value_end(double x, double y, double end_time) const
{
    double pi = 4 * atan(1);
    index output_len = get_output_len();
    vector<double> result(output_len);

    result[0] = 1 + 0.2 * sin(pi * (x - end_time));

    result = _fun_p->change_to_conversation_vars(result);
    return result;
}