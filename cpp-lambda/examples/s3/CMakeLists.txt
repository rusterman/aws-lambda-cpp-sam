cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 14)

project(s3 LANGUAGES CXX)

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

find_package(aws-lambda-runtime REQUIRED)
find_package(AWSSDK COMPONENTS s3)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} PUBLIC
        AWS::aws-lambda-runtime
        ${AWSSDK_LINK_LIBRARIES}
        ${ZLIB_LIBRARIES})

# Important is, that if you are building in an amazon linux environment
# you have to include aws_lambda_package_target(s3 NO_LIBC) to your CMakeLists.txt.
# This is in order to not include the C runtime as a dependency.
# this line creates a target that packages your binary and zips it up
aws_lambda_package_target(${PROJECT_NAME} NO_LIBC)
