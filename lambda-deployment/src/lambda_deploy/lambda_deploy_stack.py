from aws_cdk import (
    Stack,
    aws_iam as iam,
    aws_lambda as lambda_,
    aws_apigateway as apigateway,
    Duration,
)

from constructs import Construct

class LambdaStack(Stack):

    def __init__(self, scope: Construct, construct_id: str, **kwargs) -> None:
        super().__init__(scope, construct_id, **kwargs)

        # Ensure the IAM user exists
        user = iam.User.from_user_name(self, "YourCliAdminUser", user_name="your-cli-admin-user")

        # Define the Lambda function
        cpp_lambda = lambda_.Function(
            self,
            "CppLambda",  # Logical ID
            function_name="cpp-lambda",  # Name of the Lambda function
            runtime=lambda_.Runtime.PROVIDED_AL2,  # Amazon Linux 2 runtime
            architecture=lambda_.Architecture.ARM_64,  # ARM64 architecture
            handler="index.my_handler",  # The handler function name
            code=lambda_.Code.from_asset("./lambda.zip"),  # Path to the lambda.zip file
            memory_size=512,  # Memory size in MB
        )

        # Add CloudWatch Logs permissions to the Lambda execution role
        cpp_lambda.add_to_role_policy(
            iam.PolicyStatement(
                actions=[
                    "logs:CreateLogGroup",
                    "logs:CreateLogStream",
                    "logs:PutLogEvents"
                ],
                resources=[f"arn:aws:logs:{self.region}:{self.account}:log-group:/aws/lambda/*"]
            )
        )

        # Define the API Gateway with non-proxy integration
        api = apigateway.RestApi(
            self, 'CppApiGateway',
            rest_api_name='CppService',
            description='This service serves a Lambda function.',
        )

        # Configure POST method integration with Lambda
        post_integration = apigateway.LambdaIntegration(
            cpp_lambda,
            proxy=False,  # Disable proxy integration
            integration_responses=[
                apigateway.IntegrationResponse(
                    status_code="200",
                    response_templates={"application/json": ''}
                )
            ]
        )

        # Create an API resource and method
        api_resource = api.root.add_resource('invoke')
        api_resource.add_method(
            'POST',
            post_integration,
            method_responses=[
                apigateway.MethodResponse(status_code="200"),
                apigateway.MethodResponse(status_code="500"),
                apigateway.MethodResponse(status_code="502"),
            ]
        )

        # Grant API Gateway permission to invoke the Lambda function
        cpp_lambda.add_permission(
            "ApiGatewayInvoke",
            principal=iam.ServicePrincipal("apigateway.amazonaws.com"),
            source_arn=f"arn:aws:execute-api:{self.region}:{self.account}:{api.rest_api_id}/*/POST/invoke"
        )




