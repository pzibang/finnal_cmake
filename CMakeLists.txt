cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# 设置工程名字
project(PROJECT)

#设置变量TARGETS，其内容为"test"
set(TARGETS "test")

set(libadd_path "libadd")
set(libsub_path "libsub")
include_directories(${PROJECT_SOURCE_DIR}/${libadd_path}/include)
include_directories(${PROJECT_SOURCE_DIR}/${libsub_path}/include)
include_directories(${PROJECT_SOURCE_DIR})

#file(GLOB src_file "${PROJECT_SOURCE_DIR}/${src_path}/*.*")
aux_source_directory(${PROJECT_SOURCE_DIR}/${libadd_path} ADD_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/${libsub_path} SUB_SRC)
aux_source_directory(. MAIN_SRC)

#设置输出目录
set(OUTDIRS "build") # Debug:调试 Release:不调试
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/${OUTDIRS}/lib/")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/${OUTDIRS}/bin/")


# 添加对gdb的支持
SET(CMAKE_BUILD_TYPE "Debug")
#判断编译器类型,如果是gcc编译器,则在编译选项中加入c++11支持
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -lpthread -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g -ggdb")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
endif(CMAKE_COMPILER_IS_GNUCXX)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

#生成可执行文件
add_executable(${TARGETS} ${ADD_SRC} ${SUB_SRC} ${MAIN_SRC})



#提示错误：undefined reference to `pthread_create' collect2: error: ld returned 1 exit status
#解决：需要添加 pthread 库
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
#target_link_libraries(${TARGETS} PUBLIC Threads::Threads)
