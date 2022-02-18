#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "DG/Cell/Cell.h"
#include "DG/Instance/Instance.h"

#include "DG/Base/basefunction/basefunction.h"
#include "DG/Base/basefunction/values_table.h"

#include "DG/Fun/Fun.h"

double CurveIntegrate_update_edge(index gauss_k,const Fun * fun_p,const supermatrix &the_datas, vector<Cell> &the_cells,
                                  index cell_index, index value_index, const vector<double> &u);