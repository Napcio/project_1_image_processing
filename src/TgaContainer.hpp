//
// Created by bigna on 9/21/2025.
//

#ifndef PROJECT_1_IMAGE_PROCESSING_NAPCIO_TGACONTAINER_HPP
#define PROJECT_1_IMAGE_PROCESSING_NAPCIO_TGACONTAINER_HPP

#include <cstdint>
#include <string>
#include <functional>

#include "KernelOperations.hpp"

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
    static constexpr size_t defaultHeight = 512;
    static constexpr size_t defaultWidth = 512;

    explicit TgaContainer(const std::string& filename);
    explicit TgaContainer(std::ifstream& in);

    TgaContainer(const TgaContainer& other);
    TgaContainer(TgaContainer&& other) noexcept;

    TgaContainer& operator=(const TgaContainer& other);
    TgaContainer& operator=(TgaContainer&& other) noexcept;

    ~TgaContainer();

    [[nodiscard]] size_t getHeight() const;
    [[nodiscard]] size_t getWidth() const;
    Pixel& pixelAt(size_t row, size_t col);

    // Milestone 1
    TgaContainer& multiply(const TgaContainer& other);
    TgaContainer& multiply(double factor);
    TgaContainer& screen(const TgaContainer& other);
    TgaContainer& subtract(const TgaContainer& other);
    TgaContainer& add(const TgaContainer& other);
    TgaContainer& overlay(const TgaContainer& other);
    TgaContainer& flip();

    // Milestone 2
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

    // Extra credit
    TgaContainer& invert();
    TgaContainer& grayscale();
    TgaContainer& sepia();
    // Uses Laplacian edge detection
    TgaContainer& highlightEdges();
    TgaContainer& sharpen(double intensity);
    TgaContainer& blur();
    TgaContainer& scale(size_t newHeight, size_t newWidth);


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

    TgaContainer& applyKernel(const KernelVec& kernel);

    TgaContainer& save(const std::string& filename);


    // Kernels
    inline static const KernelVec laplacianEdgeDetection = {
        {-1, -1, -1},
        {-1, 8, -1},
        {-1, -1, -1}
    };


private:
    void load(std::ifstream& in);
    void deleteImageData();
    void allocateImageData();

    TgaHeader header_;
    Pixel** imageData_ = nullptr; // 2D array of Pixel structs
};


#endif //PROJECT_1_IMAGE_PROCESSING_NAPCIO_TGACONTAINER_HPP