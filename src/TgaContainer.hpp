//
// Created by bigna on 9/21/2025.
//

#include <cstdint>
#include <string>
#include <functional>

#ifndef PROJECT_1_IMAGE_PROCESSING_NAPCIO_TGACONTAINER_HPP
#define PROJECT_1_IMAGE_PROCESSING_NAPCIO_TGACONTAINER_HPP

#pragma pack(push, 1)
struct TgaHeader
{
    uint8_t idLength;
    uint8_t colorMapType;
    uint8_t imageType;
    uint16_t colorMapOrigin;
    uint16_t colorMapLength;
    uint8_t colorMapDepth;
    uint16_t xOrigin;
    uint16_t yOrigin;
    uint16_t imageWidth;
    uint16_t imageHeight;
    uint8_t pixelDepth;
    uint8_t imageDescriptor;
};
#pragma pack(pop)

struct Pixel;

// For all operations involving another TgaContainer, the invoking object is the top layer and the passed object is the
// bottom layer
class TgaContainer
{
public:
    explicit TgaContainer(const std::string& filename);
    explicit TgaContainer(std::ifstream& in);

    TgaContainer(const TgaContainer& other);
    TgaContainer(TgaContainer&& other) noexcept;

    TgaContainer& operator=(const TgaContainer& other);
    TgaContainer& operator=(TgaContainer&& other) noexcept;

    ~TgaContainer();

    TgaContainer& multiply(const TgaContainer& other);
    TgaContainer& screen(const TgaContainer& other);
    TgaContainer& subtract(const TgaContainer& other);
    TgaContainer& add(const TgaContainer& other);
    TgaContainer& overlay(const TgaContainer& other);

    TgaContainer& flip();

    TgaContainer& combine(const TgaContainer& green, const TgaContainer& blue);
    TgaContainer& onlyRed();
    TgaContainer& onlyGreen();
    TgaContainer& onlyBlue();
    TgaContainer& addRed(int x);
    TgaContainer& addGreen(int x);
    TgaContainer& addBlue(int x);
    TgaContainer& scaleRed(int x);
    TgaContainer& scaleGreen(int x);
    TgaContainer& scaleBlue(int x);


    // Helper functions
    /**
     * Calls the passed function for each pixel
     * @param func Function that is given a reference to the current pixel to operate on
     */
    TgaContainer& forEachPixel(const std::function<void(Pixel&)>& func);

    /**
     * Calls the passed function for each pixel, for operations involving another const TgaContainer
     * @param func Function that is given references to the target object's current pixel to operate on and the other TgaContainer's respective pixel
     * @param other Another TgaContainer, who's pixels are given to the passed function as a const reference
     */
    TgaContainer& forEachPixelPair(const std::function<void(Pixel&, const Pixel&)>& func, const TgaContainer& other);

    TgaContainer& save(const std::string& filename);


private:
    void load(std::ifstream& in);
    void deleteImageData();
    void allocateImageData();

    TgaHeader header_;
    Pixel** imageData_ = nullptr; // 2D array of Pixel structs
};


#endif //PROJECT_1_IMAGE_PROCESSING_NAPCIO_TGACONTAINER_HPP