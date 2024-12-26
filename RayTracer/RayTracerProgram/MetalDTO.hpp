#pragma once

#include "MaterialDTO.hpp"

class MetalDTO : public MaterialDTO {
    float albedoR_;
    float albedoG_;
    float albedoB_;
    float fuzz_;
public:
    MetalDTO(MaterialNameConvertor::Name name, 
        float albedoR, float albedoG, float albedoB, float fuzz) :
        MaterialDTO(name),
		albedoR_(albedoR), albedoG_(albedoG), albedoB_(albedoB), fuzz_(fuzz){}

    ~MetalDTO() override = default;

    [[nodiscard]] float getAlbedoR() const { return albedoR_; }
    [[nodiscard]] float getAlbedoG() const { return albedoG_; }
    [[nodiscard]] float getAlbedoB() const { return albedoB_; }
    [[nodiscard]] float getFuzz() const { return fuzz_; }
};
