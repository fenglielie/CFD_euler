#---------------------------------------------#
# head part for project, change by yourself:
# MY_PROJECT: the project now
set(MY_PROJECT CFD_euler)
# MY_VERSION: the project version now
set(MY_VERSION 0.1)
# MY_EXTRA_ROOT: the dir to find extra libs
set(MY_EXTRA_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../Base)
# the default subdir is source, you should add subdir at the end!
#---------------------------------------------#


# for gprof
if(MY_GPROF)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
endif()
# run a.exe first
# then there will be a gmout.out (recovered automaticlly)
# gprof a.exe gmout.out > a.txt
# then there will be an a.txt

#---------------------------------------------#
# the CMakeLists.txt module for project begin:
# hash=aqwfdzgvfdsbgfds 2022-02-09
#---------------------------------------------#

# cmake version required
cmake_minimum_required(VERSION 3.15)
# set project with version
project(${MY_PROJECT} VERSION ${MY_VERSION})

# my dir for config
set(MY_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(MY_LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(MY_BIN ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# cmake dir for build
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# cmake dir for install
set(CMAKE_INSTALL_PREFIX ${MY_EXTRA_ROOT})

# cmake dir for find_package
set(CMAKE_PREFIX_PATH ${MY_EXTRA_ROOT}/lib/cmake/)

# all head files -> COMMON_HEAD
file(GLOB COMMON_HEAD ${MY_INCLUDE}/*.h)

#---------------------------------------------#
# the CMakeLists.txt module for project end.
# hash=aqwfdzgvfdsbgfds 2022-02-09
#---------------------------------------------#







#---------------------------------------------#
# end part for project, change by yourself:
# configure_file(config/Config.h.in Config.h)
list(APPEND MY_INCLUDE ${CMAKE_BINARY_DIR})

# always addend current dir to MY_INCLUDE before add_subdir
list(APPEND MY_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})
# add local subdir
add_subdirectory(source)
#---------------------------------------------#


enable_testing()

# begin test for test_1d_smooth

# 无参数需要返回提示信息，包括方程信息，算例信息，但是不进行运算
add_test(NAME test_model_Eg_is_Run COMMAND test_model_Eg)
# 有参数，可以设置参数进行运算，计算判断最后一行输出结果是否ok
add_test(NAME test_model_Eg_is_OK COMMAND test_model_Eg -a)
set_tests_properties(test_model_Eg_is_OK PROPERTIES PASS_REGULAR_EXPRESSION "Result:.*OK")
# 注意这里结果的匹配.*才代表通配符


# add_test(NAME part_test_rect_mesh_is_What COMMAND part_test_rect_mesh)
# add_test(NAME part_test_tri_mesh_is_What COMMAND part_test_tri_mesh)
# add_test(NAME part_test_1d_smooth_mesh_is_What COMMAND part_test_1d_smooth_mesh)
