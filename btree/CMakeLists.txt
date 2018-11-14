cmake_minimum_required(VERSION 2.6)
project(bplustree)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g -rdynamic -pthread")

find_package(Threads)

set(src main.c
        bplustree.c bplustree.h
        myque.c myque.h
        presistBtree.c presistBtree.h
        restorefromfile.h resotrefromfile.c)

add_executable(bplustree ${src})

target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
