# set(LIB_NAME "myadd")
string(REGEX REPLACE ".*/(.*)" "\\1" LIB_NAME ${CMAKE_CURRENT_SOURCE_DIR})
#设置源文件路径
set(LIB_SRC_DIR
  "."
)
#添加源文件
foreach(FOREACH_SRC_DIR ${LIB_SRC_DIR})
    aux_source_directory(${FOREACH_SRC_DIR} TMP_SRCS)
endforeach()

#设置头文件路径
set(LIB_INC_DIR
  "include/"
)

#添加头文件路径
include_directories(${LIB_INC_DIR})


add_library(${LIB_NAME} ${LIB_TYPE} ${TMP_SRCS}) # SHARED STATIC
target_link_libraries(${LIB_NAME} ${CMAKE_CXX_FLAGS})