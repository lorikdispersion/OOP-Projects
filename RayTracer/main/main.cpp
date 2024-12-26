#include <fstream>
#include <iostream>

#include "PpmP3Printer.hpp"
#include "Camera.hpp"
#include "Dielectric.hpp"
#include "RayTracer.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include "Sky.hpp"
#include "Sphere.hpp"
#include "ConsoleUI.hpp"

int main()
{
    ConsoleUI::runRayTracer();
}