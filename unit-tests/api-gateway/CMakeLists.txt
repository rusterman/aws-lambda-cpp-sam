cmake_minimum_required(VERSION 3.14)
project(LambdaFunctionTest)

set(CMAKE_CXX_STANDARD 14)

# Set paths for GoogleTest and CPR
set(GTEST_ROOT "/usr/src/googletest")
set(CPR_ROOT "/usr/src/cpr")

# Find GoogleTest package
add_subdirectory(${GTEST_ROOT} googletest)
include_directories(${GTEST_ROOT}/googletest/include)

# Find CPR package
add_subdirectory(${CPR_ROOT} cpr)
include_directories(${CPR_ROOT}/include)

# Include nlohmann/json header directory
include_directories(/usr/local/include)

# Enable testing
enable_testing()

# Add executable and link libraries
add_executable(test_lambda test_lambda.cpp)
target_link_libraries(test_lambda gtest_main cpr::cpr)

# Discover tests
include(GoogleTest)
gtest_discover_tests(test_lambda)
