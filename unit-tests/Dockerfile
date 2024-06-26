FROM amazonlinux:2

# Accept build arguments
ARG CC=gcc
ARG CXX=c++
ARG LAMBDA_TASK_ROOT=/var/task

# Set environment variables from build arguments
ENV CC=${CC}
ENV CXX=${CXX}
ENV LAMBDA_TASK_ROOT=${LAMBDA_TASK_ROOT}

# Install essential packages
RUN yum -y groupinstall "Development Tools" && \
    yum -y install sudo nano make git gcc-c++ curl-devel ninja-build clang cmake3 zlib-devel openssl-devel

# Clone and install Google Test
RUN git clone --branch release-1.10.0 https://github.com/google/googletest.git /usr/src/googletest && \
    cd /usr/src/googletest && \
    mkdir build && cd build && \
    cmake3 .. && make && make install

# Clone and install CPR from a stable tag
# CPR is a C++ HTTP client library that makes it easy to perform HTTP requests
RUN git clone --branch 1.7.1 https://github.com/libcpr/cpr.git /usr/src/cpr && \
    cd /usr/src/cpr && \
    mkdir build && cd build && \
    cmake3 .. -DOPENSSL_ROOT_DIR=/usr/lib64/openssl -DOPENSSL_LIBRARIES=/usr/lib64 && make && make install

# nlohmann/json provides a simple, intuitive, and efficient way to parse, serialize, and manipulate JSON data in C++
RUN mkdir -p /usr/local/include/nlohmann && \
    curl -L https://github.com/nlohmann/json/releases/download/v3.10.5/json.hpp -o /usr/local/include/nlohmann/json.hpp

# Set the working directory to /var/task
WORKDIR ${LAMBDA_TASK_ROOT}/src/test

# Use a .dockerignore file to exclude unnecessary files
COPY ./api-gateway .

# Build and Run Tests
RUN mkdir build && cd build && cmake3 .. && make

# Set the working directory to /var/task
WORKDIR ${LAMBDA_TASK_ROOT}/src/test/build

COPY ./payload .

