cmake_minimum_required (VERSION 3.2)

project(avrcpp)

add_library(
    avrcpp
    STATIC
    src/dummy.cxx
)

target_include_directories(
    avrcpp
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(
    avrcpp
    PUBLIC
    cxx_std_17
)

add_subdirectory(
    test/1
)
