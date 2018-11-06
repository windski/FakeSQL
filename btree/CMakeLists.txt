cmake_minimum_required(VERSION 2.6)
project(bplustree)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

set(src bplustree.c bplustree.h
    main.c myque.c myque.h presistBtree.c presistBtree.h)
set(CMAKE_C_FLAGS -std=c99)
add_executable(bplustree ${src})
