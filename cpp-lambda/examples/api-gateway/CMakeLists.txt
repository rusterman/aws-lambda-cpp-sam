cmake_minimum_required(VERSION 3.17)

# Set the C++ standard from the environment variable
if(NOT DEFINED CPP_VERSION)
    set(CPP_VERSION 11)  # Default to C++11 if not set
endif()

set(CMAKE_CXX_STANDARD ${CPP_VERSION})

project(api-gateway LANGUAGES CXX)

find_package(aws-lambda-runtime REQUIRED)
find_package(AWSSDK COMPONENTS core)
find_package(ZLIB REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp")

# Dynamically set the compile features based on CPP_VERSION
string(CONCAT CXX_STD_FEATURE "cxx_std_" ${CPP_VERSION})
target_compile_features(${PROJECT_NAME} PRIVATE ${CXX_STD_FEATURE})

target_link_libraries(${PROJECT_NAME} PUBLIC AWS::aws-lambda-runtime ${AWSSDK_LINK_LIBRARIES} ZLIB::ZLIB)

# Important is, that if you are building in an amazon linux environment
# you have to include aws_lambda_package_target(api-gateway NO_LIBC) to your CMakeLists.txt.
# This is in order to not include the C runtime as a dependency.
# This is important because the AWS Lambda execution environment already includes the C runtime,
# and including it in the deployment package would be redundant and could cause issues.
aws_lambda_package_target(${PROJECT_NAME} NO_LIBC)
