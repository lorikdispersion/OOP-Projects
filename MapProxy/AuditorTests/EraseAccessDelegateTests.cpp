#include "pch.h"

#include <crtdbg.h>

#include "EraseAllowed.hpp"
#include "EraseDenied.hpp"
#include "EraseAllowedByKey.hpp"
#include "EraseDeniedByKey.hpp"

class EraseAccessDelegateTests : public ::testing::Test {
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

TEST_F(EraseAccessDelegateTests, EraseAllowed) {
    EraseAllowed delegate{};
    EXPECT_TRUE(delegate.canErase(" "));
}

TEST_F(EraseAccessDelegateTests, EraseDenied) {
    EraseDenied delegate{};
    EXPECT_FALSE(delegate.canErase(" "));
}

TEST_F(EraseAccessDelegateTests, EraseAllowedByKey) {
    EraseAllowedByKey delegate{ {"1"} };
    EXPECT_TRUE(delegate.canErase("1"));
    EXPECT_FALSE(delegate.canErase("2"));
}

TEST_F(EraseAccessDelegateTests, EraseDeniedByKey) {
    EraseDeniedByKey delegate{ {"1"} };
    EXPECT_FALSE(delegate.canErase("1"));
    EXPECT_TRUE(delegate.canErase("2"));
}