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
    explicit TgaContainer(const std::string &filename);

    TgaContainer(const TgaContainer& other);
    TgaContainer(TgaContainer&& other) noexcept;

    TgaContainer& operator=(const TgaContainer& other);
    TgaContainer& operator=(TgaContainer&& other) noexcept;

    ~TgaContainer();



    // Helper functions
    /**
     * Calls the passed function for each pixel
     * @param func Function that is given a reference to the current pixel to operate on
     */
    void forEachPixel(const std::function<void(Pixel&)>& func);

    /**
     * Calls the passed function for each pixel, for operations involving another const TgaContainer
     * @param func Function that is given references to the target object's current pixel to operate on and the other TgaContainer's respective pixel
     * @param other Another TgaContainer, who's pixels are given to the passed function as a const reference
     */
    void forEachPixelPair(std::function<void(Pixel&, const Pixel&)> func, const TgaContainer& other);

    void load(const std::string &filename);

    // TODO: remove this lmao its just for testing
    TgaHeader& getHeader()
    {
        return header_;
    }


private:
    void deleteImageData();
    void allocateImageData();

    TgaHeader header_;
    Pixel** imageData_; // 2D array of Pixel structs
};


#endif //PROJECT_1_IMAGE_PROCESSING_NAPCIO_TGACONTAINER_HPP