cmake_minimum_required(VERSION 2.6)
project(bplustree)

set(src bplustree.c bplustree.h
    main.c)

add_executable(bplustree ${src})
