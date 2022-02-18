# 加入当前目录，为了后续可以找到source下的头文件路径
list(APPEND MY_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(test_model_Eg)
add_subdirectory(test_simple_Eg)
