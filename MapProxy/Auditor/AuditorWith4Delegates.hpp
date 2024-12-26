#pragma once

#include <memory>
#include <string>

#include "Auditor.hpp"
#include "ReadAccessDelegate.hpp"
#include "WriteAccessDelegate.hpp"
#include "EraseAccessDelegate.hpp"
#include "ReplacementDelegate.hpp"

class AuditorWith4Delegates final : public Auditor
{
protected:
	std::unique_ptr<ReadAccessDelegate> readAccessDelegate_;
	std::unique_ptr<WriteAccessDelegate> writeAccessDelegate_;
	std::unique_ptr<EraseAccessDelegate> eraseAccessDelegate_;
	std::unique_ptr<ReplacementDelegate> replacementDelegate_;

public:
	AuditorWith4Delegates(std::unique_ptr<ReadAccessDelegate> readAccessDelegate,
		std::unique_ptr<WriteAccessDelegate> writeAccessDelegate,
		std::unique_ptr<EraseAccessDelegate> eraseAccessDelegate,
		std::unique_ptr<ReplacementDelegate> replacementDelegate);

	[[nodiscard]] bool canRead(const std::string& key) override;
	[[nodiscard]] bool canWrite(const std::string& key) override;
	[[nodiscard]] bool canErase(const std::string& key) override;

	[[nodiscard]] const std::string& replaceValue(
		const std::string& key, const std::string& value) override;
};