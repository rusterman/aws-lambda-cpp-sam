cmake_minimum_required(VERSION 3.17)

# Set the C++ standard from the environment variable
if(NOT DEFINED CPP_VERSION)
    set(CPP_VERSION 11)  # Default to C++11 if not set
endif()

set(CMAKE_CXX_STANDARD ${CPP_VERSION})

project(dynamodb LANGUAGES CXX)

find_package(ZLIB REQUIRED)
find_package(aws-lambda-runtime)
find_package(AWSSDK COMPONENTS dynamodb)

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC AWS::aws-lambda-runtime ${AWSSDK_LINK_LIBRARIES} ZLIB::ZLIB)

target_compile_options(${PROJECT_NAME} PRIVATE
        "-fno-exceptions"
        "-fno-rtti"
        "-Wall"
        "-Wextra"
        "-Werror"
        "-Wconversion"
        "-Wno-sign-conversion")

# Dynamically set the compile features based on CPP_VERSION
string(CONCAT CXX_STD_FEATURE "cxx_std_" ${CPP_VERSION})
target_compile_features(${PROJECT_NAME} PRIVATE ${CXX_STD_FEATURE})

# Important is, that if you are building in an amazon linux environment
# you have to include aws_lambda_package_target(hello NO_LIBC) to your CMakeLists.txt.
# This is in order to not include the C runtime as a dependency.
# this line creates a target that packages your binary and zips it up
aws_lambda_package_target(${PROJECT_NAME} NO_LIBC)

