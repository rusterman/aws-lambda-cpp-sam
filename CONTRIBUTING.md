# Contributing to AWS Lambda C++ Framework

First off, thank you for taking the time to contribute! 🎉


## How Can You Contribute?

- Reporting Bugs
- Suggesting Enhancements
- Writing Code (Fixes, Features, Documentation)
- Improving Documentation
- Adding Tests


## Getting Started

To get started, follow these steps:

1. Fork the repository.
2. Clone your fork:
   ```sh
   git clone https://github.com/yourusername/your-repository-name.git
   ```
3. Create a new branch for your feature or bugfix:
   ```sh
   git checkout -b feature/your-feature-name
   ```
   

## Building the Project

To build the project, you'll need Docker and Docker Compose installed. The project uses a multi-container setup for development, testing, and deployment.

1. Build and start the Docker containers:
    ```sh
    docker-compose up --build
    ```
2. The above command will initiate the build process, start the necessary services, and run tests.


## Running Tests

To ensure your changes don't break existing functionality, run the tests:

1. Start the `unit-tests` service:
    ```sh
    docker-compose run unit-tests
    ```
2. Check the test results and make sure all tests pass before submitting your changes.


## Adding New Examples or Tests
1. **Examples:** Add new examples to the `cpp-lambda/examples` directory. Ensure each example has its own `CMakeLists.txt` file and a README explaining how to build and run the example.
2. **Tests:** Add new tests to the `cpp-lambda/tests` directory. Follow the existing structure and use the Google Test framework for writing unit tests.


## Committing Your Changes

1. Stage your changes:
    ```sh 
    git add .
    ```
2. Commit your changes with a descriptive message:
    ```sh 
    git commit -m "Add feature XYZ"
    ```

3. Commit your changes with a descriptive message:
    ```sh 
    git push origin feature/your-feature-name
    ```


## Creating a Pull Request

1. Navigate to the original repository on GitHub.
2. Click on the "New pull request" button.
3. Select the branch you just pushed to.
4. Provide a clear title and description for your pull request.
5. Submit the pull request.


## Code of Conduct
Please note that this project adheres to a Code of Conduct. By participating, you are expected to uphold this code.


## Style Guide
- Follow the C++ Core Guidelines and adhere to the project's existing style.
- Use meaningful variable and function names.
- Document your code appropriately.
- Write unit tests for any new features or changes.


## Reporting Bugs
If you find a bug, please report it by opening an issue. Include as much detail as possible:

- Steps to reproduce the bug.
- Expected behavior.
- Actual behavior.
- Your environment (OS, Docker version, etc.).


## Suggesting Enhancements
If you have a suggestion for improving the project, please open an issue with the following information:

- A detailed description of the enhancement.
- The motivation behind the enhancement.
- Any examples or references that could help understand the enhancement better.

## Thank You!
Thank you for your interest in contributing to the AWS Lambda C++ Framework! Your contributions are highly appreciated.