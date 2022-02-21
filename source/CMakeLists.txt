# 加入当前目录，为了后续可以找到source下的头文件路径
list(APPEND MY_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})

# 核心
# extra是附加的可选部分，也封装成一个静态库
# add_subdirectory(extra)
# DG是最主要的部分，封装为一个静态库
add_subdirectory(DG)

add_subdirectory(model_Fun)

add_subdirectory(simple_Fun)

add_subdirectory(model_Instance)

add_subdirectory(simple_Instance)

add_subdirectory(triangle_Instance)

# add_subdirectory(Eg_1d_smooth_triangle)
# 这里四个库目标都相互独立，不事先链接内部库或者外部库
# 但是它们都需要外部库的目录
# 子目录的CMakeLists都自带下载模块，不自带测试部分

# 测试部分
# 组成部分的分块测试
# add_subdirectory(partoftest)
# 整体的测试，基于算例
add_subdirectory(test)





