# Example using the AWS C++ SDK with Lambda and Amazon S3 Bucket

In this example, we'll build an AWS Lambda function that downloads an image file from S3 and returns it as a Base64 encoded string. This encoded string can be displayed on a web page.

## Reasons for Encoding to Base64

1. **Transporting Binary Data Over Text-Based Protocols:**
   - **HTTP and JSON:** Many web protocols, such as HTTP, are designed to handle text data. When you need to send binary data (like images, files, etc.) over these protocols, encoding the data to Base64 converts it to a text format that can be easily transmitted.
   - **Email:** Email protocols like SMTP are also text-based and often require binary attachments to be encoded in Base64.

2. **Avoiding Data Corruption:**
   - **Special Characters:** Binary data might contain special characters that can be misinterpreted by systems designed to handle text, leading to data corruption. Base64 encoding ensures that the data remains intact during transmission.

3. **Compatibility with JSON:**
   - **APIs:** When interacting with APIs, particularly RESTful APIs, it is common to use JSON for data exchange. JSON does not natively support binary data, so encoding binary data in Base64 allows it to be included in JSON payloads.

## Use Cases for Base64 Encoding

1. **File Uploads in Web Applications:**
   - When users upload files through a web application, the files are often sent to the server as Base64 encoded strings. This is particularly useful when using AJAX to send data to the server without reloading the page.

2. **API Communication:**
   - **Image Processing APIs:** When sending images to a web service for processing (e.g., an OCR service), the image can be encoded in Base64 and included in the JSON request body.
   - **Document Storage:** When storing documents or other binary files via a web API, encoding the file content in Base64 allows the data to be safely included in the API request.

3. **Embedding Binary Data in HTML/CSS:**
   - **Data URIs:** Base64 encoding is used to embed images directly into HTML or CSS files using data URIs. This can reduce the number of HTTP requests needed to load a web page, improving performance.

## Example Scenario: Sending an Image via JSON API

```json
{
   "image_data": "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAA..."
}
```


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
    cmake3 .. -DBUILD_ONLY="s3" \
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

After running the above commands, you should have a zip file named `${LAMBDA_PACKAGE_NAME}.zip`. `${LAMBDA_PACKAGE_NAME}` is a variable defined in your `.env` file.

## Running the AWS Lambda Emulator
The Docker Compose file will run the aws-lambda-emulator container and mount the `shared_artifact:/var/task` volume. This will unzip our Lambda function package to the `/var/task` root, allowing us to invoke and test our Lambda function locally.

## Invoke the Lambda Function and Save the Response
```bash
curl -XPOST "http://localhost:9000/2015-03-31/functions/function/invocations" -d '{
    "s3bucket": "your-s3-test-bucket",
    "s3key": "your-test-image.png"
}' -o response.json
```
You can convert `response.json` to PNG or JPG format.


