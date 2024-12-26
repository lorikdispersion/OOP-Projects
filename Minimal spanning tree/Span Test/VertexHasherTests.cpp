#include "pch.h"
#include "VertexHasher.hpp"

class VertexHasherTest : public ::testing::Test {
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

TEST_F(VertexHasherTest, collisions_on_50_vertices)
{
	constexpr VertexHasher hasher;
    std::set<size_t> hashs;
	for(size_t i = 0; i < 50; i++)
	{
        hashs.insert(hasher.operator()({std::to_string(i), static_cast<double>(i), static_cast<double>(i) }));
	}
    hashs.insert(hasher.operator()({ "20", 20, 20 }));
    EXPECT_EQ(50, hashs.size());
}
