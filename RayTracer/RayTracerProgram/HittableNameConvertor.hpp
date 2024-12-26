#pragma once
#include <unordered_map>

class HittableNameConvertor final {
public:
    HittableNameConvertor() = default;

    enum class Name {
        Sphere, Incorrect
    };

private:
    std::unordered_map<std::string, Name> stringsToNames_{
        {"Sphere", Name::Sphere},
    };
public:
    Name getName(const std::string& Name)
    {
        const auto result = stringsToNames_.find(Name);
        if (result == stringsToNames_.end()) { return Name::Incorrect; }
        return result->second;
    }
};
