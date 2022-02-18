#include "basefunction.h"

// base_fun_2d

// p0
double p0_2d(double x, double y)
{
    return 1;
}

double p0_2d_x(double x, double y)
{
    return 0;
}

double p0_2d_y(double x, double y)
{
    return 0;
}

// p1
double p1_2d(double x, double y)
{
    return x;
}

double p1_2d_x(double x, double y)
{
    return 1;
}

double p1_2d_y(double x, double y)
{
    return 0;
}

// p2
double p2_2d(double x, double y)
{
    return y;
}

double p2_2d_x(double x, double y)
{
    return 0;
}

double p2_2d_y(double x, double y)
{
    return 1;
}

// p3
double p3_2d(double x, double y)
{
    return (3 * x * x - 1) / 2;
}

double p3_2d_x(double x, double y)
{
    return 3 * x;
}

double p3_2d_y(double x, double y)
{
    return 0;
}

// p4
double p4_2d(double x, double y)
{
    return x * y;
}

double p4_2d_x(double x, double y)
{
    return y;
}

double p4_2d_y(double x, double y)
{
    return x;
}

// p5
double p5_2d(double x, double y)
{
    return (3 * y * y - 1) / 2;
}

double p5_2d_x(double x, double y)
{
    return 0;
}

double p5_2d_y(double x, double y)
{
    return 3 * y;
}



const index base_fun_2d_len = 6;

const vector<base_fun_type_2d> base_fun_2d = {p0_2d, p1_2d, p2_2d, p3_2d, p4_2d, p5_2d};
const vector<base_fun_type_2d> base_fun_2d_x = {p0_2d_x, p1_2d_x, p2_2d_x, p3_2d_x, p4_2d_x, p5_2d_x};
const vector<base_fun_type_2d> base_fun_2d_y = {p0_2d_y, p1_2d_y, p2_2d_y, p3_2d_y, p4_2d_y, p5_2d_y};


double base_fun_2d_evalue(const vector<base_fun_type_2d> &base_funs, const vector<double> &u, double x, double y)
{
    index n = u.size();
    n = (n < base_fun_2d_len) ? n : base_fun_2d_len;

    double result = 0;

    for (index i = 0; i < n; i++) {
        result = result + (u[i] * base_funs[i](x, y));
    }

    return result;
}


