cmake_minimum_required(VERSION 3.0.0)
MESSAGE("This is isntall dir")
project(Server8888)#dir_name 
include_directories(./include)
add_definitions("-Wall -g")
aux_source_directory(./src DIR_SRC)
add_executable(server ${DIR_SRC})
target_link_libraries(server /usr/lib/libjsoncpp.a)
target_link_libraries(server -levent)
