cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 11)
project(lambda-test-fun LANGUAGES CXX)
find_package(aws-lambda-runtime)
add_executable(${PROJECT_NAME} "lambda_function.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE AWS::aws-lambda-runtime)
target_compile_features(${PROJECT_NAME} PRIVATE "cxx_std_11")
target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-Wextra")

# Important is, that if you are building in an amazon linux environment
# you have to include aws_lambda_package_target(demo NO_LIBC) to your CMakeLists.txt.
# This is in order to not include the C runtime as a dependency.
# this line creates a target that packages your binary and zips it up
aws_lambda_package_target(${PROJECT_NAME})