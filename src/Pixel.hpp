//
// Created by bigna on 9/25/2025.
//

#include <cstdint>
#include <functional>

#ifndef PROJECT_1_IMAGE_PROCESSING_PIXEL_HPP
#define PROJECT_1_IMAGE_PROCESSING_PIXEL_HPP

#pragma pack(push, 1)
struct Pixel
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;

    Pixel& multiply(const Pixel& other);
    Pixel& screen(const Pixel& other);
    Pixel& subtract(const Pixel& other);
    Pixel& add(const Pixel& other);
    Pixel& overlay(const Pixel& other);

    // Helper functions
    /**
     * Calls the passed function for each channel, for operations involving another const pixel
     * @param func Function that is given references to the target object's current channel to operate on and the other pixel's respective channel
     * @param other Another Pixel, who's channels are given to the passed function by value
     */
    Pixel& forEachChannelPair(const std::function<void(uint8_t&, uint8_t)>& func, const Pixel& other);
    static double normalize(uint8_t x);
    static uint8_t unnormalize(double x);
    static uint8_t clamp(int x);

    static uint8_t multiplyChannel(uint8_t c1, uint8_t factor);
    static uint8_t screenChannel(uint8_t c1, uint8_t factor);
    static uint8_t subtractChannel(uint8_t c, uint8_t offset);
    static uint8_t addChannel(uint8_t c, uint8_t offset);
    static uint8_t overlayChannel(uint8_t c, uint8_t factor);
};
#pragma pack(pop)

#endif //PROJECT_1_IMAGE_PROCESSING_PIXEL_HPP