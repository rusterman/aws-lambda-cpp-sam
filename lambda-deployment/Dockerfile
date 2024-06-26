# Use an official Python runtime as a parent image
FROM python:3.9-slim

# Define environment variables for AWS credentials and region
ENV AWS_ACCESS_KEY_ID=your-cli-user-access-key
ENV AWS_SECRET_ACCESS_KEY=your-cli-user-secret-key
ENV AWS_DEFAULT_REGION=your-region

# Set the working directory in the container
WORKDIR /lambda-deploy

# Install Node.js, npm, and AWS CLI
RUN apt-get update && \
    apt-get install -y nodejs npm awscli

# Configure AWS CLI
RUN aws configure set aws_access_key_id $AWS_ACCESS_KEY_ID && \
    aws configure set aws_secret_access_key $AWS_SECRET_ACCESS_KEY && \
    aws configure set region $AWS_DEFAULT_REGION

# Install AWS CDK globally
RUN npm install -g aws-cdk

# Install dependencies
RUN cdk init app --language python && pip install -r requirements.txt

# Copy the rest of the application code
COPY ./src/app.py .
COPY ./src/lambda_deploy/lambda_deploy_stack.py ./lambda_deploy

# Copy the entrypoint script
COPY ./entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# Keep the container running
CMD ["sh", "-c", "tail -f /dev/null"]

# Command to bootstrap (Bootstrap only if necessary)
# RUN cdk bootstrap

# Common CDK commands
# RUN cdk --version
# RUN cdk ls
# RUN cdk synth
# RUN cdk diff
# RUN cdk deploy --require-approval never