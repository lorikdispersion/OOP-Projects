#include "pch.h"

#include "MaterialParser.hpp"
#include "MaterialFactory.hpp"

#include <crtdbg.h>

#include "Dielectric.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"

class MaterialFactoryTests : public ::testing::Test {
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

TEST_F(MaterialFactoryTests, dielectric)
{
    std::stringstream input("Dielectric 1.5");
    MaterialParser parser(' ');

    EXPECT_NO_THROW(auto materialPtr = std::dynamic_pointer_cast<Dielectric>(
        MaterialFactory::createMaterial(parser, input)));
}

TEST_F(MaterialFactoryTests, lambertian)
{
    std::stringstream input("Lambertian 0.3 0.2 0.1");
    MaterialParser parser(' ');

    EXPECT_NO_THROW(auto materialPtr = std::dynamic_pointer_cast<Lambertian>(
        MaterialFactory::createMaterial(parser, input)));
}

TEST_F(MaterialFactoryTests, metal)
{
    std::stringstream input("Metal 0.3 0.2 0.1 1");
    MaterialParser parser(' ');

    EXPECT_NO_THROW(auto materialPtr = std::dynamic_pointer_cast<Metal>(
        MaterialFactory::createMaterial(parser, input)));
}