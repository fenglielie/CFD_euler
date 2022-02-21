#include "Instance.h"

Instance::Instance()
{
}

Instance::~Instance()
{
}

int Instance::get_output_len() const
{
    return _output_len;
}
void Instance::set_output_len(int len)
{
    _output_len = len;
    return;
}



void Instance::config_instance(vector<double> &config_args)
{

    return;
}

void Instance::with_Fun(const Fun *fun_p)
{
    if (fun_p && fun_p->get_output_len() == get_output_len()) {
        _fun_p = fun_p;
    }
    else {
        fprintf(stderr, "Instance::with_Fun output_len not equal [error]\n");
    }
    return;
}

vector<Cell> Instance::create_cells()
{
    fprintf(stderr, "Instance::create_cells: this should not be used\n");
    vector<Cell> temp(_output_len);
    return temp;
}


vector<double> Instance::value_init(double x, double y) const
{
    fprintf(stderr, "Instance::value_init: this should not be used\n");
    vector<double> temp(_output_len);
    return temp;
}

vector<double> Instance::value_end(double x, double y, double end_time) const
{
    fprintf(stderr, "Instance::value_end: this should not be used\n");
    vector<double> temp(_output_len);
    return temp;
}