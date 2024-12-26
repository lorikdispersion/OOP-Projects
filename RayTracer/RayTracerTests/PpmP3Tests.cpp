#include "pch.h"

#include "PpmP3.hpp"

#include <crtdbg.h>

class PpmP3Tests : public ::testing::Test {
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

TEST_F(PpmP3Tests, constructor)
{
    PpmP3::Builder builder(1, 1);
    builder.add(RGB256(255, 255, 255));
    EXPECT_NO_THROW(builder.createImage());
}
