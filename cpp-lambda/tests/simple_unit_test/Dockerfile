FROM amazonlinux:2

ARG LAMBDA_TASK_ROOT=/var/task

# Set environment variables from build arguments
ENV LAMBDA_TASK_ROOT=${LAMBDA_TASK_ROOT}

# Install essential packages
RUN yum -y install make git gcc-c++ clang cmake3

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

CMD ["./build/sample_test"]