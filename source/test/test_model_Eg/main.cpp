#include "MyHead.h"
#include "DG/DG.h"
#include "model_Fun/model_Fun.h"
#include "model_Instance/model_Instance.h"

// 具体算例是模板算例类的继承，算例信息存储在其中
// 数据存储在suprmatrix
// 网格结构存储在vector<Cell>中

#define THE_FUN model_Fun
#define THE_INSTANCE model_Instance

int main(int argc, char *argv[])
{
    printf("this is model Eg\n");

    THE_INSTANCE my_instance = THE_INSTANCE(); // 根据算例的类创造这个算例
    Instance *my_instance_p = &my_instance;

    // int x_num = atoi(argv[1]);
    // int y_num = atoi(argv[2]);
    int x_num = 16;
    int y_num = 16;

    printf("x_num=%d, y_num=%d\n", x_num, y_num);

    index k = 2;
    index gauss_k = 3;

    double time_now = 0;
    double time_end = 1.0;
    bool exit_flag = false;

    vector<double> config_args(2);
    config_args[0] = x_num;
    config_args[1] = y_num;

    my_instance.config_instance(config_args); // 对算例进行相关配置

    vector<Cell> my_cells = my_instance.create_cells(); // 创建算例附带的网格

    THE_FUN my_fun = THE_FUN(); //创造方程对象

    my_instance_p->with_Fun(&my_fun); //将算例与方程对象绑定

    // 一些需要的数值参数和字符串(文件名)参数
    // 这些参数可以及时修改，使用引用调用也会返回每一步的相关信息
    vector<double> init_args = {(double)k, (double)gauss_k};
    vector<double> dt_args = {0.3, (double)k};
    vector<double> update_args = {(double)k, 0, (double)gauss_k}; //第二个是dt
    vector<double> error_args = {0, (double)gauss_k, 0};          // 2->L2 end_time=0
    vector<double> output_args;
    const char output_strs[3][DG_STR_LEN] = {"file1.txt", "file2.txt", "file3.txt"};

    supermatrix my_datas = DG::DG_init(my_instance_p, my_cells, init_args);
    readMatrix(my_datas[0]);

    error_args[2] = 0;
    vector<double> init_error = DG::DG_error(my_instance_p, my_datas, my_cells, error_args);
    printf("init error\n");
    readVector(init_error);
    printf("init error = %.12f\n", init_error[0]);

    vector<double> middle_error;
    double dt_now = DG::DG_get_dt(my_instance_p, my_datas, my_cells, dt_args);
    printf("dt_now = %f\n", dt_now);
    /*
        update_args[1] = dt_now;
        my_datas = DG::DG_update(my_instance_p, my_datas, my_cells, update_args);

        error_args[2] = 0 + dt_now;
        middle_error = DG::DG_error(my_instance_p, my_datas, my_cells, error_args);

        printf("one step error\n");
        readVector(middle_error);
        printf("\n");

        readMatrix(my_datas[0]);

        return 0;
    */
    index i;
    for (i = 0; i < ITERATION_MAX && (exit_flag == false); ++i) {

        dt_now = DG::DG_get_dt(my_instance_p, my_datas, my_cells, dt_args);

        if (time_now < time_end && time_now + dt_now >= time_end) {
            dt_now = time_end - time_now;
            exit_flag = true;
        }
        // printf("i=%d,time_now=%f,dt_now=%f\n", i, time_now, dt_now);
        //  这里先设置update_args
        update_args[1] = dt_now;

        my_datas = DG::DG_update(my_instance_p, my_datas, my_cells, update_args);

        // 这里可以进行limiter

        // 这里可以进行check

        time_now = time_now + dt_now;
        /*
                error_args[2] = time_now;
                middle_error = DG::DG_error(my_instance_p, my_datas, my_cells, error_args);


                printf("[%d]middle error\n", i);
                readVector(middle_error);
                printf("\n");
                */
    }

    // 这里先设置error_args
    error_args[2] = time_end;
    vector<double> end_error = DG::DG_error(my_instance_p, my_datas, my_cells, error_args);
    printf("[%d]end error\n", i);
    readVector(end_error);
    /*
        for (index i = 0; i < len; i++) {
            printf("[%d]\n", i);
            readMatrix(my_datas[i]);
            printf("\n");
        }
    */
    // 这里先设置output_args以及output_strs

    DG::DG_output(my_instance_p, my_datas, my_cells, output_args, output_strs);


    printf("Result: nothing but OK\n");
    return 0;
}