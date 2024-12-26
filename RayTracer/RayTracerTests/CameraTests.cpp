#include "pch.h"

#include "Camera.hpp"

#include <crtdbg.h>

class CameraTests : public ::testing::Test {
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

TEST_F(CameraTests, constructor) {
    EXPECT_ANY_THROW(Camera({ 1,1,1 }, { 0, 0,0 }, { 0, 1, 0 }, -1, 1, 0.1f, 10));
    EXPECT_ANY_THROW(Camera({ 1,1,1 }, { 0, 0,0 }, { 0, 1, 0 }, 1, -1, 0.1f, 10));
    EXPECT_ANY_THROW(Camera({ 1,1,1 }, { 0, 0,0 }, { 0, 1, 0 }, 1, 1, -0.1f, 10));
    EXPECT_ANY_THROW(Camera({ 1,1,1 }, { 0, 0,0 }, { 0, 1, 0 }, 1, 1, 0.1f, -10));
}