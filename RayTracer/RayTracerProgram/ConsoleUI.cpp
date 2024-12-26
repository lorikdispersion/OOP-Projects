#include "ConsoleUI.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Camera.hpp"
#include "HittableParser.hpp"
#include "MaterialFactory.hpp"
#include "MaterialParser.hpp"
#include "Scene.hpp"
#include "Sky.hpp"
#include "Vector3d.hpp"
#include "HittableFactory.hpp"
#include "RayTracer.hpp"
#include "PpmP3Printer.hpp"

namespace
{
	float parseToFloat(std::istream& input)
	{
		float result;
		if (input >> result)
		{
			return result;
		}
		throw std::invalid_argument("Cannot convert");
	}

	Vector3d parseToVector(std::istream& input)
	{
		auto x = parseToFloat(input);
		auto y = parseToFloat(input);
		auto z = parseToFloat(input);
		return { x, y, z };
	}


	Camera initCamera(float aspectRatio, std::istream& input)
	{
		std::cout << "Enter coordinates of camera in 3d (with whitespaces): ";
		auto lookFrom = parseToVector(std::cin);
		std::cout << std::endl;

		std::cout << "Enter direction of camera view in 3d (with whitespaces): ";
		auto lookAt = parseToVector(std::cin);
		std::cout << std::endl;

		std::cout << "Enter direction of camera top in 3d (with whitespaces): ";
		auto viewUp = parseToVector(std::cin);
		std::cout << std::endl;

		std::cout << "Enter camera FOV in degrees: ";
		auto fov = parseToFloat(std::cin);
		std::cout << std::endl;

		std::cout << "Enter camera focal distance: ";
		auto distToFocus = parseToFloat(std::cin);
		std::cout << std::endl;

		std::cout << "Enter camera aperture: ";
		auto aperture = parseToFloat(std::cin);
		std::cout << std::endl;

		return {  lookFrom, lookAt, viewUp, fov, aspectRatio,
			aperture, distToFocus } ;
	}


	std::size_t parseToSizeT(std::istream& input)
	{
		std::size_t result;
		if(input >> result)
		{
			return result;
		}
		throw std::invalid_argument("Cannot convert");
	}

	void greetings()
	{
		std::cout << "Welcome to RayTracer!" << std::endl <<
			"This program allow you create pretty images with objects of different materials"
			<< std::endl << std::endl;
	}
}

void ConsoleUI::runRayTracer()
{
	greetings();

	std::string imageDir;
	std::cout << "Enter output image directory (.ppm format only)" << std::endl;
	std::cin >> imageDir;
	std::cout << std::endl;

	std::ofstream outputFile (imageDir, std::ios_base::out);
	if (!outputFile.is_open())
	{
		std::cout << "Can't open file" << std::endl;
		return;
	}


	std::cout << "Enter image width: ";
	auto imageWidth = parseToSizeT(std::cin);
	std::cout << std::endl;

	std::cout << "Enter image height: ";
	auto imageHeight = parseToSizeT(std::cin);
	std::cout << std::endl;

	float aspectRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);


	auto camera = initCamera(aspectRatio, std::cin);


	std::cout << "Enter gamma correction coefficient: ";
	auto gamma = parseToFloat(std::cin);
	std::cout << std::endl;


	std::cout << "Enter amount of reflections of one ray: ";
	auto depth = parseToSizeT(std::cin);
	std::cout << std::endl;


	std::cout << "Enter amount rays per pixel: ";
	auto samplesPerPixel = parseToSizeT(std::cin);
	std::cout << std::endl;


	Scene::Builder builder(std::make_shared<Sky>());

	std::cout << "Scene initialization block. Enter amount of objects on scene: ";
	auto hittableAmount = parseToSizeT(std::cin);
	std::cout << std::endl;

	MaterialParser materialParser(' ');
	HittableParser hittableParser(' ');

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for(std::size_t i = 0; i < hittableAmount; i++)
	{
		std::cout << "Enter name and properies of material of following object:" << std::endl;
		auto materialPtr = MaterialFactory::createMaterial(materialParser, std::cin);
		std::cout << std::endl;

		std::cout << "Enter name and properies of following object:" << std::endl;
		builder.add(HittableFactory::createHittable(
			hittableParser, std::cin, materialPtr));
		std::cout << std::endl;
	}

	auto world = builder.createScene();

	auto image = RayTracer::createImage(std::cout, world, imageWidth, imageHeight,
		camera, samplesPerPixel, depth, gamma);

	outputFile << image;
}
