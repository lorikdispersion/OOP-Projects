#include "pch.h"

#include "HittableFactory.hpp"

#include <crtdbg.h>

#include "SphereDTO.hpp"
#include "Lambertian.hpp"

class HittableFactoryTests : public ::testing::Test {
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

TEST_F(HittableFactoryTests, sphere)
{
    std::stringstream input("Sphere 1 2 3 4");
    HittableParser parser(' ');

    auto materialPtr = std::make_shared<Lambertian>(Attenuation(0, 0, 1));

    EXPECT_NO_THROW(auto object = HittableFactory::createHittable(
        parser, input, materialPtr));

}