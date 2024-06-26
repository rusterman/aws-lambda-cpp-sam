#include <gtest/gtest.h>
#include <aws/lambda-runtime/runtime.h>
#include "lambda_function.h"

TEST(LambdaFunctionTest, EchoSuccess) {
    aws::lambda_runtime::invocation_request request;
    request.payload = "{\"message\": \"hello\"}";
    auto response = echo_success(request);
    EXPECT_EQ(response.get_payload(), "{\"message\": \"hello\"}");
}

TEST(LambdaFunctionTest, EchoFailure) {
    aws::lambda_runtime::invocation_request request;
    auto response = echo_failure(request);
    std::string expected_payload = R"({"errorMessage":"Test error message","errorType":"TestErrorType", "stackTrace":[]})";
    EXPECT_EQ(response.get_payload(), expected_payload);
}

TEST(LambdaFunctionTest, BinaryResponse) {
    aws::lambda_runtime::invocation_request request;
    auto response = binary_response(request);
    std::string expected_payload(reinterpret_cast<char*>(awslogo_png), AWSLOGO_PNG_LEN);
    EXPECT_EQ(response.get_payload(), expected_payload);
}

TEST(LambdaFunctionTest, CrashBacktrace) {
    aws::lambda_runtime::invocation_request request;
    EXPECT_THROW({
        try {
            crash_backtrace(request);
        } catch (const std::runtime_error& e) {
            EXPECT_STREQ("barf", e.what());
            throw;
        }
    }, std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
