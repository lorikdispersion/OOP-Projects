#include "RayTracer.hpp"

#include <fstream>

#include "RGB256.hpp"
#include "Ray.hpp"
#include "Utilities.hpp"



PpmP3 RayTracer::createImage(std::ostream& progressBar,
                     const Scene& world, std::size_t imageWidth, std::size_t imageHeight,
    const Camera& camera, std::size_t samplesPerPixel, std::size_t maxDepth, float gamma)
{
    PpmP3::Builder builder(imageWidth, imageHeight);

    for (std::size_t j = imageHeight; j > static_cast<std::size_t>(0); --j) {
        for (std::size_t i = 0; i < imageWidth; ++i) {
            progressBar << "\rScanlines remaining: " <<  j << ' ' << "Pixels remaining: " << imageWidth - i << ' ' << std::flush;
            std::size_t tmpR = 0;
            std::size_t tmpG = 0;
            std::size_t tmpB = 0;
            for (std::size_t s = 0; s < samplesPerPixel; ++s) {
                auto horizontalOffset = (static_cast<float>(i) + randomFloat(-0.5, 0.5)) /
                    static_cast<float>(imageWidth);

                auto verticalOffset = (static_cast<float>(j) + randomFloat(-0.5, 0.5)) /
                    static_cast<float>(imageHeight);

                Ray ray = camera.getRay(horizontalOffset, verticalOffset);

                auto tmpColor = world.getRayColor(ray, maxDepth);

                tmpR += tmpColor.r();
                tmpG += tmpColor.g();
                tmpB += tmpColor.b();
            }
            RGB256 pixelColor{ tmpR / samplesPerPixel,
                                    tmpG / samplesPerPixel ,
                                    tmpB / samplesPerPixel };

            pixelColor = pixelColor.gammaCorrection(gamma);

            builder.add(pixelColor);
        }
    }
    progressBar << std::endl << "Done" << std::endl;

    return builder.createImage();
}