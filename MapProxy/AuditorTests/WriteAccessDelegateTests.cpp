#include "pch.h"

#include <crtdbg.h>

#include "WriteAllowed.hpp"
#include "WriteDenied.hpp"
#include "WriteAllowedByKey.hpp"
#include "WriteDeniedByKey.hpp"

class WriteAccessDelegateTests : public ::testing::Test {
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

TEST_F(WriteAccessDelegateTests, WriteAllowed) {
	WriteAllowed delegate{};
	EXPECT_TRUE(delegate.canWrite(" "));
}

TEST_F(WriteAccessDelegateTests, WriteDenied) {
	WriteDenied delegate{};
	EXPECT_FALSE(delegate.canWrite(" "));
}

TEST_F(WriteAccessDelegateTests, WriteAllowedByKey) {
	WriteAllowedByKey delegate{ {"1"} };
	EXPECT_TRUE(delegate.canWrite("1"));
	EXPECT_FALSE(delegate.canWrite("2"));
}

TEST_F(WriteAccessDelegateTests, WriteDeniedByKey) {
	WriteDeniedByKey delegate{ {"1"} };
	EXPECT_FALSE(delegate.canWrite("1"));
	EXPECT_TRUE(delegate.canWrite("2"));
}