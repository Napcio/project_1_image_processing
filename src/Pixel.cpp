//
// Created by bigna on 9/25/2025.
//

#include "Pixel.hpp"

#include <iostream>


Pixel& Pixel::multiply(const Pixel& other)
{
    forEachChannelPair([](uint8_t& p1, const uint8_t p2)
    {
        p1 = multiplyChannel(p1, p2);
    }, other);
    return *this;
}

Pixel& Pixel::screen(const Pixel& other)
{
    forEachChannelPair([](uint8_t& p1, uint8_t p2)
    {
        p1 = screenChannel(p1, p2);
    }, other);
    return *this;
}

Pixel& Pixel::subtract(const Pixel& other)
{
    forEachChannelPair([](uint8_t& p1, uint8_t p2)
    {
        p1 = subtractChannel(p1, p2);
    }, other);
    return *this;
}

Pixel& Pixel::add(const Pixel& other)
{
    forEachChannelPair([](uint8_t& p1, uint8_t p2)
    {
        p1 = addChannel(p1, p2);
    }, other);
    return *this;
}

Pixel& Pixel::overlay(const Pixel& other)
{
    forEachChannelPair([](uint8_t& p1, uint8_t p2)
    {
        p1 = overlayChannel(p1, p2);
    }, other);
    return *this;
}

Pixel& Pixel::forEachChannelPair(const std::function<void(uint8_t&, uint8_t)>& func, const Pixel& other)
{
    func(red, other.red);
    func(green, other.green);
    func(blue, other.blue);
    return *this;
}

// Helper functions

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

uint8_t Pixel::multiplyChannel(uint8_t c1, uint8_t c2)
{
    return unnormalize(normalize(c1) * normalize(c2));
}

uint8_t Pixel::screenChannel(uint8_t c1, uint8_t c2)
{
    return unnormalize(1 - ((1 - normalize(c1)) * (1 - normalize(c2))));
}

uint8_t Pixel::subtractChannel(uint8_t c, uint8_t offset)
{
    return clamp(c - offset);
}

uint8_t Pixel::addChannel(uint8_t c, uint8_t offset)
{
    return clamp(c + offset);
}

uint8_t Pixel::overlayChannel(uint8_t c1, uint8_t c2)
{
    const double np2 = normalize(c2);
    if (np2 <= .5)
    {
        return unnormalize(2 * normalize(c1) * np2);
    }
    if (np2 > .5)
    {
        return unnormalize(1 - (2 * (1 - normalize(c1)) * (1 - np2)));
    }
}


