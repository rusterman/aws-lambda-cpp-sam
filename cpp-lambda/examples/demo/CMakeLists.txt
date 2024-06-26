cmake_minimum_required(VERSION 3.9)

# Set the C++ standard from the environment variable
if(NOT DEFINED CPP_VERSION)
    set(CPP_VERSION 11)  # Default to C++11 if not set
endif()

set(CMAKE_CXX_STANDARD ${CPP_VERSION})

project(demo LANGUAGES CXX)
find_package(aws-lambda-runtime)
add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE AWS::aws-lambda-runtime)

# Dynamically set the compile features based on CPP_VERSION
string(CONCAT CXX_STD_FEATURE "cxx_std_" ${CPP_VERSION})
target_compile_features(${PROJECT_NAME} PRIVATE ${CXX_STD_FEATURE})

target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-Wextra")

# Important is, that if you are building in an amazon linux environment
# you have to include aws_lambda_package_target(demo NO_LIBC) to your CMakeLists.txt.
# This is in order to not include the C runtime as a dependency.
# this line creates a target that packages your binary and zips it up
aws_lambda_package_target(${PROJECT_NAME} NO_LIBC)