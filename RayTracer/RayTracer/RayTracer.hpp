#pragma once

#include "Camera.hpp"
#include "PpmP3.hpp"
#include "Scene.hpp"

class RayTracer final
{
public:
    RayTracer() = delete;
    [[nodiscard]]static PpmP3 createImage(std::ostream& progressBar,
		const Scene& world, std::size_t imageWidth, std::size_t imageHeight,
        const Camera& camera, std::size_t samplesPerPixel, std::size_t maxDepth, float gamma);
};
