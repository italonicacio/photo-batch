#include <gtest/gtest.h>

int Sum(int a, int b)
{
    return a + b;
}

TEST(SumTestSuite, TestSum)
{
    int r = Sum(2, 2);
    EXPECT_EQ(r, 4);
}

TEST(SumTestSuite, TestSum_zero)
{
    EXPECT_EQ(Sum(0, 0), 0);
    EXPECT_EQ(Sum(0, -0), 0);
    EXPECT_EQ(Sum(-0, 0), 0);
    EXPECT_EQ(Sum(-0, -0), 0);
}

TEST(SumTestSuite, TestSum_LargeNumbers)
{
    constexpr int maxInt = std::numeric_limits<int>::max();
    constexpr int minInt = std::numeric_limits<int>::min();

    EXPECT_EQ(Sum(maxInt, 1), minInt);
}