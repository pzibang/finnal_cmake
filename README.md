# 实现过程
## 源文件和头文件在同一路径下

#将路径下的所有源文件放入DIR_SRCS变量中
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

# 生成名为Demo的二进制文件
ADD_EXECUTABLE(Demo ${DIR_SRCS})

## 多个源文件和头文件
实现思路：将所有源文件和头文件的路径都包含，主要使用了cmake的include_directories（添加头文件路径）和aux_source_directory（添加源文件到变量）
#test是包含头文件和源文件的文件夹，其中test文件夹下，include文件夹是包含头文件的
set(SUBDIRS "test")
foreach(dir ${SUBDIRS})
	aux_source_directory(${PROJECT_SOURCE_DIR}/${dir} ALL_SRC)
	include_directories(${PROJECT_SOURCE_DIR}/${dir}/include)
endforeach()

## 通用cmake
使用通用的cmake的时候，其文件构成必须是以下形式：
root
    |---model
        |---include
            |---xxx.h
            |---xxxx.h
        |---xxx.cpp
        |---xxxx.cpp
        |---xxxxx.cpp
    |---main.cpp
    |---xxx.h
根目录下不作要求，但是模块中的文件包含是固定的，因为在cmake中添加了检索PROJECT_SOURCE_DIR下的源文件，并将PROJECT_SOURCE_DIR作为头文件路径包含，
所以可以写成上面的形式。

  
实现如下：
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#设置工程名字
project(PROJECT)

set(TARGETS "practice")

set(SUBDIRS "apue.3e")
foreach(dir ${SUBDIRS})
	aux_source_directory(${PROJECT_SOURCE_DIR}/${dir} ALL_SRC)
	include_directories(${PROJECT_SOURCE_DIR}/${dir}/include)
endforeach()
include_directories(${PROJECT_SOURCE_DIR})
aux_source_directory(. MAIN_SRC)


foreach(tmp ${ALL_SRC})
	message(STATUS "${tmp}")
endforeach()


#设置输出目录
set(OUTDIRS "build") # Debug:调试 Release:不调试
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/${OUTDIRS}/lib/")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/${OUTDIRS}/bin/")


#添加对gdb的支持
SET(CMAKE_BUILD_TYPE "Debug")
#判断编译器类型,如果是gcc编译器,则在编译选项中加入c++11支持
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -lpthread -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g -ggdb")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
endif(CMAKE_COMPILER_IS_GNUCXX)

#生成可执行文件
#add_executable(${TARGETS} ${ADD_SRC} ${SUB_SRC} ${MAIN_SRC})
add_executable(${TARGETS} ${ALL_SRC} ${MAIN_SRC})

#提示错误：undefined reference to `pthread_create' collect2: error: ld returned 1 exit status
#解决：需要添加 pthread 库
find_package(Threads)
target_link_libraries(${TARGETS} ${CMAKE_THREAD_LIBS_INIT})

