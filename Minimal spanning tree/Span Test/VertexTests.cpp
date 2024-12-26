#include "pch.h"
#include "Vertex.hpp"

class VertexTest : public ::testing::Test {
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

TEST_F(VertexTest, constructor)
{
    EXPECT_NO_THROW(Vertex( "1", 1, 1));
}

TEST_F(VertexTest, getId)
{
    Vertex testVertex{ "1", 1, 1 };
    EXPECT_EQ("1", testVertex.getId());
}

TEST_F(VertexTest, getIdNull)
{
    Vertex testVertex{ "", 1, 1 };
    EXPECT_EQ("", testVertex.getId());
}

TEST_F(VertexTest, getX)
{
    Vertex testVertex{ "1", 1, 2 };
    EXPECT_EQ(1, testVertex.getX());
}

TEST_F(VertexTest, getY)
{
    Vertex testVertex{ "1", 1, 2 };
    EXPECT_EQ(2, testVertex.getY());
}

TEST_F(VertexTest, eqOperator)
{
    Vertex testVertex1{ "1", 1, 2 };
    Vertex testVertex2{ "1", 2, 1 };
    Vertex testVertex3{ "1", 1, 2 };
    Vertex testVertex4{ "1", 1.0, 2.0 };
    Vertex testVertex5{ "1", 2.0, 1.0 };
    Vertex testVertex6{ "1", 1.0, 2.0 };
    Vertex testVertex7{ "2", 1, 2 };
    EXPECT_TRUE(testVertex1 == testVertex1);
    EXPECT_TRUE(testVertex4 == testVertex4);
    EXPECT_TRUE(testVertex1 == testVertex3);
    EXPECT_TRUE(testVertex4 == testVertex6);
    EXPECT_TRUE(testVertex1 == testVertex4);
    EXPECT_FALSE(testVertex1 == testVertex2);
    EXPECT_FALSE(testVertex1 == testVertex7);
}
