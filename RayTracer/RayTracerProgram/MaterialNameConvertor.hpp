#pragma once
#include <unordered_map>

class MaterialNameConvertor final {
public:
    MaterialNameConvertor() = default;

    enum class Name {
        Lambertian, Metal, Dielectric, Incorrect
    };

private:
    std::unordered_map<std::string, Name> stringsToNames_{
        {"Lambertian", Name::Lambertian},
        {"Metal", Name::Metal},
        {"Dielectric", Name::Dielectric}
    };
public:
    Name readName(const std::string& Name)
    {
	    const auto result = stringsToNames_.find(Name);
        if (result == stringsToNames_.end()) { return Name::Incorrect; }
        return result->second;
    }
};
