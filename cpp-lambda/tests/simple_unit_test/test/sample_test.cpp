#include <gtest/gtest.h>
#include "sample.h"

TEST(SampleTest, TestAdd) {
    Sample sample;
    EXPECT_EQ(sample.Add(1, 1), 2);
    EXPECT_EQ(sample.Add(-1, 1), 0);
    EXPECT_EQ(sample.Add(-1, -1), -2);
}

TEST(SampleTest, TestSubtract) {
    Sample sample;
    EXPECT_EQ(sample.Subtract(1, 1), 0);
    EXPECT_EQ(sample.Subtract(-1, 1), -2);
    EXPECT_EQ(sample.Subtract(-1, -1), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
