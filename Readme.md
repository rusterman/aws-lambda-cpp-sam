## AWS Lambda C++ Framework Build, Test, Deploy
![GitHub release (latest by date)](https://img.shields.io/badge/release-v1.0.0-blue)
![GitHub](https://img.shields.io/github/license/rusterman/aws-lambda-cpp-framework)

| OS | Arch |
|----|------|
| Amazon Linux 2 | aarch64 | [![](https://codebuild.us-west-2.amazonaws.com/badges?uuid=eyJlbmNyeXB0ZWREYXRhIjoicWNGSmJtaGdPSCtqR25KQ1k3RWNZS1pwWlZScGZ3WU1JM0lISnZJVkhVNy8zbVIyVHp6RlBmRjN4cjZJd2xWNEd0eWZmUy9JaE1vRzBYWFcrbnpFdDUwPSIsIml2UGFyYW1ldGVyU3BlYyI6ImVoeHl5TTNtMmdERjJuWisiLCJtYXRlcmlhbFNldFNlcmlhbCI6MX0%3D&branch=master)]|

## Overview

This project is a complete framework designed to streamline and support the entire lifecycle of AWS Lambda development in C++. 
It is organized into several subfolders to facilitate the development, emulation, testing, and deployment of AWS Lambda functions written in C++.

## Key Features

- **Bug-Free**: Designed to be free of bugs and easy to understand.
- **Isolated and Flexible**: Each component runs in an isolated environment, making the system flexible and manageable.
- **Best AWS C++ Examples**: Equipped with top AWS C++ examples, including those using the AWS C++ SDK.
- **Local Invocation and Testing**: Supports invoking and testing Lambda functions on a local machine.
- **Automated Workflow**: Automates the building, emulating, testing, experimenting, versioning, and deployment processes.

## Motivation

In building my custom AWS C++ runtime, I encountered challenges such as:
- Debugging and running reliable examples.
- Understanding the AWS SDK for C++.
- Testing Lambda functions locally before deploying them to the cloud.
- Simulating payloads.

This setup aims to address these challenges by providing a comprehensive, automated solution akin to **AWS SAM** but for AWS C++ Lambdas.

Let's dive in!

Below is an overview of the subfolders and their purposes:

```
.
├── cpp-lambda/
│   ├── examples/
│   │   ├── s3/
│   │   ├── dynamodb/
│   │   └── api-gateway/
│   ├── tests/
│   │   ├── recources/
│   │   ├── simple_unit_test/
│   │   └── lambda-runtime-tests/
│   └── Dockerfile
├── lambda-emulator/
│   ├── Dockerfile
│   └── entrypoint.sh
├── unit-tests/
│   ├── api-gateway/
│   ├── test-data/
│   └── Dockerfile
├── lambda-deployment/
│   ├── src/
│   ├── Dockerfile
│   └── entrypoint.sh
├── .env
└── docker-compose.yml
```

## Project Structure

### cpp-lambda
- **examples/**: Contains core examples such as S3, DynamoDB, API Gateway, and unit tests.
    - **Purpose**: Each example demonstrates the use of AWS services with C++ Lambda functions.

### lambda-emulator
- **Dockerfile**: Contains the Docker configuration for the emulator.
- **entrypoint.sh**: Script to start the emulator.
    - **Purpose**: Emulates the C++ Lambda environment locally, allowing for local testing and debugging without deploying to AWS cloud.

### unit-tests
- **api-gateway/**: Contains tests for API Gateway integration.
- **test-data/**: Contains JSON payloads for testing.
- **Dockerfile**: Docker configuration for running unit tests.
    - **Purpose**: Runs unit tests on the built examples, invoking the AWS Lambda emulator endpoint with appropriate JSON payloads.

### lambda-deployment
- **src/**: Source files for deployment.
- **Dockerfile**: Docker configuration for deployment.
- **entrypoint.sh**: Script to manage the deployment process.
    - **Purpose**: Uses AWS CDK (Cloud Development Kit) in Python to deploy Lambda functions if unit tests pass. Creates Lambda functions with a `lambda.zip` asset from the `cpp-lambda` container, sets up an API Gateway with security credentials, and runs `cdk deploy`.

Each of these subfolders contains the necessary code and Docker files to perform their respective tasks. Each folder runs a container to achieve isolation, and their built artifacts are shared using Docker volumes.

The root folder contains a single entry point, `docker-compose.yml`. Simply running this file initiates the entire process automatically. Additionally, it includes an `.env` file with all the required environment variables for building, running, testing, and deploying (including AWS and AWS Lambda configurations).

## Environment Variables in `.env` File

The root folder's `.env` file contains crucial setups for our project:

1. `CC=gcc`: Specifies `gcc` (GNU Compiler Collection) as the C compiler.
2. `CXX=g++`: Specifies `g++` (GNU Compiler Collection for C++) as the C++ compiler.
3. `CPP_VERSION`: Specifies the C++ standard version (e.g., 11, 14, 17).
    - You can compile and build your Lambda function in C++ 11, 14, or 17 just by specifying `CPP_VERSION`.
4. `LAMBDA_TASK_ROOT=/var/task`: Specifies the root directory where the AWS Lambda function's code and dependencies are located.
5. `LAMBDA_PACKAGE_NAME`: Defines the name of the package or directory that contains the Lambda function's code.
6. `CMAKE_BUILD_TYPE`: Defines the build type (configuration) for a project:
    - `Debug`: Includes debug information and no optimization.
    - `Release`: Optimizes the build for performance, usually enabling compiler optimizations and disabling debug information.
7. `TABLE_NAME=your-dynamo-table-name**: Defines the name of the DynamoDB table that your application will interact with.
8. `AWS_REGION`: Defines the specific AWS region to use for API requests and resource operations.
9. `AWS_ACCESS_KEY_ID`: Holds the access key ID, which is a part of your AWS credentials.
10. `AWS_SECRET_ACCESS_KEY`: Used to securely sign and authenticate API requests to AWS services.
11. `AWS_SESSION_TOKEN`: Stores a temporary security token provided by AWS STS (Security Token Service), it is not mandatory.
12. `AWS_LAMBDA_FUNCTION_MEMORY_SIZE`: Defines the memory size (in megabytes) allocated to the AWS Lambda function:
    - `Important Note`: Local memory usage set by this variable might not accurately reflect the actual behavior in the AWS Lambda environment, especially in terms of performance characteristics and resource availability.

## 1. Explore the `cpp-lambda` Folder in More Detail
```
.
├── cpp-lambda/
│   ├── examples/
│   │   ├── s3/
│   │   ├── dynamodb/
│   │   └── api-gateway/
│   ├── tests/
│   │   ├── recources/
│   │   ├── simple_unit_test/
│   │   └── lambda-runtime-tests/
│   └── Dockerfile
```

Each example (`s3`, `dynamodb`, `api-gateway`) contains its own `CMakeLists.txt` file to build the project, C++ code files, and detailed instructions with a README file explaining how to run the example and what it does.

- `api-gateway` example does not require the AWS SDK for C++ but requires the AWS Lambda C++ Runtime.
- `dynamodb` example requires both the AWS SDK for C++ (core) and the AWS Lambda C++ Runtime.
- `s3` example requires both the AWS SDK for C++ (s3) and the AWS Lambda C++ Runtime.

Depending on the chosen example, here is an example of a Docker command on how to conditionally install the AWS SDK:
```dockerfile
# Conditionally install AWS SDK
RUN if [ "$LAMBDA_PACKAGE_NAME" = "api-gateway" ] || [ "$LAMBDA_PACKAGE_NAME" = "dynamodb" ] || [ "$LAMBDA_PACKAGE_NAME" = "s3" ]; then \
        git clone https://github.com/aws/aws-sdk-cpp.git && \
        cd aws-sdk-cpp && \
        git submodule update --init --recursive && \
        mkdir build && \
        cd build && \
        if [ "$LAMBDA_PACKAGE_NAME" = "api-gateway" ]; then \
            BUILD_ONLY="core"; \
        elif [ "$LAMBDA_PACKAGE_NAME" = "dynamodb" ]; then \
            BUILD_ONLY="dynamodb"; \
        elif [ "$LAMBDA_PACKAGE_NAME" = "s3" ]; then \
            BUILD_ONLY="s3"; \
        fi && \
        cmake3 .. -DBUILD_ONLY=$BUILD_ONLY \
                  -DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE} \
                  -DBUILD_SHARED_LIBS=OFF \
                  -DCUSTOM_MEMORY_MANAGEMENT=OFF \
                  -DCMAKE_INSTALL_PREFIX=/usr/local && \
        make && \
        make install; \
    fi
```

- `DBUILD_SHARED_LIBS=OFF`: Option in CMake configures the build to produce static libraries instead of shared libraries, ensuring that all necessary code is included in the final binary.
- `DCUSTOM_MEMORY_MANAGEMENT=OFF`: Option in CMake means that the build will use the standard memory management provided by the C++ runtime (such as `new`, `delete`, `malloc`, and `free`) instead of a custom memory management system that may have been implemented specifically for the project.

Each unit test example (`lambda-runtime-tests`, `resources`, `simple_unit_test`) 
contains its own README file with detailed instructions, 
a self-contained Dockerfile that you can run independently, 
demonstrating core aspects of testing different functionalities, and uses the Google Test library.

The `Dockerfile` located in the `cpp-lambda` root folder is built by `docker-compose`. 
If you decide to run it separately, you need to consider the environment variables passed through `docker-compose`.

## 2. `lambda-emulator` Folder in More Detail
```
.
├── lambda-emulator/
│   │   ├── Dockerfile
│   │   └── entrypoint.sh
```

`lambda-emulator` Dockerfile uses the AWS Lambda RIE which allows to locally invoke our built lambda function from `cpp-lambda` container, and lambda package passed through shared volume to `lambda-emulator` container.
`entrypoint.sh`: Executes the AWS Lambda Runtime Interface Emulator with the specified handler which is included in Dockerfile

```shell
exec /usr/local/bin/aws-lambda-rie "$LAMBDA_TASK_ROOT"/bootstrap handler.function
```


## 3. Lambda Invocation Test `unit-tests`
```
.
├── unit-tests/
│   ├── api-gateway/
│   ├── payload/
│   │   ├── invalid.json
│   │   ├── missing_body_field.json
│   │   ├── missing_fields.json
│   │   └── valid_input.json
│   └── Dockerfile
```

- After successfully running the `lambda-emulator` container, we can invoke and test our Lambda function with different payloads.
- As an example, this folder contains unit tests only for the `api-gateway` example written in C++, but you can use the same logic to extend it to other examples (`s3`, `dynamodb`).
- The payload folder contains JSON files for each test case. You can write your own events to get the same functionalities as in AWS SAM.

It is worth mentioning that you can write these unit tests using other programming languages like Python, Java, JavaScript, etc.

## 4. AWS Deployment `lambda-deployment` Folder
```
.
├── lambda-deployment/
│   ├── src/
│   │   ├── lambda_deploy/
│   │   │   ├── lambda_deploy_stack.py
│   │   ├── app.py
│   │── Dockerfile
│   └── entrypoint.sh
```

- **Dockerfile**: Contains environment variables for AWS credentials (`AWS_ACCESS_KEY_ID`, `AWS_SECRET_ACCESS_KEY`, `AWS_DEFAULT_REGION`).
    - This Dockerfile installs necessary dependencies including AWS CLI, AWS CDK, Python, and others.
    - **Note**: It is recommended to use a separate IAM user for deployment. The environment variables are defined in the Dockerfile for this purpose.

- **app.py**: Initializes `cdk.App()` and `LambdaStack`.

- **lambda_deploy_stack.py**: Contains Python CDK code to:
    - Create a Lambda function with a `lambda.zip` asset copied from the Docker volume (generated in `cpp-lambda`).
    - Add CloudWatch Logs.
    - Define an API Gateway with non-proxy integration.
    - Grant API Gateway permission to invoke the Lambda function.
    - Create IAM policies for resource-based access to ensure security.

- **entrypoint.sh**: Runs common CDK commands automatically but can also be executed manually from the container.
  ```shell
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
  ```

## 5. Docker Compose Configuration

### Volumes
- **shared_lambda**: A shared volume used to store Lambda function code.
- **shared_lambda_zip**: A shared volume used to store the zipped Lambda package for deployment.

### Description
- The **`app`** service builds and prepares the C++ Lambda function.
- The **`emulator`** service emulates the AWS Lambda environment locally.
- The **`unit-tests`** service runs tests against the emulated Lambda functions.
- The **`cdk-deploy`** service deploys the Lambda functions to AWS if the tests pass.

### How to start
```sh
docker-compose up
```

Each service is defined to build from a specific context, 
use necessary environment variables, and share volumes for communication between containers.

## Contributing
We welcome contributions! Please see the [CONTRIBUTING.md](https://github.com/rusterman/aws-lambda-cpp-framework/blob/main/CONTRIBUTING.md) file for guidelines on how to get involved.

## Acknowledgement

1. In `docker-compose.yml`, the platform architecture for the `cpp-lambda` and `lambda-emulator` containers is specified as `arm64` (platform: `linux/arm64`).
2. It is important that the built version and the Lambda runtime environment run on the same architecture.
3. We could also use `x86_64`, but `arm64` might perform better in memory access patterns due to its efficient design.

## Future Work

For the next release, I am planning to:
1. Include CodeQL for code quality checks.
2. Implement code sanitization to prevent command injection and secure the application from buffer overflow vulnerabilities.
3. Construct GitHub Actions to automate the workflow.
   
## License
This project is licensed under the terms of the MIT License. 
See the [LICENSE](https://github.com/rusterman/aws-lambda-cpp-framework/blob/main/LICENSE) file for details.
