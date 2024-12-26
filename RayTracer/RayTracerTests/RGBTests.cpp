#include "pch.h"

#include "RGB256.hpp"

#include <crtdbg.h>

class RGBTests : public ::testing::Test {
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

TEST_F(RGBTests, Attenuation) {
    EXPECT_ANY_THROW(Attenuation(256, 0, 0));
    EXPECT_ANY_THROW(Attenuation(0, 256, 0));
    EXPECT_ANY_THROW(Attenuation(0, 0, 256));
    EXPECT_ANY_THROW(Attenuation(-256, 0, 0));
    EXPECT_ANY_THROW(Attenuation(0, -256, 0));
    EXPECT_ANY_THROW(Attenuation(0, 0, -256));
}

TEST_F(RGBTests, constructor) {
    EXPECT_ANY_THROW(RGB256(256, 0 ,0));
    EXPECT_ANY_THROW(RGB256(0, 256, 0));
    EXPECT_ANY_THROW(RGB256(0, 0, 256));
}

TEST_F(RGBTests, multWithAttenuation) {
    RGB256 color(200, 200, 200);
    color = color * Attenuation(0.9f, 0.8f, 0.7f);
    EXPECT_EQ(color.r(), 180);
    EXPECT_EQ(color.g(), 160);
    EXPECT_EQ(color.b(), 140);
}

TEST_F(RGBTests, gammaCorrection) {
    RGB256 color(200, 150, 100);
    color = color.gammaCorrection(0.5);
    EXPECT_EQ(color.r(), 226);
    EXPECT_EQ(color.g(), 195);
    EXPECT_EQ(color.b(), 160);
}