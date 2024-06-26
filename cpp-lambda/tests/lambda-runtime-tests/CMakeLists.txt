cmake_minimum_required(VERSION 3.17)
project(aws-lambda-runtime-tests LANGUAGES CXX)

find_package(AWSSDK COMPONENTS lambda iam)
find_package(ZLIB REQUIRED)  # Add this line
find_package(CURL REQUIRED)  # Add this line

add_executable(${PROJECT_NAME}
        main.cpp
        runtime_tests.cpp
        version_tests.cpp
        gtest/gtest-all.cc)

target_link_libraries(${PROJECT_NAME} PRIVATE ${AWSSDK_LINK_LIBRARIES} aws-lambda-runtime ZLIB::ZLIB CURL::libcurl)  # Link zlib and libcurl

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME} EXTRA_ARGS "--aws_prefix=${TEST_RESOURCE_PREFIX}")

add_subdirectory(resources)
