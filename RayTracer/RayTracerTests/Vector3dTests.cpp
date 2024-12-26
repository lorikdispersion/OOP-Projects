#include "pch.h"

#include "Vector3d.hpp"

#include <crtdbg.h>

class Vector3dTests : public ::testing::Test {
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

TEST_F(Vector3dTests, getters) {
    Vector3d vec;
    EXPECT_NO_THROW(vec = Vector3d( 1, 2, 3 ));
    EXPECT_EQ(vec.x(), 1);
    EXPECT_EQ(vec.y(), 2);
    EXPECT_EQ(vec.z(), 3);
}

TEST_F(Vector3dTests, randomVectors) {
    Vector3d vec;
    EXPECT_NO_THROW(vec = Vector3d::randomVector());
    EXPECT_LE(vec.x(), 1);
    EXPECT_LE(vec.y(), 1);
    EXPECT_LE(vec.z(), 1);

    EXPECT_NO_THROW(vec = Vector3d::randomVector(1, 2));
    EXPECT_LE(vec.x(), 2);
    EXPECT_LE(vec.y(), 2);
    EXPECT_LE(vec.z(), 2);

    EXPECT_NO_THROW(vec = Vector3d::randomVectorInUnitDisk(Vector3d(0, 0, 1)));
    EXPECT_LE(vec.x(), 1);
    EXPECT_LE(vec.y(), 1);
    EXPECT_EQ(vec.z(), 0);

    EXPECT_NO_THROW(vec = Vector3d::randomVectorInUnitSphere());
    EXPECT_LE(vec.length(),1 + FLT_EPSILON);
}

TEST_F(Vector3dTests, dot) {
    Vector3d vec1(1, 2, 0);
    Vector3d vec2(1, 4, 5);
    EXPECT_EQ(Vector3d::dot(vec1, vec2), 9);
}

TEST_F(Vector3dTests, cross) {
    Vector3d vec1(1, 0, 0);
    Vector3d vec2(0, 1, 0);
    EXPECT_EQ(Vector3d::cross(vec1, vec2), Vector3d(0, 0, 1));
}

TEST_F(Vector3dTests, lenght) {
    Vector3d vec(3, 4, 0);
    EXPECT_EQ(vec.length(), 5);
    EXPECT_EQ(vec.lengthSquared(), 25);
}

TEST_F(Vector3dTests, unitVector) {
    Vector3d vec(3, 4, 0);
    EXPECT_EQ(vec.length(), 5);
    EXPECT_EQ(vec.lengthSquared(), 25);
    vec = Vector3d::unitVector(vec);
    EXPECT_NE(vec.x(), 0);
    EXPECT_NE(vec.y(), 0);
    EXPECT_EQ(vec.length(), 1);
    EXPECT_EQ(vec.lengthSquared(), 1);
}

TEST_F(Vector3dTests, reflect) {
    Vector3d vec(1, 1, 0);
    Vector3d normal(0, 1, 0);
    Vector3d reflectedVec = Vector3d::reflect(vec, normal);

    EXPECT_EQ(reflectedVec.x(), 1);
    EXPECT_EQ(reflectedVec.y(), -1);
    EXPECT_EQ(reflectedVec.z(), 0);
}