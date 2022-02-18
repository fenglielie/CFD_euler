#include "Cell.h"

Cell::Cell(/* args */)
{
}

Cell::~Cell()
{
}

// 4个私有属性的访问与修改

// 获取访问标记
char Cell::get_visit_flag(void)
{
    return _flag_for_visit;
}
// 设置访问标记
void Cell::set_visit_flag(char flag_for_visit)
{
    _flag_for_visit = flag_for_visit;
    return;
}

// 获取位置标记
char Cell::get_location_flag(void) const
{
    return _flag_for_location;
}
// 设置位置标记，这只在网格初始化时候进行
void Cell::set_location_flag_init(char flag_for_location)
{
    _flag_for_location = flag_for_location;
    return;
}

// 获取单元类型
char Cell::get_cellKind(void) const
{
    return _cellKind;
}
// 设置单元类型，这只在网格初始化时候进行
void Cell::set_cellKind_init(char cellKind)
{
    _cellKind = cellKind;
    return;
}

// 获取邻居数目
char Cell::get_neighborNum(void) const
{
    return _neighborNum;
}

// 设置邻居，这只在网格初始化时候进行
// 同时初始化邻居索引和顶点位置
void Cell::set_neighbor_init(int cell_i, int side_i, double node_x, double node_y)
{
    if (_neighborNum >= 4) {
        fprintf(stderr, "Cell::set_neighbor: 邻居数目不允许超过4个,不能再设置邻居结点\n");
        return;
    }

    _neighbors[_neighborNum] = cell_i;
    _sides[_neighborNum] = side_i;
    _nodes_x[_neighborNum] = node_x;
    _nodes_y[_neighborNum] = node_y;

    ++_neighborNum; //在init阶段作为索引，在其他阶段作为邻居数目常量
    return;
}

matrix Cell::get_nodes_list() const
{
    vector<double> point(2, 0);
    matrix result(_neighborNum, point);

    for (int i = 0; i < _neighborNum; i++) {
        result[i][0] = _nodes_x[i];
        result[i][1] = _nodes_y[i];
    }

    return result;
}

vector<int> Cell::get_sides_list() const
{
    vector<int> sides(_neighborNum);
    for (int i = 0; i < _neighborNum; i++) {
        sides[i] = _sides[i];
    }
    return sides;
}

vector<int> Cell::get_neighbors_list() const
{
    vector<int> neighbors(_neighborNum);
    for (int i = 0; i < _neighborNum; i++) {
        neighbors[i] = _neighbors[i];
    }
    return neighbors;
}


void Cell::set_outsides_vector()
{
    matrix nodes = get_nodes_list();
    index len = nodes.size();
    matrix outs(nodes);
    double temp = 0;
    double u = 0, v = 0;
    for (index i = 0; i < len; i++) {
        // 差值
        u = nodes[(i + 1) % len][0] - nodes[i][0];
        v = nodes[(i + 1) % len][1] - nodes[i][1];
        // 旋转(顺时针旋转90度)
        // (a+bi)*(-i)=b-ai
        // (x,y)->(y,-x)
        temp = u;
        u = v;
        v = -temp;
        // 单位化
        temp = sqrt(u * u + v * v);
        u = u / temp;
        v = v / temp;

        outs[i][0] = u;
        outs[i][1] = v;
    }

    if (_cellKind == 3) {
        // 顶点有错位，需要修正和邻居/邻边的序号一致
        matrix outs_old = outs;
        outs[0] = outs_old[1];
        outs[1] = outs_old[2];
        outs[2] = outs_old[0];
    }
    _outsides_vector = outs;

    return;
}

matrix Cell::get_outside_vector() const
{
    return _outsides_vector;
}

void Cell::set_sides_length()
{
    matrix nodes = get_nodes_list();
    index len = nodes.size();
    vector<double> lengths(len, 0);

    double dx = 0, dy = 0;
    for (index i = 0; i < len; i++) {
        dx = nodes[(i + 1) % len][0] - nodes[i][0];
        dy = nodes[(i + 1) % len][1] - nodes[i][1];
        lengths[i] = sqrt(dx * dx + dy * dy);
    }

    if (_cellKind == 3) {
        // 顶点有错位，需要修正和邻居/邻边的序号一致
        vector<double> lengths_old = lengths;
        lengths[0] = lengths_old[1];
        lengths[1] = lengths_old[2];
        lengths[2] = lengths_old[0];
    }

    _sides_length = lengths;
    return;
}

vector<double> Cell::get_sides_length() const
{
    return _sides_length;
}

void Cell::set_A_matrix(matrix &A)
{
    _A_matrix = A;
}
matrix Cell::get_A_matrix() const
{
    return _A_matrix;
}


void read_cell(Cell the_cell)
{
    printf("cellKind = %d\n", the_cell._cellKind);
    printf("neighborNum = %d\n", the_cell._neighborNum);
    printf("location flag = %d, visit flag = %d\n", the_cell._flag_for_location, the_cell._flag_for_visit);

    for (int i = 0; i < 4; i++) {
        printf("[%d] side=%d, neighbor=%d,\t", i, the_cell._sides[i], the_cell._neighbors[i]);
        printf("node=(%f,%f)\n", the_cell._nodes_x[i], the_cell._nodes_y[i]);
    }
}