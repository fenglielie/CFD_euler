//---------------------------------------------//
// MyHead.h begin:
// hash=bngxfnrdnrg 2022-02-09
//---------------------------------------------//

#ifndef MyHead_
#define MyHead_
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

#define OK 1
#define ERROR 0
#define MACHINE_PRECISION_18 1e-18
#define MACHINE_PRECISION_15 1e-15
#define MACHINE_TINY_8 1e-8
#define VIEW_SMALL_5 1e-5
#define MACHINE_LARGE 1e10

typedef unsigned index;
typedef double T;
typedef int Status;

typedef std::vector<index> vector_index;
typedef std::vector<int> vector_int;

typedef std::vector<std::vector<T>> matrix;
typedef std::vector<std::vector<std::vector<T>>> supermatrix;
typedef std::vector<std::vector<std::vector<std::vector<T>>>> supermatrix_4;
typedef std::vector<std::vector<std::vector<std::vector<std::vector<T>>>>> supermatrix_5;


#define ITERATION_MAX 0xfffffff

#endif //MyHead_

//---------------------------------------------//
// MyHead.h end.
// hash=bngxfnrdnrg 2022-02-09
//---------------------------------------------//