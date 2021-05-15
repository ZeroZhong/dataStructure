cmake_minimum_required(VERSION 3.0.0)
project(TEST_VECTOR)
aux_source_directory(. ALL_SRCS)
# add_subdirectory(vector)
include_directories(${PROJECT_SOURCE_DIR}/vector)
add_executable(TEST_VECTOR ${ALL_SRCS})
# target_link_libraries(TEST_VECTOR vector_c++)


