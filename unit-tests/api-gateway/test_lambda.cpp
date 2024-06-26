#include <gtest/gtest.h>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <stdexcept>

using json = nlohmann::json;

class LambdaFunctionTest : public ::testing::Test {
    protected:
        std::string lambda_url;

        void SetUp() override {
            const char* lambda_url_env = std::getenv("LAMBDA_URL");
            lambda_url = lambda_url_env ? lambda_url_env : "http://emulator:8080/2015-03-31/functions/function/invocations";
        }

        cpr::Response invoke_lambda(const std::string& payload) {
            auto response = cpr::Post(
                    cpr::Url{lambda_url},
                    cpr::Header{{"Content-Type", "application/json"}},
                    cpr::Body{payload}
            );
            return response;
        }

        std::string read_file(const std::string& filename) {
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Unable to open file: " + filename);
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        }
};

TEST_F(LambdaFunctionTest, ValidInput) {
    std::string payload = read_file("valid_input.json");

    auto response = invoke_lambda(payload);
    json jsonResponse = json::parse(response.text);

    ASSERT_EQ(response.status_code, 200);
    ASSERT_EQ(jsonResponse["message"], "Good morning, John of New York. Happy Monday!");
}

TEST_F(LambdaFunctionTest, InvalidJSON) {
    std::string payload = read_file("invalid_json.json");
    auto response = invoke_lambda(payload);

    json jsonResponse = json::parse(response.text, nullptr, false);

    ASSERT_EQ(jsonResponse["errorMessage"], "Failed to parse input JSON");
}

TEST_F(LambdaFunctionTest, MissingFields) {
    std::string payload = read_file("missing_fields.json");

    auto response = invoke_lambda(payload);
    json jsonResponse = json::parse(response.text);

    ASSERT_EQ(response.status_code, 200);
    ASSERT_EQ(jsonResponse["message"], "Good evening,  of . Happy !");
}

TEST_F(LambdaFunctionTest, MissingBodyField) {
    std::string payload = read_file("missing_body_field.json");

    auto response = invoke_lambda(payload);
    json jsonResponse = json::parse(response.text);

    ASSERT_EQ(response.status_code, 200);
    ASSERT_EQ(jsonResponse["message"], "Good , Alice of Los Angeles. Happy Friday!");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
