cmake_minimum_required(VERSION 3.27)
project(kilo_clone C)

set(CMAKE_C_STANDARD 11)

add_executable(kilo_clone main.c
        kilo.c)
