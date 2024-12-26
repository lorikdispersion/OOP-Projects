#include "pch.h"

#include "ParserExceptions.hpp"
#include "Parser.hpp"

class ParserTest : public ::testing::Test {
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

TEST_F(ParserTest, constructor)
{
	EXPECT_NO_THROW(const Parser parser{ ", " });
	EXPECT_NO_THROW(const Parser parser{ "" });
	EXPECT_NO_THROW(const Parser parser{ " " });
	EXPECT_NO_THROW(const Parser parser{ "\n" });
}

TEST_F(ParserTest, oneRow)
{
	std::stringstream string{ "1, 2.25, 3" };
	const Parser parser{ ", " };
	const VertexData obj = parser.createVertexDataFromStream(string);
	EXPECT_EQ("1", obj.getId());
	EXPECT_EQ(2.25, obj.getX());
	EXPECT_EQ(3, obj.getY());
}

TEST_F(ParserTest, twoRows)
{
	std::stringstream string{ "1, 2, 3\n4, 5, 6" };
	const Parser parser{ ", " };
	VertexData obj = parser.createVertexDataFromStream(string);
	EXPECT_EQ("1", obj.getId());
	EXPECT_EQ(2, obj.getX());
	EXPECT_EQ(3, obj.getY());
	obj = parser.createVertexDataFromStream(string);
	EXPECT_EQ("4", obj.getId());
	EXPECT_EQ(5, obj.getX());
	EXPECT_EQ(6, obj.getY());
}

TEST_F(ParserTest, nullRow)
{
	std::stringstream string{ "" };
	const Parser parser{ ", " };
	EXPECT_THROW(parser.createVertexDataFromStream(string), BadRow);
}

TEST_F(ParserTest, choppedOffRow)
{
	std::stringstream string{ "1, 1" };
	const Parser parser{ ", " };
	EXPECT_THROW(parser.createVertexDataFromStream(string), BadRow);
}

TEST_F(ParserTest, saying)
{
	std::stringstream string{ "Ad astra per aspera" };
	const Parser parser{ " " };
	EXPECT_THROW(parser.createVertexDataFromStream(string), BadRow);
}