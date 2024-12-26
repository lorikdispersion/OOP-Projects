#include "pch.h"

#include "Scene.hpp"

#include <crtdbg.h>

#include "Sky.hpp"
#include "Sphere.hpp"
#include "Lambertian.hpp"

class SceneTests : public ::testing::Test {
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

TEST_F(SceneTests, builder) {
    Scene::Builder builder(std::make_shared<Sky>());

    auto material_left = std::make_shared<Lambertian>(Attenuation(0, 0, 1));
    auto material_right = std::make_shared<Lambertian>(Attenuation(1, 0, 0));

    builder.add(std::make_shared<Sphere>(Vector3d(1, 0, -1), 1, material_left));
    builder.add(std::make_shared<Sphere>(Vector3d(1, 0, -1), 1, material_right));

    EXPECT_NO_THROW(builder.createScene());
}