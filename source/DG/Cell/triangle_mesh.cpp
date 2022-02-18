#include "triangle_mesh.h"

matrix read_matrix_from_file(const char *str, index len)
{
    ifstream rfile;
    rfile.open(str, ios::in);
    index num = 0;
    rfile >> num; //读取总行数
    // len是每一行获取数据
    matrix u = newMatrix(num, len);

    for (index i = 0; i < num; i++) {
        for (index j = 0; j < len; j++) {
            rfile >> u[i][j];
        }
    }

    rfile.close();
    return u;
}


vector<Cell> create_triangle_cell_from_file(const char *nodefile_name, const char *elementfile_name, const char *sidefile_name)
{
    // 从三个文件创建cell组成的矩阵
    matrix mar_node = read_matrix_from_file(nodefile_name, 4);
    matrix mar_element = read_matrix_from_file(elementfile_name, 13);
    matrix mar_side = read_matrix_from_file(sidefile_name, 6);

    // 记录cell的个数
    int node_num = (int)mar_element.size();
    // 创建cell的vector，最终返回
    vector<Cell> cells(node_num);
    int celltype = 3; // 三角形单元

    // 基准位置，去获取结点编号，单元编号，邻边编号
    int node_index_base = 1;
    int element_index_base = node_index_base + celltype;
    int side_index_base = element_index_base + celltype;

    int node_index, element_index, side_index;
    int node, element, side;
    double node_x = 0;
    double node_y = 0;

    for (int i = 0; i < node_num; ++i) {
        // 标记初始化
        cells[i].set_cellKind_init(celltype); // 三角形单元类型
        cells[i].set_location_flag_init(0);   // 后续可选的标记在边界的单元
        cells[i].set_visit_flag(0);

        // 索引重置
        node_index = node_index_base;
        element_index = element_index_base;
        side_index = side_index_base;

        for (int j = 0; j < celltype; ++j) {
            node = (int)mar_element[i][node_index]; //获取结点编号,可能是-1
            if (node >= 0) {
                node_x = mar_node[node][0];
                node_y = mar_node[node][1]; // 获取结点的具体坐标位置
            }
            else {
                node_x = node_y = 0;
            }

            element = (int)mar_element[i][element_index]; // 获取单元的编号,注意，这里可能记作-1，也就是边界
            side = (int)mar_element[i][side_index];       // 获取边的编号

            cells[i].set_neighbor_init(element, side, node_x, node_y); // 初始化邻居，一个点一个边一个单元一起

            // 索引后移
            ++node_index;
            ++element_index;
            ++side_index;
        }

        cells[i].set_outsides_vector();
        cells[i].set_sides_length();
    }

    return cells;
}
