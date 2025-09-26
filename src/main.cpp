//
// Created by bigna on 9/21/2025.
//

#include <iostream>
#include <filesystem>
#include "TgaContainer.hpp"
#include "Pixel.hpp"

int main()
{
    // Part 1
    TgaContainer part1Image("../input/layer1.tga");
    TgaContainer part1Reference("../input/car.tga");
    part1Image.multiply(part1Reference).load("../output/part1.tga");

    // Part 2
    TgaContainer part2Image("../input/layer2.tga");
    TgaContainer part2Reference("../input/car.tga");
    part2Image.subtract(part2Reference).load("../output/part2.tga");

    TgaContainer part3Image("../input/layer2.tga");
    TgaContainer part3Reference("../input/car.tga");
    part3Image.subtract(part3Reference);
    part3Image.load("../output/part3.tga");
}