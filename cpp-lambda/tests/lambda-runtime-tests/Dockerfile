FROM amazonlinux:2

ARG LAMBDA_TASK_ROOT=/var/task
ARG AWS_REGION=your-region
ARG AWS_ACCESS_KEY_ID=your-access-key
ARG AWS_SECRET_ACCESS_KEY=your-secret-access-key
ARG LAMBDA_TEST_ROLE=integration-tests
ARG LAMBDA_PACKAGE_NAME=lambda-test-fun
ARG DCMAKE_BUILD_TYPE=Debug

# Set environment variables from build arguments
ENV LAMBDA_TASK_ROOT=${LAMBDA_TASK_ROOT}
ENV AWS_REGION=${AWS_REGION}
ENV AWS_ACCESS_KEY_ID=${AWS_ACCESS_KEY_ID}
ENV AWS_SECRET_ACCESS_KEY=${AWS_SECRET_ACCESS_KEY}
ENV LAMBDA_TEST_ROLE=${LAMBDA_TEST_ROLE}
ENV LAMBDA_PACKAGE_NAME=${LAMBDA_PACKAGE_NAME}
ENV DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE}

# Install essential packages
RUN yum -y groupinstall "Development Tools" && \
    yum -y install sudo nano make git gcc-c++ curl-devel ninja-build clang cmake3 unzip zlib-devel openssl-devel googletest-devel

# Increase git buffer size to 4GB
RUN git config --global http.postBuffer 4294967296

# Clone and build the AWS SDK for C++ with necessary components
RUN git clone https://github.com/aws/aws-sdk-cpp.git && \
    cd aws-sdk-cpp && \
    git submodule update --init --recursive && \
    mkdir build && \
    cd build && \
    cmake3 .. -DBUILD_ONLY="lambda;iam;core" \
             -DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE} \
             -DBUILD_SHARED_LIBS=OFF \
             -DCUSTOM_MEMORY_MANAGEMENT=OFF \
             -DCMAKE_INSTALL_PREFIX=/usr/local && \
    make && \
    make install

# This test requires aws-lambda-cpp
RUN git clone https://github.com/awslabs/aws-lambda-cpp.git && \
    cd aws-lambda-cpp && \
    mkdir build && \
    cd build && \
    cmake3 .. -DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE} -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_INSTALL_PREFIX=/usr/local && \
    make && \
    make install


# Set the working directory to /var/task
WORKDIR ${LAMBDA_TASK_ROOT}/src/test

# Use a .dockerignore file to exclude unnecessary files
COPY . ${LAMBDA_TASK_ROOT}/src/test

# Build and Run Tests
RUN mkdir build && cd build && cmake3 .. && make

# Set the working directory to /var/task/build/resources
WORKDIR ${LAMBDA_TASK_ROOT}/src/test/build/resources

# Build and package the Lambda function
RUN cmake3 .. -DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=/usr/local && \
    make aws-lambda-package-${LAMBDA_PACKAGE_NAME}

WORKDIR ${LAMBDA_TASK_ROOT}/src/test/build

CMD ["./aws-lambda-runtime-tests"]