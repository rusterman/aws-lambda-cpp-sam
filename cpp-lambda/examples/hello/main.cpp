// main.cpp
#include <aws/lambda-runtime/runtime.h>
#include <iostream>
#include <string>
using namespace aws::lambda_runtime;

invocation_response my_handler(invocation_request const& request)
{
    // Print the payload from the invocation request
    std::cout << "Received event: " << request.payload << std::endl;

    // Print additional request details if available
    std::cout << "Request ID: " << request.request_id << std::endl;
    std::cout << "Cognito Identity: " << request.cognito_identity << std::endl;
    std::cout << "Client Context: " << request.client_context << std::endl;

    // Check for the C++ version
    // Check for the C++ version
    if (__cplusplus == 201103L) {
        std::cout << "C++11" << std::endl;
    } else if (__cplusplus == 201402L) {
        std::cout << "C++14" << std::endl;
    } else if (__cplusplus == 201703L) {
        std::cout << "C++17" << std::endl;
    } else if (__cplusplus == 202002L) {
        std::cout << "C++20" << std::endl;
    } else {
        std::cout << "Pre-C++11 or an unknown C++ version" << std::endl;
    }

    // Define a simple response message
    std::string message = "{\"message\": \"Hello, World!\"}";

    // Return the response
    return invocation_response::success(message, "application/json");
}

int main()
{
    run_handler(my_handler);
    return 0;
}