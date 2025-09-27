//
// Created by bigna on 9/21/2025.
//

#include <iostream>
#include <filesystem>
#include "TgaContainer.hpp"
#include "Pixel.hpp"

int main()
{
    TgaContainer car("../input/car.tga");
    TgaContainer circles("../input/circles.tga");
    TgaContainer layer_blue("../input/layer_blue.tga");
    TgaContainer layer_green("../input/layer_green.tga");
    TgaContainer layer_red("../input/layer_red.tga");
    TgaContainer layer1("../input/layer1.tga");
    TgaContainer layer2("../input/layer2.tga");
    TgaContainer pattern1("../input/pattern1.tga");
    TgaContainer pattern2("../input/pattern2.tga");
    TgaContainer text("../input/text.tga");
    TgaContainer text2("../input/text2.tga");

    // Part 1
    TgaContainer(layer1).multiply(pattern1).load("../output/part1.tga");

    // Part 2
    TgaContainer(car).subtract(layer2).load("../output/part2.tga");

    // Part 3
    TgaContainer(layer1).multiply(pattern2).screen(text).load("../output/part3.tga");

    // Part 4
    TgaContainer(layer2).multiply(circles).subtract(pattern2).load("../output/part4.tga");

    // Part 5
    TgaContainer(layer1).overlay(pattern1).load("../output/part5.tga");

    // Part 6
    TgaContainer(car).forEachPixel([](Pixel& pixel)
    {
        pixel.green = Pixel::clamp(pixel.green + 200);
    }).load("../output/part6.tga");

    // Part 7
    TgaContainer(car).forEachPixel([](Pixel& pixel)
    {
        pixel.red = Pixel::clamp(pixel.red * 4);
        pixel.blue = 0;
    }).load("../output/part7.tga");

    // Part 8
    TgaContainer(car).forEachPixel([](Pixel& pixel)
    {
        pixel.blue = pixel.red;
        pixel.green = pixel.red;
    }).load("../output/part8_r.tga");
    TgaContainer(car).forEachPixel([](Pixel& pixel)
    {
        pixel.red = pixel.green;
        pixel.blue = pixel.green;
    }).load("../output/part8_g.tga");
    TgaContainer(car).forEachPixel([](Pixel& pixel)
    {
        pixel.red = pixel.blue;
        pixel.green = pixel.blue;
    }).load("../output/part8_b.tga");

    // Part 9
    TgaContainer(layer_red).forEachPixelPair([](Pixel& pixel, const Pixel& other)
    {
        pixel.green = other.green;
    }, layer_green).forEachPixelPair([](Pixel& pixel, const Pixel& other)
    {
        pixel.blue = other.blue;
    }, layer_blue).load("../output/part9.tga");

    // Part 10
    TgaContainer(text2).rotate180().load("../output/part10.tga");
}