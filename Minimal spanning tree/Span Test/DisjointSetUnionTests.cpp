#include "pch.h"

#include "DisjointSetUnionExceptions.hpp"
#include "DisjointSetUnion.hpp"

class DisjointSetUnionTest : public ::testing::Test {
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

TEST_F(DisjointSetUnionTest, constructor)
{
    EXPECT_NO_THROW(DisjointSetUnion DSU{});
}

TEST_F(DisjointSetUnionTest, insertNewVertexParentPair)
{
    DisjointSetUnion DSU{};
    for (size_t i = 0; i < 50; i++)
    {
        EXPECT_NO_THROW(DSU.insertNewVertexToDeligate(
            { std::to_string(i), static_cast<double>(i), static_cast<double>(i) },
            { std::to_string(i), static_cast<double>(i), static_cast<double>(i) }));
    }
    for(auto it:DSU.getVerticesToDeligates())
    {
        EXPECT_EQ(it.first, it.second);
    }
    EXPECT_EQ(DSU.getVerticesToDeligates().size(), 50);
}

TEST_F(DisjointSetUnionTest, insertNewVertexParentPairAlreadyInserted)
{
    DisjointSetUnion DSU{};
    DSU.insertNewVertexToDeligate(
        { std::to_string(1), static_cast<double>(1), static_cast<double>(1) },
        { std::to_string(1), static_cast<double>(1), static_cast<double>(1) });
    EXPECT_THROW(DSU.insertNewVertexToDeligate(
        { std::to_string(1), static_cast<double>(1), static_cast<double>(1) },
        { std::to_string(2), static_cast<double>(2), static_cast<double>(2) }), VertexAlreadyInSet);
}

TEST_F(DisjointSetUnionTest, getPair)
{
    DisjointSetUnion DSU{};
    for (size_t i = 0; i < 50; i++)
    {
        EXPECT_NO_THROW(DSU.insertNewVertexToDeligate(
            { std::to_string(i), static_cast<double>(i), static_cast<double>(i) },
            { std::to_string(i), static_cast<double>(i), static_cast<double>(i) }));
    }
    for (size_t i = 0; i < 50; i++)
    {
        EXPECT_EQ(DSU.getParent({ std::to_string(i), static_cast<double>(i), static_cast<double>(i) }),
						  Vertex( std::to_string(i), static_cast<double>(i), static_cast<double>(i) ));
    }
}

TEST_F(DisjointSetUnionTest, getPairNotInserted)
{
    DisjointSetUnion DSU{};
    for (size_t i = 0; i < 50; i++)
    {
        EXPECT_NO_THROW(DSU.insertNewVertexToDeligate(
            { std::to_string(i), static_cast<double>(i), static_cast<double>(i) },
            { std::to_string(i), static_cast<double>(i), static_cast<double>(i) }));
    }
    EXPECT_THROW(DSU.getParent({ std::to_string(51), static_cast<double>(51), static_cast<double>(51) }), VertexNotInSet);
}

TEST_F(DisjointSetUnionTest, changeParent)
{
    DisjointSetUnion DSU{};
    for (size_t i = 0; i < 50; i++)
    {
        EXPECT_NO_THROW(DSU.insertNewVertexToDeligate(
            { std::to_string(i), static_cast<double>(i), static_cast<double>(i) },
            { std::to_string(i), static_cast<double>(i), static_cast<double>(i) }));
    }
    for (size_t i = 0; i < 50; i++)
    {
        EXPECT_NO_THROW(DSU.changeDeligate(
            { std::to_string(i), static_cast<double>(i), static_cast<double>(i) },
            { std::to_string(i+1), static_cast<double>(i+1), static_cast<double>(i+1) }));
    }
    for (size_t i = 0; i < 50; i++)
    {
        EXPECT_EQ(DSU.getParent({ std::to_string(i), static_cast<double>(i), static_cast<double>(i) }),
            Vertex(std::to_string(i+1), static_cast<double>(i+1), static_cast<double>(i+1)));
    }
}

TEST_F(DisjointSetUnionTest, changeParentNotInserted)
{
    DisjointSetUnion DSU{};
    for (size_t i = 0; i < 50; i++)
    {
        EXPECT_NO_THROW(DSU.insertNewVertexToDeligate(
            { std::to_string(i), static_cast<double>(i), static_cast<double>(i) },
            { std::to_string(i), static_cast<double>(i), static_cast<double>(i) }));
    }
    EXPECT_THROW(DSU.changeDeligate(
        { std::to_string(51), static_cast<double>(51), static_cast<double>(51) },
        { std::to_string(1), static_cast<double>(1), static_cast<double>(1) }), VertexNotInSet);
}