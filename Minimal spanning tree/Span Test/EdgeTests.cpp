#include "pch.h"
#include "Edge.hpp"
#include "GraphExceptions.hpp"

class EdgeTest : public ::testing::Test {
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

TEST_F(EdgeTest, constructor)
{
    EXPECT_NO_THROW(Edge({ "1", 1, 1 }, {"2", 2, 2}));
    EXPECT_THROW(Edge({ "1", 1, 1 }, { "1", 2, 2 }), BadVertex);
}

TEST_F(EdgeTest, getLength)
{
    Edge edge({ "1", 0, 0 }, { "2", 3, 4 });
    EXPECT_EQ(5, edge.getLength());
}

TEST_F(EdgeTest, getVertices)
{
    Edge edge({ "1", 0, 0 }, { "2", 3, 4 });
    EXPECT_EQ(Vertex( "2", 3, 4 ), edge.getEndVertex());
    EXPECT_EQ(Vertex( "1", 0, 0), edge.getStartVertex());
    edge = Edge({ "1", 0, 0 }, { "2", 3, 4 });
    EXPECT_EQ(Vertex("2", 3, 4), edge.getEndVertex());
    EXPECT_EQ(Vertex("1", 0, 0), edge.getStartVertex());
}

TEST_F(EdgeTest, eqOperator)
{
    Edge testEdge1( { "1", 1, 1 },{"2", 1, 1});
    Edge testEdge2({ "1", 2, 1 }, { "2", 1, 2 });
    Edge testEdge3({ "1", 1, 1 }, { "2", 1, 1 });
    EXPECT_TRUE(testEdge1 == testEdge3);
    EXPECT_FALSE(testEdge2 == testEdge3);
}