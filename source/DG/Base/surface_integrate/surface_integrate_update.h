#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "DG/Cell/Cell.h"
#include "DG/Instance/Instance.h"

#include "DG/Base/basefunction/basefunction.h"
#include "DG/Base/basefunction/values_table.h"

#include "DG/Fun/Fun.h"

// update 部分

double SurfaceIntegrate_update_main(index gauss_k, const matrix &the_data, Cell &the_cell, index value_index,
                                    const vector<double> &u);

double SurfaceIntegrate_update_Fu(index gauss_k, const Fun *fun_p, const matrix &the_data, Cell &the_cell, index value_index,
                                  const vector<double> &u);
