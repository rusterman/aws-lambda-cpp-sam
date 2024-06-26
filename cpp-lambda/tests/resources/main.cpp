#include <aws/lambda-runtime/runtime.h>
#include <aws/logging/logging.h>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <functional>
#include <iostream>
#include "lambda_function.h"

using namespace aws::lambda_runtime;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <handler_name> [payload]" << std::endl;
        return 1;
    }

    std::unordered_map<std::string, std::function<invocation_response(invocation_request const&)>> handlers;
    handlers.emplace("echo_success", echo_success);
    handlers.emplace("echo_failure", echo_failure);
    handlers.emplace("binary_response", binary_response);
    handlers.emplace("crash_backtrace", crash_backtrace);

    const char* handler_name = argv[1];
    auto it = handlers.find(handler_name);
    if (it == handlers.end()) {
        std::cerr << "Handler " << handler_name << " not found. Exiting." << std::endl;
        return -2;
    }

    invocation_request req;
    if (argc > 2) {
        req.payload = argv[2];
    }

    try {
        auto resp = it->second(req);
        std::cout << "Response: " << resp.get_payload() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Handler threw an exception: " << e.what() << std::endl;
    }

    return 0;
}
