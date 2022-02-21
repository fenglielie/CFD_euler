#pragma once
#include "MyHead.h"
#include "Cell/Cell.h"
#include "Fun/Fun.h"


// 基类，具体的算例是它一个继承
class Instance {
private:
    int _output_len = 0;

public:
    const Fun *_fun_p = NULL;

public:
    Instance();
    ~Instance();

    int get_output_len() const;
    void set_output_len(int len);

    void with_Fun(const Fun *fun_p);

    // 算例的可选配置
    virtual void config_instance(vector<double> &config_args);

    // 纯虚函数 创建网格
    virtual vector<Cell> create_cells();
    // 虚函数 获取初值
    virtual vector<double> value_init(double x, double y) const;
    // 虚函数 获取精确值
    virtual vector<double> value_end(double x, double y, double end_time) const;
};
