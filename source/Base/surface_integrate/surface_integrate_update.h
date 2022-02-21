#pragma once
#include "MyHead.h"
#include "MyMatrixBase/MyMatrixBase.h"

#include "Cell/Cell.h"
#include "Instance/Instance.h"

#include "Base/basefunction/basefunction.h"
#include "Base/basefunction/values_table.h"

#include "Fun/Fun.h"

// update 部分

double SurfaceIntegrate_update_main(index gauss_k, const matrix &the_data, Cell &the_cell, index value_index,
                                    const vector<double> &u);

double SurfaceIntegrate_update_Fu(index gauss_k, const Fun *fun_p, const matrix &the_data, Cell &the_cell, index value_index,
                                  const vector<double> &u);
