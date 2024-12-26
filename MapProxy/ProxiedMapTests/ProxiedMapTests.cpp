#include "pch.h"

#include "AuditorWith4Delegates.hpp"
#include "ProxiedMap.hpp"
#include "ProxiedMapExpections.hpp"

#include "EraseAllowed.hpp"
#include "EraseAllowedByKey.hpp"
#include "EraseDenied.hpp"
#include "EraseDeniedByKey.hpp"
#include "ReadAllowed.hpp"
#include "ReadAllowedByKey.hpp"
#include "ReadDenied.hpp"
#include "ReadDeniedByKey.hpp"
#include "WithoutReplacement.hpp"
#include "WithReplacement.hpp"
#include "WriteAllowed.hpp"
#include "WriteAllowedByKey.hpp"
#include "WriteDenied.hpp"
#include "WriteDeniedByKey.hpp"

class ProxiedMapTests : public ::testing::Test {
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

TEST_F(ProxiedMapTests, constructor) {
	auto auditor = new AuditorWith4Delegates(std::make_unique_for_overwrite<ReadAllowed>(),
		std::make_unique_for_overwrite<WriteAllowed>(),
		std::make_unique_for_overwrite<EraseAllowed>(),
		std::make_unique_for_overwrite<WithoutReplacement>());
	std::map < std::string, std::string> mapToWrap{ {"", ""} };
	EXPECT_NO_THROW(ProxiedMap(mapToWrap, std::unique_ptr<Auditor>(auditor)));
}

TEST_F(ProxiedMapTests, contains) {
	auto* auditor = new AuditorWith4Delegates(std::make_unique_for_overwrite<ReadAllowed>(),
		std::make_unique_for_overwrite<WriteAllowed>(),
		std::make_unique_for_overwrite<EraseAllowed>(),
		std::make_unique_for_overwrite<WithoutReplacement>());
	std::map < std::string, std::string> mapToWrap{ {"1", "a"} };
	const ProxiedMap proxiedMap(mapToWrap, std::unique_ptr<Auditor>(auditor));
	EXPECT_TRUE(proxiedMap.contains("1"));
	EXPECT_FALSE(proxiedMap.contains("2"));
}

class DummyFlagCheckingAuditor final : public Auditor
{
	bool readFlag_ = false;
	bool writeFlag_ = false;
	bool eraseFlag_ = false;
	bool replaceFlag_ = false;
public:
	DummyFlagCheckingAuditor() = default;

	[[nodiscard]] bool getReadFlag() const noexcept { return readFlag_; }
	[[nodiscard]] bool getWriteFlag() const noexcept { return writeFlag_; }
	[[nodiscard]] bool getEraseFlag() const noexcept { return eraseFlag_; }
	[[nodiscard]] bool getReplaceFlag() const noexcept { return replaceFlag_; }

	[[nodiscard]] bool canRead(const std::string& key) override { readFlag_ = true;  return true; }
	[[nodiscard]] bool canWrite(const std::string& key) override { writeFlag_ = true;  return true; }
	[[nodiscard]] bool canErase(const std::string& key) override { eraseFlag_ = true;  return true; }

	[[nodiscard]] const std::string& replaceValue(
		const std::string& key, const std::string& value) override {
		replaceFlag_ = true;  return value;
	}
};

class DummyAuditorWith4Delegates final : public Auditor
{
protected:
	std::unique_ptr<ReadAccessDelegate> readAccessDelegate_;
	std::unique_ptr<WriteAccessDelegate> writeAccessDelegate_;
	std::unique_ptr<EraseAccessDelegate> eraseAccessDelegate_;
	std::unique_ptr<ReplacementDelegate> replacementDelegate_;

public:
	DummyAuditorWith4Delegates(std::unique_ptr<ReadAccessDelegate> readAccessDelegate,
		std::unique_ptr<WriteAccessDelegate> writeAccessDelegate,
		std::unique_ptr<EraseAccessDelegate> eraseAccessDelegate,
		std::unique_ptr<ReplacementDelegate> replacementDelegate) :
		readAccessDelegate_(std::move(readAccessDelegate)),
		writeAccessDelegate_(std::move(writeAccessDelegate)),
		eraseAccessDelegate_(std::move(eraseAccessDelegate)),
		replacementDelegate_(std::move(replacementDelegate)) {}

	[[nodiscard]] bool canRead(const std::string& key) override {
		return readAccessDelegate_->canRead(key);
	}

	[[nodiscard]] bool canWrite(const std::string& key) override {
		return writeAccessDelegate_->canWrite(key);
	}

	[[nodiscard]] bool canErase(const std::string& key) override {
		return eraseAccessDelegate_->canErase(key);
	}

	[[nodiscard]] const std::string& replaceValue(
		const std::string& key, const std::string& value) override {
		return	replacementDelegate_->getFakeValue(key, value);
	}
};

TEST_F(ProxiedMapTests, dummyAuditor) {
	auto* checkingAuditor = new DummyFlagCheckingAuditor();

	EXPECT_FALSE(checkingAuditor->getEraseFlag());
	EXPECT_FALSE(checkingAuditor->getReadFlag());
	EXPECT_FALSE(checkingAuditor->getReplaceFlag());
	EXPECT_FALSE(checkingAuditor->getWriteFlag());

	std::map < std::string, std::string> mapToWrap{ {"1", "a"} };
	ProxiedMap proxiedMap(mapToWrap, std::unique_ptr<Auditor>(checkingAuditor));

	EXPECT_NO_THROW(proxiedMap.erase("1"));
	EXPECT_TRUE(checkingAuditor->getEraseFlag());
	EXPECT_FALSE(checkingAuditor->getReadFlag());
	EXPECT_FALSE(checkingAuditor->getReplaceFlag());
	EXPECT_FALSE(checkingAuditor->getWriteFlag());

	EXPECT_TRUE(proxiedMap.insertOrAssign("1", "A"));
	EXPECT_TRUE(checkingAuditor->getWriteFlag());
	EXPECT_FALSE(checkingAuditor->getReadFlag());
	EXPECT_FALSE(checkingAuditor->getReplaceFlag());

	EXPECT_EQ(proxiedMap.at("1"), "A");
	EXPECT_TRUE(checkingAuditor->getReadFlag());
	EXPECT_TRUE(checkingAuditor->getReplaceFlag());
}

TEST_F(ProxiedMapTests, eraseAllowed) {
	auto* auditor = new DummyAuditorWith4Delegates(nullptr, nullptr,
		std::make_unique_for_overwrite<EraseAllowed>(),nullptr);
	std::map < std::string, std::string> mapToWrap{ {"1", "a"} };
	ProxiedMap proxiedMap(mapToWrap, std::unique_ptr<Auditor>(auditor));
	EXPECT_NO_THROW(proxiedMap.erase("1"));
}

TEST_F(ProxiedMapTests, eraseDenied) {
	auto* auditor = new DummyAuditorWith4Delegates(nullptr, nullptr,
		std::make_unique_for_overwrite<EraseDenied>(),nullptr);
	std::map < std::string, std::string> mapToWrap{ {"1", "a"} };
	ProxiedMap proxiedMap(mapToWrap, std::unique_ptr<Auditor>(auditor));
	EXPECT_THROW(proxiedMap.erase("1"), EraseAccessDenied);
	EXPECT_TRUE(mapToWrap.contains("1"));
}

TEST_F(ProxiedMapTests, eraseAllowedByKey) {
	auto* auditor = new DummyAuditorWith4Delegates(nullptr, nullptr,
		std::make_unique<EraseAllowedByKey>(EraseAllowedByKey({ "1" })),nullptr);
	std::map < std::string, std::string> mapToWrap{ {"1", "a"} };
	ProxiedMap proxiedMap(mapToWrap, std::unique_ptr<Auditor>(auditor));
	EXPECT_NO_THROW(proxiedMap.erase("1"));
	EXPECT_THROW(proxiedMap.erase("2"), EraseAccessDenied);
}

TEST_F(ProxiedMapTests, eraseDeniedByKey) {
	auto* auditor = new DummyAuditorWith4Delegates(nullptr, nullptr,
		std::make_unique<EraseDeniedByKey>(EraseDeniedByKey({ "1" })),nullptr);
	std::map < std::string, std::string> mapToWrap{ {"1", "a"} };
	ProxiedMap proxiedMap(mapToWrap, std::unique_ptr<Auditor>(auditor));
	EXPECT_THROW(proxiedMap.erase("1"), EraseAccessDenied);
	EXPECT_TRUE(mapToWrap.contains("1"));
}

TEST_F(ProxiedMapTests, writeAllowed) {
	auto* auditor = new DummyAuditorWith4Delegates(nullptr,
		std::make_unique_for_overwrite<WriteAllowed>(),nullptr, nullptr );
	ProxiedMap proxiedMap{std::unique_ptr<Auditor>(auditor)};
	bool insertOrAssignFlag = false;
	EXPECT_NO_THROW(insertOrAssignFlag = proxiedMap.insertOrAssign("1", "a"));
	EXPECT_TRUE(insertOrAssignFlag);
	EXPECT_NO_THROW(insertOrAssignFlag = proxiedMap.insertOrAssign("1", "b"));
	EXPECT_FALSE(insertOrAssignFlag);
}

TEST_F(ProxiedMapTests, writeDenied) {
	auto* auditor = new DummyAuditorWith4Delegates(nullptr,
		std::make_unique_for_overwrite<WriteDenied>(),nullptr, nullptr);
	std::map < std::string, std::string> mapToWrap{};
	ProxiedMap proxiedMap(mapToWrap, std::unique_ptr<Auditor>(auditor));
	EXPECT_THROW(proxiedMap.insertOrAssign("1", "a"), WriteAccessDenied);
	EXPECT_FALSE(mapToWrap.contains("1"));
}

TEST_F(ProxiedMapTests, writeAllowedByKey) {
	auto* auditor = new DummyAuditorWith4Delegates(nullptr,
		std::make_unique<WriteAllowedByKey>(WriteAllowedByKey({ "1" })),
		nullptr, nullptr);
	ProxiedMap proxiedMap{std::unique_ptr<Auditor>(auditor)};
	bool insertOrAssignFlag = false;
	EXPECT_NO_THROW(insertOrAssignFlag = proxiedMap.insertOrAssign("1", "a"));
	EXPECT_TRUE(insertOrAssignFlag);
	EXPECT_THROW(proxiedMap.insertOrAssign("2", "b"), WriteAccessDenied);
	EXPECT_NO_THROW(insertOrAssignFlag = proxiedMap.insertOrAssign("1", "b"));
	EXPECT_FALSE(insertOrAssignFlag);
}

TEST_F(ProxiedMapTests, writeDeniedByKey) {
	auto* auditor = new DummyAuditorWith4Delegates(nullptr,
		std::make_unique<WriteDeniedByKey>(WriteDeniedByKey({ "1" })),
		nullptr, nullptr);
	ProxiedMap proxiedMap{std::unique_ptr<Auditor>(auditor)};
	bool insertOrAssignFlag = false;
	EXPECT_THROW(proxiedMap.insertOrAssign("1", "a"), WriteAccessDenied);
	EXPECT_NO_THROW(insertOrAssignFlag = proxiedMap.insertOrAssign("2", "b"));
	EXPECT_TRUE(insertOrAssignFlag);
	EXPECT_NO_THROW(insertOrAssignFlag = proxiedMap.insertOrAssign("2", "c"));
	EXPECT_FALSE(insertOrAssignFlag);
}

TEST_F(ProxiedMapTests, readAllowed) {
	auto* auditor = new DummyAuditorWith4Delegates(std::make_unique_for_overwrite<ReadAllowed>(),
		nullptr, nullptr,
		std::make_unique_for_overwrite<WithoutReplacement>());
	const std::map < std::string, std::string> mapToWrap{ {"1", "a"} };
	const ProxiedMap proxiedMap(mapToWrap, std::unique_ptr<Auditor>(auditor));
	EXPECT_EQ(proxiedMap.at("1"), "a");
	EXPECT_THROW(proxiedMap.at("2"), std::out_of_range);
}

TEST_F(ProxiedMapTests, readDenied) {
	auto* auditor = new DummyAuditorWith4Delegates(std::make_unique_for_overwrite<ReadDenied>(),
		nullptr, nullptr,
		std::make_unique_for_overwrite<WithoutReplacement>());
	const std::map < std::string, std::string> mapToWrap{ {"1", "a"} };
	const ProxiedMap proxiedMap(mapToWrap, std::unique_ptr<Auditor>(auditor));
	EXPECT_THROW(proxiedMap.at("1"), ReadAccessDenied);
}

TEST_F(ProxiedMapTests, readAllowedByKey) {
	auto* auditor = new DummyAuditorWith4Delegates(std::make_unique<ReadAllowedByKey>(ReadAllowedByKey({ "1" })),
		nullptr, nullptr,
		std::make_unique_for_overwrite<WithoutReplacement>());
	const std::map < std::string, std::string> mapToWrap{ {"1", "a"} };
	const ProxiedMap proxiedMap(mapToWrap, std::unique_ptr<Auditor>(auditor));
	EXPECT_EQ(proxiedMap.at("1"), "a");
	EXPECT_THROW(proxiedMap.at("2"), ReadAccessDenied);
}

TEST_F(ProxiedMapTests, readDeniedByKey) {
	auto* auditor = new DummyAuditorWith4Delegates(std::make_unique<ReadDeniedByKey>(ReadDeniedByKey({ "1" })),
		nullptr, nullptr,
		std::make_unique_for_overwrite<WithoutReplacement>());
	const std::map < std::string, std::string> mapToWrap{ {"1", "a"} };
	const ProxiedMap proxiedMap(mapToWrap, std::unique_ptr<Auditor>(auditor));
	EXPECT_THROW(proxiedMap.at("1"), ReadAccessDenied);
	EXPECT_THROW(proxiedMap.at("2"), std::out_of_range);
}

TEST_F(ProxiedMapTests, withoutReplacement) {
	auto* auditor = new DummyAuditorWith4Delegates(std::make_unique_for_overwrite<ReadAllowed>(),
		nullptr, nullptr,
		std::make_unique_for_overwrite<WithoutReplacement>());
	const std::map < std::string, std::string> mapToWrap{ {"1", "a"} };
	const ProxiedMap proxiedMap(mapToWrap, std::unique_ptr<Auditor>(auditor));
	EXPECT_EQ(proxiedMap.at("1"), "a");
}

TEST_F(ProxiedMapTests, withReplacement) {
	auto* auditor = new DummyAuditorWith4Delegates(std::make_unique_for_overwrite<ReadAllowed>(),
		nullptr, nullptr,
		std::make_unique<WithReplacement>(
			std::unordered_map<std::string, std::string>({ {"1", "c"} })));
	const std::map < std::string, std::string> mapToWrap{ {"1", "a"}, {"2", "b"} };
	const ProxiedMap proxiedMap(mapToWrap, std::unique_ptr<Auditor>(auditor));
	EXPECT_EQ(proxiedMap.at("1"), "c");
	EXPECT_EQ(mapToWrap.at("1"), "a");
	EXPECT_EQ(proxiedMap.at("2"), "b");
}