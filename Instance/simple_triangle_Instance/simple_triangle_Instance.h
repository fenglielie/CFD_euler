#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "Cell/Cell.h"
#include "Instance/Instance.h"

#include "Cell/triangle_mesh.h"

class triangle_Instance : public Instance {
private:
    int _x_num = 0;
    int _y_num = 0;
    double _xleft = 0;
    double _xright = 0;
    double _ydown = 0;
    double _yup = 0;

    int _config_flag = 0;

public:
    triangle_Instance();
    ~triangle_Instance();

    void config_instance(vector<double> &config_args);

    void with_Fun(const Fun *fun_p);
    vector<Cell> create_cells();
    vector<double> value_init(double x, double y) const;
    vector<double> value_end(double x, double y, double end_time) const;
};
