#include "pch.h"
#include "EdgeHasher.hpp"

class EdgesHasherTest : public ::testing::Test {
protected:
    virtual void SetUp(void) {
        _CrtMemCheckpoint(&startup);
    }
    virtual void TearDown(void) {
        _CrtMemState teardown, diff;
        _CrtMemCheckpoint(&teardown);
        ASSERT_EQ(0, _CrtMemDifference(&diff, &startup, &teardown)) << "Memory leaks detected";
    }
    _CrtMemState startup;
};

TEST_F(EdgesHasherTest, collisions_on_50_edges)
{
    constexpr EdgeHasher hasher;
    std::set<size_t> hashs;
    for (size_t i = 1; i < 51; i++)
    {
        hashs.insert(hasher.operator()(
            { { std::to_string(-1*i), static_cast<double>(-1 * i), static_cast<double>(-1 * i) },
					          { std::to_string(i), static_cast<double>(i), static_cast<double>(i)} }));
    }
    EXPECT_EQ(50, hashs.size());
}
