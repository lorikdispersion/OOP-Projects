#include "pch.h"

#include "HittableParser.hpp"

#include <crtdbg.h>

#include "SphereDTO.hpp"


class HittableParserTests : public ::testing::Test {
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

TEST_F(HittableParserTests, sphere)
{
    std::stringstream input("Sphere 1 2 3 4");
    HittableParser parser(' ');
    auto materialData = std::dynamic_pointer_cast<SphereDTO>(
        parser.parse(input));

    EXPECT_FLOAT_EQ(materialData->getX(), 1);
    EXPECT_FLOAT_EQ(materialData->getY(), 2);
    EXPECT_FLOAT_EQ(materialData->getZ(), 3);
    EXPECT_FLOAT_EQ(materialData->getRadius(), 4);
}