cmake_minimum_required(VERSION 3.10)

project(SampleProject)

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})

# Add the sample library
add_library(sample sample.cpp)

# Add the test executable
add_executable(sample_test test/sample_test.cpp)
target_link_libraries(sample_test ${GTEST_LIBRARIES} pthread sample)
