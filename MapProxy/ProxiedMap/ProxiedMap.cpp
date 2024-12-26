#include "ProxiedMap.hpp"
#include "ProxiedMapExpections.hpp"

#include <stdexcept>
#include <utility>

ProxiedMap::ProxiedMap(std::unique_ptr<Auditor> auditor) : auditor_(std::move(auditor)) {}

ProxiedMap::ProxiedMap(std::map<std::string, std::string> mapToWrap, std::unique_ptr<Auditor> auditor)
    :wrappedMap_(std::move(mapToWrap)), auditor_(std::move(auditor))
{
	if(!auditor_)
	{
        throw AuditorNullPtr();
	}
}


bool ProxiedMap::insertOrAssign(const std::string& key, const std::string& value)
{
    if (!auditor_->canWrite(key)) {
        throw WriteAccessDenied();
    }
    return wrappedMap_.insert_or_assign(key, value).second;
}

const std::string& ProxiedMap::at(const std::string& key) const
{
    if (!auditor_->canRead(key)) {
        throw ReadAccessDenied();
    }
    return auditor_->replaceValue(key, wrappedMap_.at(key));
}

void ProxiedMap::erase(const std::string& key)
{
    if (!auditor_->canErase(key)) {
        throw EraseAccessDenied();
    }
    wrappedMap_.erase(key);
}

bool ProxiedMap::contains(const std::string& key) const noexcept
{
    return wrappedMap_.contains(key);
}