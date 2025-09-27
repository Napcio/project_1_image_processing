//
// Created by bigna on 9/21/2025.
//

#include <fstream>
#include "Pixel.hpp"
#include "TgaContainer.hpp"


TgaContainer::TgaContainer(const std::string &filename)
{
    // Set up filestream
    std::ifstream in(filename, std::ios::binary);
    if (!in)
    {
        throw std::ios_base::failure("Failed to open " + filename + " to load into TgaContainer.");
    }

    // Initialize header
    in.read(reinterpret_cast<char*>(&header_), sizeof(header_));

    // Allocate imageData_ array
    allocateImageData();
    // Initialize imageData_ array
    forEachPixel([&in](Pixel& pixel)
    {
        in.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));
    });

}

// Copy constructor
TgaContainer::TgaContainer(const TgaContainer& other)
{
    header_ = other.header_;

    allocateImageData();
    forEachPixelPair([](Pixel& pixel, const Pixel& otherPixel)
    {
        pixel = otherPixel;
    }, other);
}

// Move constructor
TgaContainer::TgaContainer(TgaContainer&& other) noexcept
{
    header_ = other.header_;

    imageData_ = other.imageData_;
    other.imageData_ = nullptr;
}

// Copy assignment
TgaContainer& TgaContainer::operator=(const TgaContainer& other)
{
    if (this == &other)
        return *this;

    header_ = other.header_;

    allocateImageData();
    forEachPixelPair([](Pixel& pixel, const Pixel& otherPixel)
    {
        pixel = otherPixel;
    }, other);

    return *this;
}

TgaContainer& TgaContainer::operator=(TgaContainer&& other) noexcept
{
    if (this == &other)
        return *this;

    header_ = other.header_;

    deleteImageData();
    imageData_ = other.imageData_;
    other.imageData_ = nullptr;

    return *this;
}


TgaContainer::~TgaContainer()
{
    deleteImageData();
}

TgaContainer& TgaContainer::multiply(const TgaContainer& other)
{
    forEachPixelPair([](Pixel& p1, const Pixel& p2)
    {
        p1.multiply(p2);
    }, other);
    return *this;
}

TgaContainer& TgaContainer::screen(const TgaContainer& other)
{
    forEachPixelPair([](Pixel& p1, const Pixel& p2)
    {
        p1.screen(p2);
    }, other);
    return *this;
}

TgaContainer& TgaContainer::subtract(const TgaContainer& other)
{
    forEachPixelPair([](Pixel& p1, const Pixel& p2)
    {
        p1.subtract(p2);
    }, other);
    return *this;
}

TgaContainer& TgaContainer::add(const TgaContainer& other)
{
    forEachPixelPair([](Pixel& p1, const Pixel& p2)
    {
        p1.add(p2);
    }, other);
    return *this;
}

TgaContainer& TgaContainer::overlay(const TgaContainer& other)
{
    forEachPixelPair([](Pixel& p1, const Pixel& p2)
    {
        p1.overlay(p2);
    }, other);
    return *this;
}

TgaContainer& TgaContainer::rotate180()
{
    const TgaContainer old(*this);
    for (size_t row = 0; row < header_.imageHeight; row++)
    {
        for (size_t col = 0; col < header_.imageWidth; col++)
        {
            imageData_[row][col] = old.imageData_[header_.imageHeight - 1 - row][header_.imageWidth - 1 - col];
        }
    }
    return *this;
}


TgaContainer& TgaContainer::forEachPixel(const std::function<void(Pixel&)>& func)
{
    for (size_t row = 0; row < header_.imageHeight; row++)
    {
        for (size_t col = 0; col < header_.imageWidth; col++)
        {
            func(imageData_[row][col]);
        }
    }
    return *this;
}

TgaContainer& TgaContainer::forEachPixelPair(const std::function<void(Pixel&, const Pixel&)>& func,
                                             const TgaContainer& other)
{
    if (header_.imageHeight != other.header_.imageHeight ||
        header_.imageWidth != other.header_.imageWidth)
    {
        throw std::runtime_error("TgaContainer.forEachPixelPair() cannot take a TgaContainer of different dimensions than the target.");
    }

    for (size_t row = 0; row < header_.imageHeight; row++)
    {
        for (size_t col = 0; col < header_.imageWidth; col++)
        {
            func(imageData_[row][col], other.imageData_[row][col]);
        }
    }
    return *this;
}

TgaContainer& TgaContainer::load(const std::string& filename)
{
    std::ofstream out(filename, std::ios::binary);

    out.write(reinterpret_cast<const char*>(&header_), sizeof(header_));
    forEachPixel([&out](Pixel& pixel)
    {
        out.write(reinterpret_cast<const char*>(&pixel), sizeof(pixel));
    });

    out.close();
    return *this;
}

void TgaContainer::deleteImageData()
{
    for (size_t i = 0; i < header_.imageHeight; i++)
    {
        delete[] imageData_[i];
    }
    delete[] imageData_;
    imageData_ = nullptr;
}

// Required header_ to be initialized
void TgaContainer::allocateImageData()
{
    imageData_ = new Pixel*[header_.imageHeight];
    for (size_t i = 0; i < header_.imageHeight; i++)
    {
        imageData_[i] = new Pixel[header_.imageWidth];
    }
}

