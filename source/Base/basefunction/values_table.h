#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"
#include "MyGauss/Gauss.h"

#include "basefunction.h"
#include "Cell/Cell.h"
#include "Instance/Instance.h"
#include "Base/translate/translate.h"

// 这一层产生的点值列表，传递给上一层的具体情况的面积分和线积分计算
// 关于三角形和矩形单元的区分，在这一层解决
// 并且上一层将只是进行线性组合，这一层需要解决cell的尺度变换，记录到值列表中
matrix jacobi(const Cell &the_cell);
matrix inv_jacobi(const Cell &the_cell);
double jacobi_det_fabs(const Cell&the_cell);

// 这里还产生面积分的权重和局部坐标
vector<double> get_cell_gaussweights(index gauss_k, index cellkind);

matrix get_cell_gausspoints(index gauss_k, index cellkind);

// 这里还产生线积分的权重和局部坐标
vector<double> get_side_gaussweights(index gauss_k, index cellkind);

matrix get_side_gausspoints(index gauss_k, index cellkind, int side_loc);








// 产生cell的单元内部的高斯点的值的table，用于后续的面积分
// 基于指定的基函数的线性组合
vector<double> get_cell_values_table(index gauss_k, const Cell &the_cell, const vector<base_fun_type_2d> &base_funs, const vector<double> &u);

// 基于instance的初值函数
vector<double> get_cell_values_table_init(index gauss_k, const Cell &the_cell, const Instance *the_instance_p,index out_index);

// 基于instance的精确值函数
vector<double> get_cell_values_table_end(index gauss_k, const Cell &the_cell, const Instance *the_instance_p,index out_index, double time_now);



// 产生cell的指定第几条边的高斯点的值的table，用于后续的线积分

// 基于指定的基函数的线性组合
vector<double> get_side_values_table(index gauss_k, const Cell &the_cell, int side_loc, const vector<base_fun_type_2d> &base_funs, const vector<double> &u);

// 基于instance的初值函数
vector<double> get_side_values_table_init(index gauss_k, const Cell &the_cell, int side_loc, const Instance *the_instance_p,index out_index);

// 基于instance的精确值函数
vector<double> get_side_values_table_end(index gauss_k, const Cell &the_cell, int side_loc, const Instance *the_instance_p,index out_index, double time_now);
