#include "pch.h"

#include "MaterialParser.hpp"

#include <crtdbg.h>

#include "DielectricDTO.hpp"
#include "LambertianDTO.hpp"
#include "MetalDTO.hpp"

class MaterialParserTests : public ::testing::Test {
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

TEST_F(MaterialParserTests, dielectric)
{
    std::stringstream input("Dielectric 1.5");
    MaterialParser parser(' ');
    auto materialData = std::dynamic_pointer_cast<DielectricDTO>(
        parser.parse(input));

    EXPECT_FLOAT_EQ(materialData->getRefractionIndex(), 1.5);
}

TEST_F(MaterialParserTests, lambertian)
{
    std::stringstream input("Lambertian 0.3 0.2 0.1");
    MaterialParser parser(' ');
    auto materialData = std::dynamic_pointer_cast<LambertianDTO>(
        parser.parse(input));

    EXPECT_FLOAT_EQ(materialData->getAlbedoR(), 0.3f);
    EXPECT_FLOAT_EQ(materialData->getAlbedoG(), 0.2f);
    EXPECT_FLOAT_EQ(materialData->getAlbedoB(), 0.1f);
}

TEST_F(MaterialParserTests, metal)
{
    std::stringstream input("Metal 0.3 0.2 0.1 1");
    MaterialParser parser(' ');
    auto materialData = std::dynamic_pointer_cast<MetalDTO>(
        parser.parse(input));

    EXPECT_FLOAT_EQ(materialData->getAlbedoR(), 0.3f);
    EXPECT_FLOAT_EQ(materialData->getAlbedoG(), 0.2f);
    EXPECT_FLOAT_EQ(materialData->getAlbedoB(), 0.1f);

    EXPECT_FLOAT_EQ(materialData->getFuzz(), 1);
}