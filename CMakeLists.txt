cmake_minimum_required(VERSION 3.10)

project(camin)

set(CAMIN_C_FILES src/input/sdli.c)

add_library(camin ${CAMIN_C_FILES})

