#pragma once
#include "MyHead.h"

// 网格与数据分离
// 数据用vector合并存储，网格只负责存储固定点边的信息，两者通过相同序号对应

class Cell {
private:
    char _flag_for_location = 0; //标记位，记录关于结点位置的类型,是否是边界,相应边界条件等
    char _flag_for_visit = 0;    //标记位，记录一次遍历中的访问状态，由于好几个边，可能要按比特使用
    char _cellKind = 0;          //单元类型
    char _neighborNum = 0;       //拥有的邻居数目，也就是边的数量

    int _sides[4];      //单元的邻边编号数组，单元编号-1代表不存在
    int _neighbors[4];  //邻居单元的编号数组,与上述邻边对应
    double _nodes_x[4]; //单元的顶点位置x分量
    double _nodes_y[4]; //单元的顶点位置y分量

    // 三角单元 相邻单元-邻边-顶点 直接对应
    // 作为三组，逆时针排序

    // 矩形单元 相邻单元-邻边 直接对应 一共四组
    // 逆时针排序，下->右->上->左
    // 四个顶点 逆时针排序，左下->右下->右上->左上
public:
    Cell(/* args */);
    ~Cell();

    char get_visit_flag(void);
    void set_visit_flag(char flag_for_visit);

    char get_location_flag(void) const;
    void set_location_flag_init(char flag_for_location);

    char get_cellKind(void) const;
    void set_cellKind_init(char cellKind);

    char get_neighborNum(void) const;

    // 添加单元编号，单元公共边编号，单元相对的顶点的x与y坐标
    void set_neighbor_init(int cell_i, int side_i, double node_x, double node_y);

    // 获取所有顶点的位置(x,y)的列表
    matrix get_nodes_list() const;
    // 获取所有邻边索引的列表
    vector<int> get_sides_list() const;
    // 获取所有邻居索引的列表
    vector<int> get_neighbors_list() const;

    // 获取所有边的单位外法向量
    matrix get_outside_vector() const;
    // 获取所有边的长度
    vector<double> get_sides_length() const;

    // 友元函数，直接输出cell的所有信息
    friend void read_cell(Cell the_cell);

    // 友元函数，周期性修正
    friend void period_modify_rectangle_cells(vector<Cell> &the_cells, int x_num, int y_num);
};
