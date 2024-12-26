#include "pch.h"

#include "Ray.hpp"

#include <crtdbg.h>

class RayTests : public ::testing::Test {
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

TEST_F(RayTests, at) {
    Ray ray({ 0, 0, 0 }, { 1, 1, 1 });
    EXPECT_EQ(ray.at(2), Vector3d(2, 2, 2));
}