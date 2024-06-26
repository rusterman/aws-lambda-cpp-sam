# AWS Lambda Runtime Tests

This project contains tests for AWS Lambda functions written in C++. It leverages the AWS SDK for C++ and the AWS Lambda C++ runtime to create, invoke, and verify the behavior of Lambda functions. The project uses the Google Test framework for defining and running the tests.

## Project Structure
    .
    ├── gtest/                  
    ├── resources/
    │   ├── CMakeLists.txt
    │   └── lambda_function.cpp
    ├── CMakeLists.txt
    ├── main.cpp
    ├── runtime_tests.cpp
    ├── version_tests.cpp
    ├── Dockerfile  
    ├── .dockerignore 
    └── README.md

## Acknowledgments

- AWS SDK for C++
- Google Test Framework
- Docker

## Lambda Function Tests

The project includes a set of unit tests for AWS Lambda functions written in C++. These tests use the AWS SDK for C++ and the Google Test framework to create, invoke, and validate the behavior of the Lambda functions. The main components of the tests are:

- **LambdaRuntimeTest Structure**: A test fixture that sets up and tears down Lambda functions for testing. It includes methods to create and delete Lambda functions and retrieve IAM role ARNs.
- **Test Cases**:
    - `echo_success`: Tests that the function returns the input payload as a successful JSON response.
    - `echo_unicode`: Tests that the function correctly handles and returns Unicode text.
    - `echo_failure`: Tests that the function returns an "Unhandled" error.
    - `binary_response`: Tests that the function returns a binary response of the expected length.
    - `crash`: Tests that the function throws a runtime error and generates a stack trace.

Each test case ensures the Lambda functions behave as expected under different scenarios, such as success, failure, and error handling. The tests are run in a Docker container to provide a consistent environment.

## Environment Variables

The following environment variables need to be set for the Docker image in order to create, update, and delete Lambda functions on your AWS account:

- **AWS_REGION**: AWS region (default: `YOUR_AWS_REGION`).
- **AWS_ACCESS_KEY_ID**: AWS access key ID.
- **AWS_SECRET_ACCESS_KEY**: AWS secret access key.
- **LAMBDA_TEST_ROLE**: IAM role for the Lambda function (default: `YOUR_IAM_ROLE_NAME`).
- **LAMBDA_PACKAGE_NAME**: Name of the Lambda package (default: `lambda-test-fun`).

## Building and Running the Project

```sh
docker build -t lambda-test-fun .
docker run --rm -it lambda-test-fun
```
