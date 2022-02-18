#include "values_table.h"

matrix jacobi(const Cell &the_cell)
{
    matrix result = newMatrix(2, 2);
    matrix points = the_cell.get_nodes_list();

    index cellkind = the_cell.get_cellKind();
    if (cellkind == 4) {
        double dx = points[1][0] - points[0][0];
        double dy = points[3][1] - points[0][1];
        result[0][0] = dx / 2;
        result[1][1] = dy / 2;
    }
    else if (cellkind == 3) {
        result[0][0] = points[1][0] - points[0][0];
        result[0][1] = points[2][0] - points[0][0];
        result[1][0] = points[1][1] - points[0][1];
        result[1][1] = points[2][1] - points[0][1];
    }
    else {
    }
    return result;
}

double jacobi_det_fabs(const Cell &the_cell)
{
    matrix mar = jacobi(the_cell);
    double det = mar[0][0] * mar[1][1] - mar[0][1] * mar[1][0];
    return fabs(det);
}

double coeff_for_dx(const Cell &the_cell)
{
    matrix mar = jacobi(the_cell);
    return 1.0 / mar[0][0];
}

double coeff_for_dy(const Cell &the_cell)
{
    matrix mar = jacobi(the_cell);
    return 1.0 / mar[1][1];
}

vector<double> get_cell_gaussweights(index gauss_k, index cellkind)
{
    vector<double> gaussweights;
    if (cellkind == 4) {
        gaussweights = setGaussWeights_2d(gauss_k);
    }
    else if (cellkind == 3) {
        //  TODO 三角形数值积分的权重
        // 权宜之计，三角形平移变换，并且自动补全另一半，成[-1,1]^2，把右上侧舍弃，也就是权重需要变成原来的一半
        gaussweights = 1.0 / 8 * setGaussWeights_2d(gauss_k);
    }
    else {
    }
    return gaussweights;
}

matrix get_cell_gausspoints(index gauss_k, index cellkind)
{
    matrix gausspoints;
    if (cellkind == 4) {
        gausspoints = setGaussPoints_2d(gauss_k);
    }
    else if (cellkind == 3) {
        //  TODO 三角形数值积分的点
        gausspoints = setGaussPoints_2d(gauss_k);

        index len = gausspoints.size();
        double temp = 0;
        for (index i = 0; i < len; i++) {
            if (gausspoints[i][0] + gausspoints[i][1] > 0) {
                // 首先把右上角部分关于x+y=0对称过来
                // (x,y)->(-y,-x)
                temp = gausspoints[i][0];
                gausspoints[i][0] = -gausspoints[i][1];
                gausspoints[i][1] = -temp;
            }
            // 然后把点变换到标准的三角形单元
            gausspoints[i][0] = 1 + 0.5 * (gausspoints[i][0] - 1);
            gausspoints[i][1] = 1 + 0.5 * (gausspoints[i][1] - 1);
        }
    }
    else {
    }
    return gausspoints;
}

vector<double> get_side_gaussweights(index gauss_k, index cellkind)
{
    vector<double> gaussweights;
    if (cellkind == 4) {
        gaussweights = setGaussWeights(gauss_k);
    }
    else if (cellkind == 3) {
        gaussweights = setGaussWeights(gauss_k);
    }
    else {
    }
    return gaussweights;
}

// 沿线获取高斯点，进行高斯点的线积分
matrix get_side_gausspoints(index gauss_k, index cellkind, int side_loc)
{
    vector<double> gausspoints_1d = setGaussPoints(gauss_k);
    matrix gausspoints = newMatrix(gauss_k, 2);
    if (cellkind == 4) {
        // 再根据是第几条边，进行转换
        for (index i = 0; i < gauss_k; i++) {
            switch (side_loc) {
            case 0:
                gausspoints[i][0] = gausspoints_1d[i];
                gausspoints[i][1] = -1;
                break;
            case 1:
                gausspoints[i][0] = 1;
                gausspoints[i][1] = gausspoints_1d[i];
                break;
            case 2:
                gausspoints[i][0] = -gausspoints_1d[i];
                gausspoints[i][1] = 1;
                break;
            case 3:
                gausspoints[i][0] = -1;
                gausspoints[i][1] = -gausspoints_1d[i];
                break;

            default:
                break;
            }
        }
    }
    else if (cellkind == 3) {
        // 针对三条边具体转换
        for (index i = 0; i < gauss_k; i++) {
            switch (side_loc) {
            case 0:
                gausspoints[i][0] = 0.5 + 0.5 * gausspoints_1d[i];
                gausspoints[i][1] = 0;
                break;
            case 1: //斜边上高斯点
                gausspoints[i][0] = 0.5 - 0.5 * gausspoints_1d[i];
                gausspoints[i][1] = 0.5 + 0.5 * gausspoints_1d[i];
                break;
            case 2:
                gausspoints[i][0] = 0;
                gausspoints[i][1] = 0.5 - 0.5 * gausspoints_1d[i];
                break;
            default:
                break;
            }
        }
    }
    else {
    }
    return gausspoints;
}