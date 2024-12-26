#include "pch.h"
#include "EdgeLengthComparator.hpp"

class EdgesLengthComparatorTest : public ::testing::Test {
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

TEST_F(EdgesLengthComparatorTest, setOnLengthComparator)
{
    std::set<Edge, EdgesLengthComparator> edges;
    for (size_t i = 51; i > 1; i--)
    {
        edges.insert({ { std::to_string(200 - i), static_cast<double>(200 - i), static_cast<double>(200 - i) },
                              { std::to_string(i), static_cast<double>(i), static_cast<double>(i)} });
    }
    for(auto it = edges.begin(); it != edges.end(); ++it)
    {
		for(auto jt = std::next(it); jt != edges.end(); ++jt)
		{
            EXPECT_LE(it->getLength(), jt->getLength());
		}
    }
    EXPECT_EQ(50, edges.size());
}
