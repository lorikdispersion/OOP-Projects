#include "pch.h"

#include "RayTracer.hpp"

#include <crtdbg.h>
#include <sstream>

#include "Lambertian.hpp"
#include "Sky.hpp"
#include "Sphere.hpp"

class RayTracerTests : public ::testing::Test {
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

TEST_F(RayTracerTests, constructor)
{
    std::stringstream progressBar;

    Scene::Builder builder(std::make_shared<Sky>());

    auto material_left = std::make_shared<Lambertian>(Attenuation(0, 0, 1));
    auto material_right = std::make_shared<Lambertian>(Attenuation(1, 0, 0));

    builder.add(std::make_shared<Sphere>(Vector3d(1, 0, -1), 1, material_left));
    builder.add(std::make_shared<Sphere>(Vector3d(1, 0, -1), 1, material_right));
    auto world = builder.createScene();

    Camera camera({ 1,1,1 }, { 0, 0,0 },
        { 0, 1, 0 }, 1, 1, 0.1f, 10);

    EXPECT_NO_THROW(RayTracer::createImage(progressBar, world, 1, 1, camera, 10, 10, 0.5f));
}
