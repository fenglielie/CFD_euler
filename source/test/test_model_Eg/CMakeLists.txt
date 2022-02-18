list(APPEND MY_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})


# test_1d_smooth
set(MY_TARGET_NAME test_model_Eg)
add_executable(${MY_TARGET_NAME})

# target_compile_definitions(${MY_TARGET_NAME} PRIVATE LOG)

set(MY_EXTRA_INCLUDE TRUE)
set(MY_LOCAL_NEED TRUE)
set(MY_LOCAL_LIBS DG model_Fun model_Instance DG model_Fun model_Instance)

set(MY_EXTRA_NEED TRUE)
set(MY_EXTRA_LIBS mygauss mylinearsolve mar)
find_package(mar 1.0 REQUIRED)
find_package(mygauss 1.0 REQUIRED)
find_package(mylinearsolve 1.0 REQUIRED)





#---------------------------------------------#
# the CMakeLists.txt module for lib/exe begin:
# hash=esbgfdsbgfdxbvdxv 2022-02-09
#---------------------------------------------#

# you have add_lib/exe before
# here we check now
message(">> Here we check: ${MY_TARGET_NAME}")

if(${MY_EXTRA_INCLUDE})
    message(">> we need extra include now")
endif()
if(${MY_LOCAL_NEED})
    message(">> we need loc libs now: ${MY_LOCAL_LIBS}")
endif()
if(${MY_EXTRA_NEED})
    message(">> we need extra libs now: ${MY_EXTRA_LIBS}")
endif()


# all local source files -> LOC_SRCS
file(GLOB LOC_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# all local head files -> LOC_HEAD
file(GLOB LOC_HEAD ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


# add sources
target_sources(${MY_TARGET_NAME} PRIVATE ${LOC_SRCS})
# add include dirs
target_include_directories(${MY_TARGET_NAME} PRIVATE ${MY_INCLUDE})
# add extra include dirs
if(${MY_EXTRA_INCLUDE})
    target_include_directories(${MY_TARGET_NAME} PUBLIC ${MY_EXTRA_ROOT}/include)
endif()

# private link local libs
if(${MY_LOCAL_NEED})
    target_link_libraries(${MY_TARGET_NAME} PRIVATE ${MY_LOCAL_LIBS})
endif()
# public link extra libs
if(${MY_EXTRA_NEED})
    target_link_libraries(${MY_TARGET_NAME} PUBLIC ${MY_EXTRA_LIBS})
endif()


#---------------------------------------------#
# the CMakeLists.txt module for lib/exe end.
# hash=esbgfdsbgfdxbvdxv 2022-02-09
#---------------------------------------------#





