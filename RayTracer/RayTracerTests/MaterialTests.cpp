#include "pch.h"

#include "Lambertian.hpp"
#include "Metal.hpp"
#include "Dielectric.hpp"

#include <crtdbg.h>

class MaterialTests : public ::testing::Test {
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

TEST_F(MaterialTests, dielectric) {
    Vector3d normal(1, 1, 1);
    Ray ray({ 0, 0 ,0 }, { -3, 7, 7 });
    auto point = ray.at(1);
    auto material = std::make_shared<Dielectric>(1.5f);

    EXPECT_NO_THROW(auto scatterOptional = material->scatter(HitRecord(
        point, normal, ray, 1, material, true)));
}

TEST_F(MaterialTests, metal) {
    Vector3d normal(1, 1, 1);
    Ray ray({ 0, 0 ,0 }, { -3, 7, 7 });
    auto point = ray.at(1);
    auto material = std::make_shared<Metal>(Attenuation(0.5, 0.5, 0.5), 0.5);

    EXPECT_NO_THROW(material->scatter(HitRecord(
	    point, normal, ray, 1, material, true)));
}

TEST_F(MaterialTests, lambertian) {
    Vector3d normal(1, 1, 1);
    Ray ray({ 0, 0 ,0 }, { -3, 7, 7 });
    auto point = ray.at(1);
    auto material = std::make_shared<Lambertian>(Attenuation(0.5, 0.5, 0.5));

    EXPECT_NO_THROW(auto scatterOptional = material->scatter(HitRecord(
        point, normal, ray, 1, material, true)));
}