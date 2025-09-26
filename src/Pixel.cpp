//
// Created by bigna on 9/25/2025.
//

#include "Pixel.hpp"

#include <iostream>


void Pixel::multiply(const Pixel& other)
{
    forEachChannelPair([](uint8_t& p1, const uint8_t p2)
    {
        p1 = unnormalize(normalize(p1) * normalize(p2));
    }, other);
}

void Pixel::screen(const Pixel& other)
{
    forEachChannelPair([](uint8_t& p1, uint8_t p2)
    {
        p1 = unnormalize(1 - ((1 - normalize(p1)) * (1 - normalize(p2))));
    }, other);
}

void Pixel::subtract(const Pixel& other)
{
    forEachChannelPair([](uint8_t& p1, uint8_t p2)
    {
        p1 = clamp(p1 - p2);
    }, other);
}

void Pixel::add(const Pixel& other)
{
    forEachChannelPair([](uint8_t& p1, uint8_t p2)
    {
        p1 = clamp(p1 + p2);
    }, other);
}

void Pixel::overlay(const Pixel& other)
{
    forEachChannelPair([](uint8_t& p1, uint8_t p2)
    {
        double np2 = normalize(p2);
        if (np2 <= .5)
            return 2 * normalize(p1) * np2;
        if (np2 > .5)
            return 1 - (2 * (1 - normalize(p1) * (1 - np2)));
    }, other);

}

void Pixel::forEachChannelPair(const std::function<void(uint8_t&, uint8_t)>& func, const Pixel& other)
{
    func(red, other.red);
    func(green, other.green);
    func(blue, other.blue);
}


double Pixel::normalize(const uint8_t x)
{
    return x / 255.0;
}

uint8_t Pixel::unnormalize(const double x)
{
    return (x * 255) + .5;
}

uint8_t Pixel::clamp(const int x)
{
    if (x > 255)
        return 255;
    if (x < 0)
        return 0;
    return x;
}
