# Lambda Test

This project demonstrates a simple AWS Lambda function setup using C++ and Google Test for unit testing. The project includes:
- AWS Lambda function implementation.
- Unit tests for the Lambda functions.
- Dockerfile for building and running the project in an Amazon Linux environment.

## Prerequisites

- Docker
- CMake (version 3.17 or higher)
- AWS Lambda C++ Runtime
- Google Test

## Project Structure

- `CMakeLists.txt`: CMake configuration file
- `Dockerfile`: Dockerfile to build the environment and run tests
- `lambda_function.cpp`: Implementation of Lambda functions
- `lambda_function.h`: Header file for Lambda functions
- `lambda_function_test.cpp`: Unit tests for Lambda functions
- `main.cpp`: Main executable to invoke Lambda functions
- `run_all_tests.sh`: Script to run all tests


## Building and Running the Project
```shell
docker build -t lambda-test-fun .
docker run --rm -it lambda-test-fun
```
This command will execute the run_all_tests.sh script, which runs the Lambda functions and the unit tests.


## Conclusion

This project demonstrates setting up AWS Lambda functions in C++, writing unit tests using Google Test, and using Docker to create a consistent build environment.
