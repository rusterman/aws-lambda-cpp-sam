#!/bin/bash

# Copy the lambda.zip file to the /lambda-deploy directory
cp /shared_lambda_zip/lambda.zip /lambda-deploy

# Run CDK commands
cdk --version
cdk bootstrap
cdk ls
cdk synth
cdk diff
# cdk deploy --require-approval never
# cdk destroy --require-approval never

# Keep the container running
tail -f /dev/null
