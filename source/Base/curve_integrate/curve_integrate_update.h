#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "Cell/Cell.h"
#include "Instance/Instance.h"

#include "Base/basefunction/basefunction.h"
#include "Base/basefunction/values_table.h"

#include "Fun/Fun.h"

double CurveIntegrate_update_edge(index gauss_k,const Fun * fun_p,const supermatrix &the_datas, vector<Cell> &the_cells,
                                  index cell_index, index value_index, const vector<double> &u);