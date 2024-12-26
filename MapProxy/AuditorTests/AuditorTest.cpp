#include "pch.h"

#include <crtdbg.h> // Windows only

#include "AuditorWith4Delegates.hpp"
#include "AuditorExpections.hpp"

#include "ReadAccessDelegate.hpp"
#include "WriteAccessDelegate.hpp"
#include "EraseAccessDelegate.hpp"
#include "ReplacementDelegate.hpp"

#include "ReadAllowed.hpp"
#include "WriteAllowed.hpp"
#include "EraseAllowed.hpp"
#include "WithoutReplacement.hpp"


class DummyReadDelegate : public ReadAccessDelegate
{
    bool flag_ = false;
public:
    [[nodiscard]] bool canRead(const std::string& key) override { flag_ = true; return true; }
    [[nodiscard]] bool getFlag() const noexcept { return flag_; }
};

class DummyWriteDelegate : public WriteAccessDelegate
{
    bool flag_ = false;
public:
    [[nodiscard]] bool canWrite(const std::string& key) override { flag_ = true; return true; }
    [[nodiscard]] bool getFlag() const noexcept { return flag_; }
};

class DummyEraseDelegate : public EraseAccessDelegate
{
    bool flag_ = false;
public:
    [[nodiscard]] bool canErase(const std::string& key) override { flag_ = true; return true; }
    [[nodiscard]] bool getFlag() const noexcept { return flag_; }
};

class DummyReplacementDelegate : public ReplacementDelegate
{
    bool flag_ = false;
public:
    [[nodiscard]] const std::string& getFakeValue(
        const std::string& key, const std::string& value) override {
        flag_ = true;
        return value;
    }
    [[nodiscard]] bool getFlag() const noexcept { return flag_; }
};

class AuditorTests : public ::testing::Test {
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


TEST_F(AuditorTests, constructor) {
    EXPECT_NO_THROW(AuditorWith4Delegates(
        std::make_unique_for_overwrite<ReadAllowed>(),
        std::make_unique_for_overwrite<WriteAllowed>(),
        std::make_unique_for_overwrite<EraseAllowed>(),
        std::make_unique_for_overwrite<WithoutReplacement>()));
}

TEST_F(AuditorTests, constructorNullReadDelegate) {
    EXPECT_THROW(AuditorWith4Delegates(
        std::unique_ptr<ReadAllowed>(nullptr),
        std::make_unique_for_overwrite<WriteAllowed>(),
        std::make_unique_for_overwrite<EraseAllowed>(),
        std::make_unique_for_overwrite<WithoutReplacement>()),
        NullPtrReadAccessDelegate);
}

TEST_F(AuditorTests, constructorNullWriteDelegate) {
    EXPECT_THROW(AuditorWith4Delegates(
        std::make_unique_for_overwrite<ReadAllowed>(),
        std::unique_ptr<WriteAllowed>(nullptr),
        std::make_unique_for_overwrite<EraseAllowed>(),
        std::make_unique_for_overwrite<WithoutReplacement>()),
        NullPtrWriteAccessDelegate);
}
TEST_F(AuditorTests, constructorNullEraseDelegate) {
    EXPECT_THROW(AuditorWith4Delegates(
        std::make_unique_for_overwrite<ReadAllowed>(),
        std::make_unique_for_overwrite<WriteAllowed>(),
        std::unique_ptr<EraseAllowed>(nullptr),
        std::make_unique_for_overwrite<WithoutReplacement>()),
        NullPtrEraseAccessDelegate);
}
TEST_F(AuditorTests, constructorNullReplacementDelegate) {
    EXPECT_THROW(AuditorWith4Delegates(
        std::make_unique_for_overwrite<ReadAllowed>(),
        std::make_unique_for_overwrite<WriteAllowed>(),
        std::make_unique_for_overwrite<EraseAllowed>(),
        std::unique_ptr<WithoutReplacement>(nullptr)),
        NullPtrReplacementDelegate);
}

TEST_F(AuditorTests, dummyDelegates) {
	auto readDelegate = new DummyReadDelegate;
    auto writeDelegate = new DummyWriteDelegate;
    auto eraseDelegate = new DummyEraseDelegate;
    auto replacementDelegate = new DummyReplacementDelegate;

    AuditorWith4Delegates auditor{ std::unique_ptr<ReadAccessDelegate>(readDelegate),
		std::unique_ptr<WriteAccessDelegate>(writeDelegate),
		std::unique_ptr<EraseAccessDelegate>(eraseDelegate),
		std::unique_ptr<ReplacementDelegate>(replacementDelegate) };

    EXPECT_FALSE(readDelegate->getFlag());
    EXPECT_FALSE(writeDelegate->getFlag());
    EXPECT_FALSE(eraseDelegate->getFlag());
    EXPECT_FALSE(replacementDelegate->getFlag());

    EXPECT_TRUE(auditor.canErase(""));
    EXPECT_FALSE(readDelegate->getFlag());
    EXPECT_FALSE(writeDelegate->getFlag());
    EXPECT_TRUE(eraseDelegate->getFlag());
    EXPECT_FALSE(replacementDelegate->getFlag());


    EXPECT_TRUE(auditor.canRead(""));
    EXPECT_TRUE(readDelegate->getFlag());
    EXPECT_FALSE(writeDelegate->getFlag());
    EXPECT_TRUE(eraseDelegate->getFlag());
    EXPECT_FALSE(replacementDelegate->getFlag());

    EXPECT_TRUE(auditor.canWrite(""));
    EXPECT_TRUE(readDelegate->getFlag());
    EXPECT_TRUE(writeDelegate->getFlag());
    EXPECT_TRUE(eraseDelegate->getFlag());
    EXPECT_FALSE(replacementDelegate->getFlag());

    EXPECT_EQ(auditor.replaceValue("1", "a"), "a");
    EXPECT_TRUE(readDelegate->getFlag());
    EXPECT_TRUE(writeDelegate->getFlag());
    EXPECT_TRUE(eraseDelegate->getFlag());
    EXPECT_TRUE(replacementDelegate->getFlag());
}