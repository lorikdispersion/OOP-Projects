#include "pch.h"

#include <crtdbg.h>

#include "ReadAllowed.hpp"
#include "ReadDenied.hpp"
#include "ReadAllowedByKey.hpp"
#include "ReadDeniedByKey.hpp"

class ReadAccessDelegateTests : public ::testing::Test {
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

TEST_F(ReadAccessDelegateTests, ReadAllowed) {
    ReadAllowed delegate{};
    EXPECT_TRUE(delegate.canRead(" "));
}

TEST_F(ReadAccessDelegateTests, ReadDenied) {
    ReadDenied delegate{};
    EXPECT_FALSE(delegate.canRead(" "));
}

TEST_F(ReadAccessDelegateTests, ReadAllowedByKey) {
    ReadAllowedByKey delegate{ {"1"} };
    EXPECT_TRUE(delegate.canRead("1"));
    EXPECT_FALSE(delegate.canRead("2"));
}

TEST_F(ReadAccessDelegateTests, ReadDeniedByKey) {
    ReadDeniedByKey delegate{ {"1"} };
    EXPECT_FALSE(delegate.canRead("1"));
    EXPECT_TRUE(delegate.canRead("2"));
}