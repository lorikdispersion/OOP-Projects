#include "pch.h"

#include <crtdbg.h> // Windows only

#include "WithReplacement.hpp"
#include "WithoutReplacement.hpp"

class ReplacementDelegateTests : public ::testing::Test {
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

TEST_F(ReplacementDelegateTests, WithReplacement) {
    WithReplacement delegate{ {{"1", "a"}} };
    EXPECT_EQ(delegate.getFakeValue("1", "b"), "a");
    EXPECT_EQ(delegate.getFakeValue("2", "b"), "b");
}

TEST_F(ReplacementDelegateTests, WithoutReplacement) {
    WithoutReplacement delegate{};
    EXPECT_EQ(delegate.getFakeValue("1", "a"), "a");
}