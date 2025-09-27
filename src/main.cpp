//
// Created by bigna on 9/21/2025.
//

#include <iostream>
#include <filesystem>
#include "TgaContainer.hpp"
#include "Pixel.hpp"


int main()
{
    const std::string INPUT_PATH = "./input/";
    const std::string OUTPUT_PATH = "./output/";

    TgaContainer car(INPUT_PATH + "car.tga");
    TgaContainer circles(INPUT_PATH + "circles.tga");
    TgaContainer layer_blue(INPUT_PATH + "layer_blue.tga");
    TgaContainer layer_green(INPUT_PATH + "layer_green.tga");
    TgaContainer layer_red(INPUT_PATH + "layer_red.tga");
    TgaContainer layer1(INPUT_PATH + "layer1.tga");
    TgaContainer layer2(INPUT_PATH + "layer2.tga");
    TgaContainer pattern1(INPUT_PATH + "pattern1.tga");
    TgaContainer pattern2(INPUT_PATH + "pattern2.tga");
    TgaContainer text(INPUT_PATH + "text.tga");
    TgaContainer text2(INPUT_PATH + "text2.tga");

    // Part 1
    TgaContainer(layer1).multiply(pattern1).load(OUTPUT_PATH + "part1.tga");

    // Part 2
    TgaContainer(car).subtract(layer2).load(OUTPUT_PATH + "part2.tga");

    // Part 3
    TgaContainer(layer1).multiply(pattern2).screen(text).load(OUTPUT_PATH + "part3.tga");

    // Part 4
    TgaContainer(layer2).multiply(circles).subtract(pattern2).load(OUTPUT_PATH + "part4.tga");

    // Part 5
    TgaContainer(layer1).overlay(pattern1).load(OUTPUT_PATH + "part5.tga");

    // Part 6
    TgaContainer(car).forEachPixel([](Pixel& pixel)
    {
        pixel.green = Pixel::clamp(pixel.green + 200);
    }).load(OUTPUT_PATH + "part6.tga");

    // Part 7
    TgaContainer(car).forEachPixel([](Pixel& pixel)
    {
        pixel.red = Pixel::clamp(pixel.red * 4);
        pixel.blue = 0;
    }).load(OUTPUT_PATH + "part7.tga");

    // Part 8
    TgaContainer(car).forEachPixel([](Pixel& pixel)
    {
        pixel.blue = pixel.red;
        pixel.green = pixel.red;
    }).load(OUTPUT_PATH + "part8_r.tga");
    TgaContainer(car).forEachPixel([](Pixel& pixel)
    {
        pixel.red = pixel.green;
        pixel.blue = pixel.green;
    }).load(OUTPUT_PATH + "part8_g.tga");
    TgaContainer(car).forEachPixel([](Pixel& pixel)
    {
        pixel.red = pixel.blue;
        pixel.green = pixel.blue;
    }).load(OUTPUT_PATH + "part8_b.tga");

    // Part 9
    TgaContainer(layer_red).forEachPixelPair([](Pixel& pixel, const Pixel& other)
    {
        pixel.green = other.green;
    }, layer_green).forEachPixelPair([](Pixel& pixel, const Pixel& other)
    {
        pixel.blue = other.blue;
    }, layer_blue).load(OUTPUT_PATH + "part9.tga");

    // Part 10
    TgaContainer(text2).rotate180().load(OUTPUT_PATH + "part10.tga");
}