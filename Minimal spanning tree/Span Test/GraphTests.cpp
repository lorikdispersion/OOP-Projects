#include "pch.h"

#include "GraphExceptions.hpp"
#include "Graph.hpp"

class GraphBuilderTests : public ::testing::Test {
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

TEST_F(GraphBuilderTests, constructor)
{
    EXPECT_NO_THROW(Graph::Builder graphData());
    Graph::Builder graphData;
    EXPECT_EQ(graphData.countEdges(), 0);
    EXPECT_EQ(graphData.countVertices(), 0);
}

TEST_F(GraphBuilderTests, insert50Vertex)
{
    Graph::Builder graphData;
    for (size_t i = 0; i < 50; i++)
    {
        EXPECT_NO_THROW(graphData.insertVertex({ std::to_string(i), static_cast<double>(i), static_cast<double>(i) }));
    }
    EXPECT_EQ(graphData.countEdges(), 0);
    EXPECT_EQ(graphData.countVertices(), 50);
    for (size_t i = 0; i < 50; i++)
    {
        EXPECT_EQ(graphData.getVertices().find(std::to_string(i))->second, 
            Vertex( std::to_string(i), static_cast<double>(i), static_cast<double>(i) ));
    }
}

TEST_F(GraphBuilderTests, insertInvalidVertex)
{
    Graph::Builder graphData;
    EXPECT_NO_THROW(graphData.insertVertex({ std::to_string(1), static_cast<double>(1), static_cast<double>(1) }));
    EXPECT_THROW(graphData.insertVertex({ std::to_string(1), static_cast<double>(2), static_cast<double>(2) }),
                 BadVertex);
}

TEST_F(GraphBuilderTests, insertSameVertex)
{
    Graph::Builder graphData;
    EXPECT_NO_THROW(graphData.insertVertex({ std::to_string(1), static_cast<double>(1), static_cast<double>(1) }));
    EXPECT_NO_THROW(graphData.insertVertex({ std::to_string(1), static_cast<double>(1), static_cast<double>(1) }));
    EXPECT_EQ(1, graphData.countVertices());
}

TEST_F(GraphBuilderTests, insert45Edges)
{
    Graph::Builder graphData;
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = i+1; j < 10; j++)
        {
            EXPECT_NO_THROW(
	            graphData.insertEdge({ std::to_string(i), static_cast<double>(i), static_cast<double>(i) }, 
                    { std::to_string(j), static_cast<double>(j), static_cast<double>(j) }));
        }
    }
    EXPECT_EQ(graphData.countEdges(), 45);
    EXPECT_EQ(graphData.countVertices(), 10);
    for (size_t i = 0; i < 10; i++)
    {
        EXPECT_EQ(graphData.getVertices().find(std::to_string(i))->second,
            Vertex(std::to_string(i), static_cast<double>(i), static_cast<double>(i)));
    }
}

TEST_F(GraphBuilderTests, insertInvalidEdges)
{
    Graph::Builder graphData;
    EXPECT_NO_THROW(graphData.insertEdge({ std::to_string(1), static_cast<double>(1), static_cast<double>(1) },
        { std::to_string(2), static_cast<double>(2), static_cast<double>(2) }));
    EXPECT_THROW(graphData.insertEdge({ std::to_string(1), static_cast<double>(2), static_cast<double>(2) },
        { std::to_string(2), static_cast<double>(2), static_cast<double>(2) }), BadEdge);
    EXPECT_THROW(graphData.insertEdge({ std::to_string(1), static_cast<double>(1), static_cast<double>(1) },
        { std::to_string(2), static_cast<double>(3), static_cast<double>(3) }), BadEdge);
    EXPECT_THROW(graphData.insertEdge({ std::to_string(1), static_cast<double>(2), static_cast<double>(2) },
        { std::to_string(2), static_cast<double>(3), static_cast<double>(3) }), BadEdge);
}

TEST_F(GraphBuilderTests, insertSameEdges)
{
    Graph::Builder graphData;
    EXPECT_NO_THROW(graphData.insertEdge({ std::to_string(1), static_cast<double>(1), static_cast<double>(1) },
        { std::to_string(2), static_cast<double>(2), static_cast<double>(2) }));
    EXPECT_NO_THROW(graphData.insertEdge({ std::to_string(1), static_cast<double>(1), static_cast<double>(1) },
        { std::to_string(2), static_cast<double>(2), static_cast<double>(2) }));
    EXPECT_EQ(graphData.countVertices(), 2);
    EXPECT_EQ(graphData.countEdges(), 1);
}

TEST_F(GraphBuilderTests, constructGraphOn50Vertices)
{
    Graph::Builder graphData;
    for (size_t i = 0; i < 50; i++)
    {
        EXPECT_NO_THROW(graphData.insertVertex({ std::to_string(i), static_cast<double>(i), static_cast<double>(i) }));
    }
    Graph graph = graphData.createGraph();
    EXPECT_EQ(graph.countEdges(), 0);
    EXPECT_EQ(graph.countVertices(), 50);
    for (size_t i = 0; i < 50; i++)
    {
        EXPECT_EQ(graph.getVertices().find(std::to_string(i))->second,
            Vertex(std::to_string(i), static_cast<double>(i), static_cast<double>(i)));
    }
}

TEST_F(GraphBuilderTests, constructGraphOn45Edges)
{
    Graph::Builder graphData;
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = i + 1; j < 10; j++)
        {
            EXPECT_NO_THROW(
                graphData.insertEdge({ std::to_string(i), static_cast<double>(i), static_cast<double>(i) },
                    { std::to_string(j), static_cast<double>(j), static_cast<double>(j) }));
        }
    }
    Graph graph = graphData.createGraph();
    EXPECT_EQ(graph.countEdges(), 45);
    EXPECT_EQ(graph.countVertices(), 10);
    for (size_t i = 0; i < 10; i++)
    {
        EXPECT_EQ(graph.getVertices().find(std::to_string(i))->second,
            Vertex(std::to_string(i), static_cast<double>(i), static_cast<double>(i)));
    }
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = i + 1; j < 10; j++)
        {
            EXPECT_TRUE(graph.getEdges().contains({{ std::to_string(i), static_cast<double>(i), static_cast<double>(i) },
                    { std::to_string(j), static_cast<double>(j), static_cast<double>(j) } }));
        }
    }
}

TEST_F(GraphBuilderTests, constructGraphOn0Vertices)
{
    Graph::Builder graphData;
    Graph graph = graphData.createGraph();
    EXPECT_EQ(graph.countEdges(), 0);
    EXPECT_EQ(graph.countVertices(), 0);
}

TEST_F(GraphBuilderTests, constructGraphOn1Vertex)
{
    Graph::Builder graphData;
    graphData.insertVertex({ std::to_string(1), static_cast<double>(1), static_cast<double>(1) });
    const Graph graph = graphData.createGraph();
    EXPECT_EQ(graph.countEdges(), 0);
    EXPECT_EQ(graph.countVertices(), 1);
    EXPECT_EQ(graph.getVertices().find("1")->second, Vertex( std::to_string(1), 1, 1 ));
}

TEST_F(GraphBuilderTests, constructGraphOn1Edge)
{
    Graph::Builder graphData;
    graphData.insertEdge({std::to_string(1), static_cast<double>(1), static_cast<double>(1)}, 
						 {std::to_string(2), static_cast<double>(2), static_cast<double>(2)});
    const Graph graph = graphData.createGraph();
    EXPECT_EQ(graph.countEdges(), 1);
    EXPECT_EQ(graph.countVertices(), 2);
    EXPECT_TRUE(graph.getEdges().contains(Edge( Vertex( std::to_string(1), static_cast<double>(1), static_cast<double>(1) ),
        Vertex( std::to_string(2), static_cast<double>(2), static_cast<double>(2) ))));
}
