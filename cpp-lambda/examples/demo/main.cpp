#include <iostream>
#include <string>
#include <aws/lambda-runtime/runtime.h>

using namespace std;
using namespace aws::lambda_runtime;

static invocation_response my_handler(invocation_request const& req)
{
    if (req.payload.length() > 42) {
        return invocation_response::failure("error message here" /*error_message*/,
                                            "error type here" /*error_type*/);
    }

    /*
        Here are the key attributes that req might contain (depending on the specific event type):
        - payload: This is a string attribute containing the actual data or payload sent with the event that triggered the Lambda function.
          You can access its length using req.payload.length().
        - headers: This might be an object containing key-value pairs representing the headers sent with the event.
          (Not explicitly shown in the provided code).
        - context: This could be an object containing additional context information about the invocation,
          such as Lambda function name, memory limits, and execution time remaining.
          (Not explicitly shown in the provided code, but might be available depending on the library version).
    */

    string message = "payload: ";
    message += req.payload;

    return invocation_response::success(message, "application/json" /*MIME type*/);
}

int main()
{
    run_handler(my_handler);
    return 0;
}
