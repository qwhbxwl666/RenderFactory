#需要的最低cmake程序版本
cmake_minimum_required(VERSION 3.16)

#本工程的名字
project(RenderFactory)

#本工程支持的版本
set(CMAKE_CXX_STANDARD 17)

# 往项目中加入一个全局的预编译宏
#add_definitions (-DDEBUG)

# 设置头文件和库文件搜索路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

#将funcs文件夹纳入到编译系统 文件夹！
#add_subdirectory(funcs)

#把需要拷贝的资源路径都放到ASSETS里
file(GLOB ASSETS "./assets")

#把ASSETS指代的目录集合的内容，都拷贝到可执行文件目录下
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

#搜索所有的cpp，加入SRCS变量中
#aux_source_directory(. SRCS)

#本工程主程序所有cpp文件编译链接，生成exe
add_executable(GraphicsRenderer "main.cpp" "glad.c")

#将 glfw3.lib 链接到目标 GraphicsRenderer 确保 CMake 能找到 glfw3.lib，通常需要先设置 link_directories() 或 find_package() 
target_link_libraries(GraphicsRenderer glfw3.lib)