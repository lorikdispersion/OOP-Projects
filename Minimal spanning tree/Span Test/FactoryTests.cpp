#include "pch.h"

#include "CompleteGraphFactory.hpp"
#include "ParserExceptions.hpp"

class FactoryTests : public::testing::Test {
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

TEST_F(FactoryTests, constructor)
{
	EXPECT_NO_THROW(CompleteGraphFactory factory{ Parser{", "} });
}

TEST_F(FactoryTests, 0vertex)
{
	std::stringstream ssInput;
	std::stringstream ssOutput;
	CompleteGraphFactory factory{ Parser{ ", " } };
	EXPECT_THROW(auto completeGraph = factory.createGraph(ssInput), BadRow);
}

TEST_F(FactoryTests, 1vertex)
{
	std::stringstream ssInput;
	std::stringstream ssOutput;
	const CompleteGraphFactory factory{ Parser{ ", " } };
	std::size_t i = 0;
	for(; i <0; i++)
	{
		ssInput << i << ", " << i << ", " << i << "\n";
	}
	ssInput << i << ", " << i << ", " << i;
	const auto completeGraph = factory.createGraph(ssInput);
	EXPECT_EQ(0, completeGraph.countEdges());
	EXPECT_EQ(1, completeGraph.countVertices());
	for (std::size_t j = 0; j < 1; j++) {
		EXPECT_EQ(completeGraph.getVertices().find(std::to_string(j))->second,
			Vertex(std::to_string(j), static_cast<double>(j), static_cast<double>(j)));
	}
}

TEST_F(FactoryTests, 2vertex)
{
	std::stringstream ssInput;
	std::stringstream ssOutput;
	const CompleteGraphFactory factory{ Parser{ ", " } };
	std::size_t i = 0;
	for (; i < 1; i++)
	{
		ssInput << i << ", " << i << ", " << i << "\n";
	}
	ssInput << i << ", " << i << ", " << i;
	const auto completeGraph = factory.createGraph(ssInput);
	EXPECT_EQ(1, completeGraph.countEdges());
	EXPECT_EQ(2, completeGraph.countVertices());
	for (std::size_t j = 0; j < 2; j++) {
		EXPECT_EQ(completeGraph.getVertices().find(std::to_string(j))->second,
			Vertex(std::to_string(j), static_cast<double>(j), static_cast<double>(j)));
	}
	for (std::size_t i = 0; i < 2; i++)
	{
		for (std::size_t j = i + 1; j < 2; j++)
		{
			EXPECT_TRUE(completeGraph.getEdges().contains(
				Edge(Vertex(std::to_string(i), static_cast<double>(i), static_cast<double>(i)),
					Vertex(std::to_string(j), static_cast<double>(j), static_cast<double>(j)))));
		}
	}
}

TEST_F(FactoryTests, 100vertex)
{
	std::stringstream ssInput;
	std::stringstream ssOutput;
	const CompleteGraphFactory factory{ Parser{ ", " } };
	std::size_t i = 0;
	for (; i < 99; i++)
	{
		ssInput << i << ", " << i << ", " << i << "\n";
	}
	ssInput << i << ", " << i << ", " << i;
	const auto completeGraph = factory.createGraph(ssInput);
	EXPECT_EQ(4950, completeGraph.countEdges());
	EXPECT_EQ(100, completeGraph.countVertices());
	for (std::size_t j = 0; j < 100; j++) {
		EXPECT_EQ(completeGraph.getVertices().find(std::to_string(j))->second,
			Vertex(std::to_string(j), static_cast<double>(j), static_cast<double>(j)));
	}
	for (std::size_t i = 0; i < 100; i++)
	{
		for (std::size_t j = i+1; j < 100; j++)
		{
			EXPECT_TRUE(completeGraph.getEdges().contains(
				Edge(Vertex(std::to_string(i), static_cast<double>(i), static_cast<double>(i)), 
					 Vertex(std::to_string(j), static_cast<double>(j), static_cast<double>(j)))));
		}
	}
}
