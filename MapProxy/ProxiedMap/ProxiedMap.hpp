#pragma once

#include <map>
#include <memory>
#include "Auditor.hpp"

class ProxiedMap final
{
    std::map<std::string, std::string> wrappedMap_;
    std::unique_ptr<Auditor> auditor_;

public:
    ProxiedMap(std::unique_ptr<Auditor> auditor);
    ProxiedMap(std::map<std::string, std::string> mapToWrap, std::unique_ptr<Auditor> auditor);

    [[nodiscard]] bool insertOrAssign(const std::string& key, const std::string& value);

    [[nodiscard]] const std::string& at(const std::string& key) const;

    void erase(const std::string& key);

    [[nodiscard]] bool contains(const std::string& key) const noexcept;
};