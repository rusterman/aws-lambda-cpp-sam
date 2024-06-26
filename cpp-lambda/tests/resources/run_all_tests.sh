#!/bin/sh

# Run lambda-test-fun with binary_response
./lambda-test-fun binary_response
echo

# Run lambda-test-fun with echo_success and payload
./lambda-test-fun echo_success '{"message": "Hello"}'

# Run lambda-test-fun with echo_failure
./lambda-test-fun echo_failure

# Run lambda-test-fun with crash_backtrace
./lambda-test-fun crash_backtrace
echo

# Run lambda_function_test
./lambda_function_test
