#include "pch.h"
#include "VertexData.hpp"

class VertexDataTest : public ::testing::Test {
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

TEST_F(VertexDataTest, constructor)
{
    EXPECT_NO_THROW(VertexData("1", 1, 1));
}

TEST_F(VertexDataTest, getId)
{
    const VertexData testVertex{ "1", 1, 1 };
    EXPECT_EQ("1", testVertex.getId());
}

TEST_F(VertexDataTest, getIdNull)
{
    const VertexData testVertex{ "", 1, 1 };
    EXPECT_EQ("", testVertex.getId());
}

TEST_F(VertexDataTest, getX)
{
    const VertexData testVertex{ "1", 1, 2 };
    EXPECT_EQ(1, testVertex.getX());
}

TEST_F(VertexDataTest, getY)
{
    const VertexData testVertex{ "1", 1, 2 };
    EXPECT_EQ(2, testVertex.getY());
}

