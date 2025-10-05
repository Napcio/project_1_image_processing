//
// Created by bigna on 9/25/2025.
//

#include "Pixel.hpp"

#include <stdexcept>

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

Pixel& Pixel::invert()
{
    forEachChannel([](uint8_t& c)
    {
        c = invertChannel(c);
    });
    return *this;
}

Pixel& Pixel::grayscale()
{
    // Stole the following formula from here:
    // https://github.com/pyvista/pyvista/blob/release/0.46/pyvista/plotting/texture.py#L610-L645
    // uint8_t gray  = clamp((0.299 * red) + (0.587 * green) + (0.114 * blue) + .5);
    // nevermind i think i need the dumb grayscale for the histogram
    uint8_t gray = ((red + green + blue) / 3.0) + .5;

    forEachChannel([gray](uint8_t& c)
    {
        c = gray;
    });
    return *this;
}

Pixel& Pixel::sepia()
{
    // Stole the following formulas from here:
    // https://medium.com/@rupertontheloose/functional-shaders-a-colorful-intro-part5-tinting-with-sepia-tone-cd6c2b49806
    red = clamp((red * 0.393) + (green * 0.769) + (blue * 0.189) + .5);
    green = clamp((red * 0.349) + (green * 0.686) + (blue * 0.168) + .5);
    blue = clamp((red * 0.272) + (green * 0.534) + (blue * 0.131) + .5);
    return *this;
}

Pixel& Pixel::forEachChannel(const std::function<void(uint8_t&)>& func)
{
    func(red);
    func(green);
    func(blue);
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
    throw std::runtime_error("Pixel::overlayChannel() error: Control should never pass if statements");
}

uint8_t Pixel::invertChannel(uint8_t c)
{
    return 255 - c;
}


