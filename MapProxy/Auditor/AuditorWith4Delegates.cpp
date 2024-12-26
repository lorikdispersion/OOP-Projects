#include "AuditorWith4Delegates.hpp"
#include "AuditorExpections.hpp"

AuditorWith4Delegates::AuditorWith4Delegates(std::unique_ptr<ReadAccessDelegate> readAccessDelegate,
	std::unique_ptr<WriteAccessDelegate> writeAccessDelegate,
	std::unique_ptr<EraseAccessDelegate> eraseAccessDelegate,
	std::unique_ptr<ReplacementDelegate> replacementDelegate) :
	readAccessDelegate_(std::move(readAccessDelegate)),
	writeAccessDelegate_(std::move(writeAccessDelegate)),
	eraseAccessDelegate_(std::move(eraseAccessDelegate)),
	replacementDelegate_(std::move(replacementDelegate))
{
	if(!readAccessDelegate_) {
		throw NullPtrReadAccessDelegate();
	}
	if (!writeAccessDelegate_) {
		throw NullPtrWriteAccessDelegate();
	}
	if (!eraseAccessDelegate_) {
		throw NullPtrEraseAccessDelegate();
	}
	if (!replacementDelegate_) {
		throw NullPtrReplacementDelegate();
	}
}


bool AuditorWith4Delegates::canRead(const std::string& key)
{
	return readAccessDelegate_->canRead(key);
}

bool AuditorWith4Delegates::canWrite(const std::string& key)
{
	return writeAccessDelegate_->canWrite(key);
}

bool AuditorWith4Delegates::canErase(const std::string& key)
{
	return eraseAccessDelegate_->canErase(key);
}

const std::string& AuditorWith4Delegates::replaceValue(const std::string& key, const std::string& value)
{
	return replacementDelegate_->getFakeValue(key, value);
}