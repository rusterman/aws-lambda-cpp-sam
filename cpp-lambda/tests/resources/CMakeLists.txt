cmake_minimum_required(VERSION 3.17)
project(lambda-test-fun LANGUAGES CXX)

# Add the common library
add_library(lambda_function_lib lambda_function.cpp)

# Add the main executable
add_executable(${PROJECT_NAME} main.cpp)

# Add the test executable
add_executable(lambda_function_test lambda_function_test.cpp)

# Include directories for AWS Lambda C++ Runtime and Google Test
target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include)
target_include_directories(lambda_function_test PRIVATE /usr/local/include /usr/src/googletest/googletest/include)

# Link against the common library and the AWS Lambda C++ Runtime and libcurl
target_link_libraries(${PROJECT_NAME} PRIVATE lambda_function_lib aws-lambda-runtime curl)

# Link against the common library, AWS Lambda C++ Runtime, Google Test, and libcurl
target_link_libraries(lambda_function_test PRIVATE lambda_function_lib aws-lambda-runtime curl gtest pthread)
