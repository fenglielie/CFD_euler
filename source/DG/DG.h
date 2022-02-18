/*
(1)DG框架层
class DG 是一个空的框架，包括了DG需要的五个主要函数
DG_init, DG_get_dt, DG_update, DG_error, DG_output
这些方法定义在DG.h, 实现在DG.cpp
其实DG.cpp 对于这些方法没有做任何处理, 只是进行了参数列表的检验, 要求参数args至少有若干位.
然后原样传递给下层的与DG类无关的具体函数.
这些函数分别在 init, get_dt, update, error, output 五个子文件夹中实现, 也就是传递到了下层的(2)核心函数层
*/
#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "Cell/Cell.h"
#include "Instance/Instance.h"
#include "DG/Fun/Fun.h"

#ifndef DG_STR_LEN
#define DG_STR_LEN 50
#endif


class DG {
private:
public:
    DG();
    ~DG();

    // 初始化, 获取数据结构
    static supermatrix DG_init(const Instance *the_instance_p, const vector<Cell> &the_cells, vector<double> &init_args);
    // 获取时间步长dt, 需要Fun
    static double DG_get_dt( const Instance *the_instance_p, const supermatrix &the_datas, const vector<Cell> &the_cells, vector<double> &dt_args);
    // 更新, 这里cells不能是const，需要Fun
    static supermatrix DG_update(const Instance *the_instance_p, const supermatrix &the_datas, vector<Cell> &the_cells, vector<double> &update_args);
    // 误差计算
    static vector<double> DG_error(const Instance *the_instance_p, const supermatrix &the_datas, const vector<Cell> &the_cells, vector<double> &error_args);
    // 输出详细数据(作图用)
    static void DG_output(const Instance *the_instance_p, const supermatrix &the_datas, const vector<Cell> &the_cells, vector<double> &output_args, const char output_strs[][DG_STR_LEN]);
};
