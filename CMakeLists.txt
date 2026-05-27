cmake_minimum_required(VERSION 3.20)
project (conch C)

set(CMAKE_C_STANDARD 23)

add_executable(conch
        main.c
        parser.c
)
