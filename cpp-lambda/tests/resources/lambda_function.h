#ifndef LAMBDA_FUNCTION_H
#define LAMBDA_FUNCTION_H

#include <aws/lambda-runtime/runtime.h>

aws::lambda_runtime::invocation_response echo_success(aws::lambda_runtime::invocation_request const& request);
aws::lambda_runtime::invocation_response echo_failure(aws::lambda_runtime::invocation_request const& request);
aws::lambda_runtime::invocation_response binary_response(aws::lambda_runtime::invocation_request const& request);
aws::lambda_runtime::invocation_response crash_backtrace(aws::lambda_runtime::invocation_request const& request);

constexpr unsigned int AWSLOGO_PNG_LEN = 1451;
extern unsigned char awslogo_png[AWSLOGO_PNG_LEN];

#endif // LAMBDA_FUNCTION_H
