/*
(1)DG框架层
具体五个DG方法的定义,
在本层内实现了init_args之类的参数列表的长度检验，保证下层有足够多的参数进行解析
主要内容都原样传递到下层的(2)核心函数层
*/
#include "DG.h"

#include "init/init.h"
#include "get_dt/get_dt.h"
#include "update/update.h"
#include "error/error.h"
#include "output/output.h"


DG::DG()
{
}

DG::~DG()
{
}

supermatrix DG::DG_init(const Instance *the_instance_p, vector<Cell> &the_cells, vector<double> &init_args)
{
    if (init_args.size() < 2) {
        fprintf(stderr, "DG_init: init_args.size() < 2 [error]\n");
    }
    // init_args解析参数
    // 第一个参数k, 由于是二维的, 此后自动转换为k_2d = (k+1)(k+2)/2
    // 第二个参数gauss_k

    return init(the_instance_p, the_cells, init_args);
}

double DG::DG_get_dt(const Instance *the_instance_p, const supermatrix &the_datas, const vector<Cell> &the_cells, vector<double> &dt_args)
{
    if (dt_args.size() < 2) {
        fprintf(stderr, "DG_get_dt: dt_args.size() < 2 [error]\n");
    }
    // dt_args解析参数
    // 对于矩形单元
    // 第一个参数c1
    // 第二个参数k
    // 最终dt = c1/(2k+1)*(dx/Jx + dy/Jy)

    // TODO 对于三角形单元的dt_args解析

    return get_dt(the_instance_p, the_datas, the_cells, dt_args);
}

supermatrix DG::DG_update(const Instance *the_instance_p, const supermatrix &the_datas, vector<Cell> &the_cells, vector<double> &update_args)
{
    if (update_args.size() < 3) {
        fprintf(stderr, "DG_update: update_args.size() < 3 [error]\n");
    }
    // update_args解析参数
    // 第一个参数是k
    // 第二个参数是dt
    // 第三个参数是gauss_k

    return update(the_instance_p, the_datas, the_cells, update_args);
}

vector<double> DG::DG_error(const Instance *the_instance_p, const supermatrix &the_datas, const vector<Cell> &the_cells, vector<double> &error_args)
{
    if (error_args.size() < 3) {
        fprintf(stderr, "DG_error: error_args.size() < 3 [error]\n");
    }
    // error_args解析
    // 第一个是error类型
    // 第二个是gauss_k
    // 第三个是end_time现在时间
    return error(the_instance_p, the_datas, the_cells, error_args);
}

void DG::DG_output(const Instance *the_instance_p, const supermatrix &the_datas, const vector<Cell> &the_cells, vector<double> &output_args, const char output_strs[][DG_STR_LEN])
{
    if (output_args.size() < 0) {
        fprintf(stderr, "DG_output: output_args.size() < 0 [error]\n");
    }
    // TODO output_args长度检验和参数解析

    return output(the_instance_p, the_datas, the_cells, output_args, output_strs);
}