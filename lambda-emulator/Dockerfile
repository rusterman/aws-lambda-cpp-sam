FROM amazonlinux:2

# Accept build arguments
ARG LAMBDA_TASK_ROOT
ARG AWS_LAMBDA_FUNCTION_MEMORY_SIZE

# Set environment variables from build arguments
ENV AWS_LAMBDA_FUNCTION_MEMORY_SIZE=${AWS_LAMBDA_FUNCTION_MEMORY_SIZE}
ENV LAMBDA_TASK_ROOT=${LAMBDA_TASK_ROOT}

# Download and install the AWS Lambda RIE for your architecture (x86_64 or arm64)
ADD https://github.com/aws/aws-lambda-runtime-interface-emulator/releases/latest/download/aws-lambda-rie /usr/local/bin/aws-lambda-rie
RUN chmod +x /usr/local/bin/aws-lambda-rie

# Set the working directory (to /var/task)
WORKDIR ${LAMBDA_TASK_ROOT}

# (Optional) Alternative deployment using pre-built artifact (commented out)
# COPY ./hello.zip ${LAMBDA_TASK_ROOT}
# RUN unzip hello.zip

# Copy the entrypoint script into the container and make it executable
COPY ./entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# Set the entrypoint to your script
ENTRYPOINT ["/entrypoint.sh"]

# Alternative entrypoint and command (without environment variable parsing)
# Not recommended - use environment variables for flexibility
# ENTRYPOINT ["/usr/local/bin/aws-lambda-rie", "/var/task/bootstrap"]
# CMD ["handler.function"]

