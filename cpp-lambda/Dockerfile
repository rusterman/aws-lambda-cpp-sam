FROM amazonlinux:2

# Accept build arguments
ARG CC
ARG CXX
ARG CPP_VERSION
ARG LAMBDA_TASK_ROOT
ARG LAMBDA_PACKAGE_NAME
ARG DCMAKE_BUILD_TYPE

# Set environment variables from build arguments
ENV CC=${CC}
ENV CXX=${CXX}
ENV CPP_VERSION=${CPP_VERSION}
ENV LAMBDA_TASK_ROOT=${LAMBDA_TASK_ROOT}
ENV LAMBDA_PACKAGE_NAME=${LAMBDA_PACKAGE_NAME}
ENV DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE}

# Install essential packages
RUN yum -y groupinstall "Development Tools" && \
    yum -y install sudo nano make git gcc-c++ curl-devel ninja-build clang cmake3 unzip zlib-devel openssl-devel

# Increase git buffer size to 4GB
RUN git config --global http.postBuffer 4294967296

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

RUN git clone https://github.com/awslabs/aws-lambda-cpp.git && \
    cd aws-lambda-cpp && \
    mkdir build && \
    cd build && \
    cmake3 .. -DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE} -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_INSTALL_PREFIX=/usr/local && \
    make && \
    make install

# Set the working directory to /var/task
WORKDIR ${LAMBDA_TASK_ROOT}

# Copy the Lambda function source code to the container
COPY examples/${LAMBDA_PACKAGE_NAME} ${LAMBDA_TASK_ROOT}/src
WORKDIR ${LAMBDA_TASK_ROOT}/src

# Build and package the Lambda function
RUN mkdir build && \
    cd build && \
    cmake3 .. -DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=/usr/local -DCPP_VERSION=${CPP_VERSION} && \
    make aws-lambda-package-${LAMBDA_PACKAGE_NAME} && \
    unzip ${LAMBDA_TASK_ROOT}/src/build/${LAMBDA_PACKAGE_NAME}.zip -d ${LAMBDA_TASK_ROOT}/lambda && \
    mkdir -p /shared_lambda_zip && \
    cp ${LAMBDA_TASK_ROOT}/src/build/${LAMBDA_PACKAGE_NAME}.zip /shared_lambda_zip/lambda.zip
