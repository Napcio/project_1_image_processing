//
// Created by bigna on 9/21/2025.
//

#include <iostream>
#include <filesystem>
#include "TgaContainer.hpp"
#include "Pixel.hpp"

int main()
{
    // std::cout << std::filesystem::current_path() << std::endl;
    TgaContainer test("../input/car.tga");
    test.load("../output/test.tga");

    // std::cout << test.getHeader().imageWidth << std::endl;
}