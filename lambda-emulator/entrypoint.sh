#!/bin/sh

# Execute the AWS Lambda Runtime Interface Emulator with the specified handler
exec /usr/local/bin/aws-lambda-rie "$LAMBDA_TASK_ROOT"/bootstrap handler.function
