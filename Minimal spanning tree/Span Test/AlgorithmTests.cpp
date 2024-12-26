#include "pch.h"

#include "CompleteGraphFactory.hpp"
#include "GraphsEdgesPrinter.hpp"
#include "KruskalsAlgorithm.hpp"

class AlgorithmTests : public ::testing::Test {
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


TEST_F(AlgorithmTests, constructor)
{
    EXPECT_NO_THROW(KruskalsAlgorithm algorithm);
}

TEST_F(AlgorithmTests, createSpanningTreeOn0Vertices)
{
    KruskalsAlgorithm algorithm;
    Graph::Builder graphData;
    Graph graph = graphData.createGraph();
    Graph span = algorithm.createSpanningTree(graph);
    EXPECT_EQ(span.countEdges(), 0);
    EXPECT_EQ(span.countVertices(), 0);
}

TEST_F(AlgorithmTests, createSpanningTreeOn1Vertex)
{
    KruskalsAlgorithm algorithm;
    Graph::Builder graphData;
    graphData.insertVertex({ "1", 1, 1 });
    Graph graph = graphData.createGraph();
    Graph span = algorithm.createSpanningTree(graph);
    EXPECT_EQ(span.countEdges(), 0);
    EXPECT_EQ(span.countVertices(), 1);
    EXPECT_EQ(span.getVertices().find("1")->second, Vertex("1", 1, 1));
}

TEST_F(AlgorithmTests, createSpanningTreeOn1Edge)
{
    KruskalsAlgorithm algorithm;
    Graph::Builder graphData;
    graphData.insertEdge({ "1", 1, 1 }, { "2", 2, 2 });
    Graph graph = graphData.createGraph();
    Graph span = algorithm.createSpanningTree(graph);
    EXPECT_EQ(span.countEdges(), 1);
    EXPECT_EQ(span.countVertices(), 2);
    EXPECT_TRUE(span.getEdges().contains({ { "1", 1, 1 }, { "2", 2, 2 } }));
}

TEST_F(AlgorithmTests, createSpanningTreeOn4VertexLine)
{
    std::stringstream ssInput, ssOutput;
    CompleteGraphFactory factory{ Parser{", "} };
    KruskalsAlgorithm algorithm;
    ssInput << "1, 0, 0\n2, 1, 0\n3, 3, 0\n4, 4, 0";
    const auto graph = factory.createGraph(ssInput);
    const auto span = algorithm.createSpanningTree(graph);
    EXPECT_EQ(span.getEdges().size(), 3);
    EXPECT_EQ(span.getVertices().size(), 4);
    GraphEdgesPrinter::printToStream(span, ssOutput);
    EXPECT_EQ("1 - 2\n3 - 4\n2 - 3\n", ssOutput.str());
}

TEST_F(AlgorithmTests, createSpanningTreeOnSquare)
{
    std::stringstream ssInput, ssOutput;
    CompleteGraphFactory factory{ Parser{", "} };
    KruskalsAlgorithm algorithm;
    ssInput << "1, 1, 1\n2, -1, 1\n3, -1, -1\n4, 1, -1";
    const auto graph = factory.createGraph(ssInput);
    const auto span = algorithm.createSpanningTree(graph);
    EXPECT_EQ(span.getEdges().size(), 3);
    EXPECT_EQ(span.getVertices().size(), 4);
    GraphEdgesPrinter::printToStream(span, ssOutput);
    EXPECT_EQ("1 - 2\n2 - 3\n3 - 4\n", ssOutput.str());
}

TEST_F(AlgorithmTests, createSpanningTreeOn6Vertices)
{
    std::stringstream ssInput, ssOutput;
    CompleteGraphFactory factory{ Parser{", "} };
    KruskalsAlgorithm algorithm;
	ssInput << "1, 1, 1\n2, 2, 5\n3, -2, 2\n4, -1, 10\n5, 5, -3\n6, 3, 0";
	const auto graph = factory.createGraph(ssInput);
	const auto span = algorithm.createSpanningTree(graph);
	EXPECT_EQ(span.getEdges().size(), 5);
	EXPECT_EQ(span.getVertices().size(), 6);
	GraphEdgesPrinter::printToStream(span, ssOutput);
	EXPECT_EQ("1 - 6\n1 - 2\n1 - 3\n5 - 6\n2 - 4\n", ssOutput.str());
}

TEST_F(AlgorithmTests, createSpanningTreeOnManyVertices)
{
    std::stringstream ssInput, ssOutput;
    CompleteGraphFactory factory{ Parser{", "} };
    KruskalsAlgorithm algorithm;

    std::size_t tag = 0;
    for(double i = 1; i < 4; i += 0.25)
    {
        ssInput << tag << ", " << i << ", " << i << "\n";
        tag++;
        ssInput << tag << ", " << -i << ", " << i << "\n";
        tag++;
        ssInput << tag << ", " << i << ", " << -i << "\n";
        tag++;
        ssInput << tag << ", " << -i << ", " << -i << "\n";
        tag++;
    }
    ssInput << 50 << ", " << 6 << ", " << 6;
    Graph graph = factory.createGraph(ssInput);
    const auto span = algorithm.createSpanningTree(graph);
    EXPECT_EQ(span.getEdges().size(), 48);
    EXPECT_EQ(span.getVertices().size(), 49);
    GraphEdgesPrinter::printToStream(span, ssOutput);
    EXPECT_EQ("20 - 24\n35 - 39\n10 - 14\n33 - 37\n3 - 7\n42 - 46\n22 - 26\n27 - 31\n37 - 41\n39 - 43\n13 - 9\n11 - 7\n0 - 4\n32 - 36\n4 - 8\n21 - 25\n34 - 38\n43 - 47\n11 - 15\n23 - 27\n38 - 42\n36 - 40\n2 - 6\n30 - 34\n1 - 5\n24 - 28\n5 - 9\n14 - 18\n0 - 2\n40 - 44\n31 - 35\n10 - 6\n12 - 8\n41 - 45\n25 - 29\n29 - 33\n28 - 32\n26 - 30\n16 - 20\n18 - 22\n12 - 16\n13 - 17\n15 - 19\n17 - 21\n19 - 23\n0 - 1\n1 - 3\n44 - 50\n", ssOutput.str());
}