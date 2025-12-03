cmake_minimum_required(VERSION 3.10)

project(glad LANGUAGES C)

add_library(glad STATIC
    src/glad.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Optional: set C standard
set_target_properties(glad PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)
