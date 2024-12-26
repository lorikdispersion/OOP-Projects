#pragma once

#include "MaterialDTO.hpp"

class LambertianDTO : public MaterialDTO {
    float albedoR_;
    float albedoG_;
    float albedoB_;
public:
    LambertianDTO(MaterialNameConvertor::Name name,
        float albedoR, float albedoG, float albedoB) :
        MaterialDTO(name), albedoR_(albedoR), albedoG_(albedoG), albedoB_(albedoB) {}

    ~LambertianDTO() override = default;

    [[nodiscard]] float getAlbedoR() const { return albedoR_; }
    [[nodiscard]] float getAlbedoG() const { return albedoG_; }
    [[nodiscard]] float getAlbedoB() const { return albedoB_; }
};