#include "output.h"


void output(const Instance *the_instance_p, const supermatrix &the_datas, const vector<Cell> &the_cells,
            vector<double> &output_args, const char output_strs[][DG_STR_LEN])
{
    // output_args参数解析
    // 第一个参数是time_now

    // 在每个cell的中心点获取所有分量的值，
    // 然后汇总，经过守恒型到非守恒型的转换
    // 最后按照分量输出到各个文件中，
    // output_strs是文件


}
