FROM amazonlinux:2

ARG LAMBDA_TASK_ROOT=/var/task
ARG DCMAKE_BUILD_TYPE=Debug

# Set environment variables from build arguments
ENV LAMBDA_TASK_ROOT=${LAMBDA_TASK_ROOT}
ENV DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE}

# Install essential packages
RUN yum -y install make git gcc-c++ clang cmake3 libcurl-devel

# This test requires aws-lambda-cpp
RUN git clone https://github.com/awslabs/aws-lambda-cpp.git && \
    cd aws-lambda-cpp && \
    mkdir build && \
    cd build && \
    cmake3 .. -DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE} -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_INSTALL_PREFIX=/usr/local && \
    make && \
    make install

# Clone and install Google Test
RUN git clone --branch release-1.10.0 https://github.com/google/googletest.git /usr/src/googletest && \
    cd /usr/src/googletest && \
    mkdir build && cd build && \
    cmake3 .. && make && make install

# Set the working directory to /var/task
WORKDIR ${LAMBDA_TASK_ROOT}/src/test

# Use a .dockerignore file to exclude unnecessary files
COPY . ${LAMBDA_TASK_ROOT}/src/test

# Build and Run Tests
RUN mkdir build && cd build && cmake3 .. && make

# Set the working directory to /var/task/build
WORKDIR ${LAMBDA_TASK_ROOT}/src/test/build

# Copy the script to the container
COPY run_all_tests.sh .

# Make the script executable
RUN chmod +x ${LAMBDA_TASK_ROOT}/src/test/build/run_all_tests.sh

# Set the command to run the script and keep the container running
CMD ["sh", "-c", "./run_all_tests.sh && tail -f /dev/null"]