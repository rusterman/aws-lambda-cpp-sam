# Example using the AWS C++ Lambda Runtime and Amazon API Gateway

In this example, we'll build a simple "Hello, World" lambda function that can be invoked using an api endpoint created using Amazon API gateway. This example can be viewed as the C++ counterpart to the NodeJS "Hello, World" API example as viewed [here](https://docs.aws.amazon.com/apigateway/latest/developerguide/api-gateway-create-api-as-simple-proxy-for-lambda.html). At the end of this example, you should be able to invoke your lambda via an api endpoint and receive a raw JSON response. This example employs the use of the AWS C++ SDK to parse the request and write the necessary response.

## Building the AWS C++ SDK

First, we need to build the AWS C++ SDK to use in our Lambda function. Include the following commands in your Dockerfile:

```dockerfile
# Increase git buffer size to 4GB
RUN git config --global http.postBuffer 4294967296

# Clone and build the AWS SDK for C++
RUN git clone https://github.com/aws/aws-sdk-cpp.git && \
    cd aws-sdk-cpp && \
    git submodule update --init --recursive && \
    mkdir build && \
    cd build && \
    cmake3 .. -DBUILD_ONLY="core" \
              -DCMAKE_BUILD_TYPE=Release \
              -DBUILD_SHARED_LIBS=OFF \
              -DCUSTOM_MEMORY_MANAGEMENT=OFF \
              -DCMAKE_INSTALL_PREFIX=/usr/local && \
    make && \
    make install


# Next, we'll build the AWS Lambda C++ runtime:
# Clone the aws-lambda-cpp repository from GitHub and build it
RUN git clone https://github.com/awslabs/aws-lambda-cpp.git && \
    cd aws-lambda-cpp && \
    mkdir build && \
    cd build && \
    cmake3 .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_INSTALL_PREFIX=/usr/local && \
    make && \
    make install
```

## Setting Up the Lambda Function
```dockerfile
# Set the working directory to /var/task
WORKDIR ${LAMBDA_TASK_ROOT}

# Copy the Lambda function source code to the container
COPY examples/${LAMBDA_PACKAGE_NAME} ${LAMBDA_TASK_ROOT}/src
WORKDIR ${LAMBDA_TASK_ROOT}/src
```


## Building and Packaging the Lambda Function
To build and package the Lambda function, follow these steps:
Ensure you have your AWS credentials set:
- AWS_REGION=YOUR-REGION
- AWS_ACCESS_KEY_ID=YOUR-ACCESS-KEY
- AWS_SECRET_ACCESS_KEY=YOUR-SECRET-ACCESS-KEY

```dockerfile
RUN mkdir build && \
    cd build && \
    cmake3 .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr/local && \
    make aws-lambda-package-${LAMBDA_PACKAGE_NAME} && \
    unzip ${LAMBDA_TASK_ROOT}/src/build/${LAMBDA_PACKAGE_NAME}.zip -d ${LAMBDA_TASK_ROOT}/artifact
```

You should now have a zip file called `api-gateway.zip`. Follow the instructions in the main README to upload it and return here once complete.


## Making an API Call from the Host Machine
You can use `curl` or Postman to make an API call:

```bash
curl -X POST http://localhost:9000/2015-03-31/functions/function/invocations 
-d @payload.json --header "Content-Type: application/json" 
-o response.js
```

`payload.json` contains an example request body and `response.js` will contain the response from the invocation. 
Example response:

```json
{ 
   "message":  "Good morning, Alice of Wonderland. Happy Monday!"
}
```


## Using Amazon API Gateway
For the rest of this example, we will use the AWS Management Console to create the API endpoint using Amazon API Gateway.

1. Navigate to AWS Lambda within the console [here](https://console.aws.amazon.com/lambda/home)
1. Select the newly created function. Within the specific function, the "Designer" window should appear.
1. Simply click "Add trigger" -> "API Gateway" -> "Create an API". Please view the settings below.
   * API Type: HTTP API
   * Security: Open
   * API name: Hello-World-API (or desired name)
   * Deployment stage: default
1. Once you have added the API gateway, locate the newly created endpoint. View how to test the endpoint below.

## Test the endpoint
Feel free to test the endpoint any way you desire. Below is a way to test using cURL:

```
curl -v -X POST \
  '<YOUR-API-ENDPOINT>?name=Bradley&city=Chicago' \
  -H 'content-type: application/json' \
  -H 'day: Sunday' \
  -d '{ "time": "evening" }'
```

With the expected response being:
```json
{
  "message": "Good evening, Bradley of Chicago. Happy Sunday!"
}
```
