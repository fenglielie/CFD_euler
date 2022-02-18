list(APPEND MY_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})
set(MY_TARGET_NAME model_Fun)
add_library(${MY_TARGET_NAME} STATIC)
# target_compile_definitions(${MY_TARGET_NAME} PRIVATE LOG)

# MY_EXTRA_INCLUDE: whether include extra libs
set(MY_EXTRA_INCLUDE TRUE)
# MY_LOCAL_NEED: whether need local libs
set(MY_LOCAL_NEED FALSE)
# MY_EXTRA_NEED: whether need extra libs
set(MY_EXTRA_NEED FALSE)

# prepare for install
set(MY_TARGET_TO_INSTALL ${MY_TARGET_NAME})
set(MY_PROJECT_TO_INSTALL ${MY_PROJECT})
set(MY_VERSION_TO_INSTALL ${MY_VERSION})
#---------------------------------------------#








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







#---------------------------------------------#
# the CMakeLists.txt module for install begin:
# hash=vbfisbvfhkesbvhfs 2022-02-09
#---------------------------------------------#

# you need set "MY_PROJECT_TO_INSTALL" before
# you need set "MY_TARGET_TO_INSTALL" before
# you need set "MY_VERSION_TO_INSTALL" before

# module prepare
include(GNUInstallDirs)

# install target mainly
install(TARGETS ${MY_TARGET_TO_INSTALL}
        EXPORT ${MY_TARGET_TO_INSTALL}Targets
        LIBRARY DESTINATION lib/${MY_PROJECT_TO_INSTALL}
        ARCHIVE DESTINATION lib/${MY_PROJECT_TO_INSTALL}
        RUNTIME DESTINATION bin/${MY_PROJECT_TO_INSTALL}
        INCLUDES DESTINATION include/${MY_PROJECT_TO_INSTALL}
)

# install head files
install(FILES ${LOC_HEAD} ${COMMON_HEAD} DESTINATION include/${MY_PROJECT_TO_INSTALL})

# install target
install(EXPORT ${MY_TARGET_TO_INSTALL}Targets
        FILE ${MY_TARGET_TO_INSTALL}Config.cmake
        DESTINATION lib/cmake
)

# write down target version
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${MY_TARGET_TO_INSTALL}ConfigVersion.cmake
        VERSION ${MY_VERSION_TO_INSTALL}
        COMPATIBILITY AnyNewerVersion  # 表示该函数库向下兼容
)

# version to lib/cmake
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${MY_TARGET_TO_INSTALL}ConfigVersion.cmake"
        DESTINATION lib/cmake
)

#---------------------------------------------#
# the CMakeLists.txt module for install end.
# hash=vbfisbvfhkesbvhfs 2022-02-09
#---------------------------------------------#


