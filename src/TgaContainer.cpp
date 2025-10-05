//
// Created by bigna on 9/21/2025.
//

#include <fstream>
#include "Pixel.hpp"
#include "TgaContainer.hpp"

#include <iostream>
#include <cmath>


TgaContainer::TgaContainer(const std::string& filename)
{
    // Set up filestream
    std::ifstream in(filename, std::ios::binary);
    if (!in)
    {
        throw std::ios_base::failure("Failed to open " + filename + " to load into TgaContainer.");
    }

    load(in);
}

TgaContainer::TgaContainer(std::ifstream& in)
{
    if (!in)
    {
        throw std::ios_base::failure("std::ifstream passed into TgaContainer constructor is invalid.");
    }
    load(in);
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

TgaContainer& TgaContainer::multiply(double factor)
{
    forEachPixel([&factor](Pixel& p)
    {
        p.multiply(factor);
    });
    return *this;
}

TgaContainer& TgaContainer::blur()
{
    // TODO: implement
    throw std::runtime_error("blur not implemented");
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

TgaContainer& TgaContainer::flip()
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

TgaContainer& TgaContainer::combine(const TgaContainer& green, const TgaContainer& blue)
{
    forEachPixelPair([](Pixel& pixel, const Pixel& other)
    {
        pixel.green = other.green;
    }, green).forEachPixelPair([](Pixel& pixel, const Pixel& other)
    {
        pixel.blue = other.blue;
    }, blue);
    return *this;
}

TgaContainer& TgaContainer::onlyRed()
{
    forEachPixel([](Pixel& pixel)
    {
        pixel.blue = pixel.red;
        pixel.green = pixel.red;
    });
    return *this;
}

TgaContainer& TgaContainer::onlyGreen()
{
    forEachPixel([](Pixel& pixel)
    {
        pixel.red = pixel.green;
        pixel.blue = pixel.green;
    });
    return *this;
}

TgaContainer& TgaContainer::onlyBlue()
{
    forEachPixel([](Pixel& pixel)
    {
        pixel.red = pixel.blue;
        pixel.green = pixel.blue;
    });
    return *this;
}

TgaContainer& TgaContainer::addRed(int x)
{
    forEachPixel([&x](Pixel& pixel)
    {
        pixel.red = Pixel::clamp(pixel.red + x);
    });
    return *this;
}

TgaContainer& TgaContainer::addGreen(int x)
{
    forEachPixel([&x](Pixel& pixel)
    {
        pixel.green = Pixel::clamp(pixel.green + x);
    });
    return *this;
}

TgaContainer& TgaContainer::addBlue(int x)
{
    forEachPixel([&x](Pixel& pixel)
    {
        pixel.blue = Pixel::clamp(pixel.blue + x);
    });
    return *this;
}

TgaContainer& TgaContainer::scaleRed(int x)
{
    forEachPixel([&x](Pixel& pixel)
    {
        pixel.red = Pixel::clamp(pixel.red * x);
    });
    return *this;
}

TgaContainer& TgaContainer::scaleGreen(int x)
{
    forEachPixel([&x](Pixel& pixel)
    {
        pixel.green = Pixel::clamp(pixel.green * x);
    });
    return *this;
}

TgaContainer& TgaContainer::scaleBlue(int x)
{
    forEachPixel([&x](Pixel& pixel)
    {
        pixel.blue = Pixel::clamp(pixel.blue * x);
    });
    return *this;
}

TgaContainer& TgaContainer::invert()
{
    forEachPixel([](Pixel& pixel)
    {
        pixel.invert();
    });
    return *this;
}

TgaContainer& TgaContainer::grayscale()
{
    forEachPixel([](Pixel& pixel)
    {
        pixel.grayscale();
    });
    return *this;
}

TgaContainer& TgaContainer::sepia()
{
    forEachPixel([](Pixel& pixel)
    {
        pixel.sepia();
    });
    return *this;
}

TgaContainer& TgaContainer::highlightEdges()
{
    applyKernel(laplacianEdgeDetection);
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

// Kernel must have an odd size in both x and y, such that there is a center
TgaContainer& TgaContainer::applyKernel(const KernelVec& kernel)
{
    if (!isKernel(kernel))
    {
        throw std::runtime_error("Invalid kernel passed to TgaContainer::applyKernel()");
    }
    std::pair<size_t, size_t> centerOffsets = {kernel.size() / 2.0, kernel[0].size() / 2.0}; // x, y
    const TgaContainer oldData(*this);

    // very disgusting code ahead beware
    // For every pixel
    for (size_t row = 0; row < header_.imageHeight; row++)
    {
        for (size_t col = 0; col < header_.imageWidth; col++)
        {
            size_t bottomBound;
            if (int indexOfTopOfKernel = (row - (kernel.size() / 2)); indexOfTopOfKernel < 0)
                bottomBound = -indexOfTopOfKernel;
            else
                bottomBound = 0;
            size_t topBound;
            if (int indexOfBottomOfKernel = row + (kernel.size() / 2); indexOfBottomOfKernel >= header_.imageHeight)
                topBound = indexOfBottomOfKernel - (header_.imageHeight - 1) + 1;
            else
                topBound = kernel.size();
            size_t leftBound;
            if (int indexOfLeftOfKernel = (col - (kernel[0].size() / 2)); indexOfLeftOfKernel < 0)
                leftBound = -indexOfLeftOfKernel;
            else
                leftBound = 0;
            size_t rightBound;
            if (int indexOfRightOfKernel = row + (kernel[0].size() / 2); indexOfRightOfKernel >= header_.imageWidth)
                rightBound = indexOfRightOfKernel - (header_.imageWidth - 1) + 1;
            else
                rightBound = kernel.size();

            // i realize this is dirty code but i cant think of another way to do it without rewriting a lot of things
            // 0 = red, 1 = green, 2 = blue
            int channel = 0;
            imageData_[row][col].forEachChannel([&](uint8_t& c)
            {
                double sum = 0;
                // For every element in the kernel that fits on the image, given the center
                for (size_t kernelRow = bottomBound; kernelRow < topBound; kernelRow++)
                {
                    for (size_t kernelCol = leftBound; kernelCol < rightBound; kernelCol++)
                    {
                        const Pixel& otherPixel = oldData.imageData_
                        [row - centerOffsets.second + kernelRow][col - centerOffsets.first + kernelCol];
                        double n;
                        // forgive me uncle bob
                        switch (channel)
                        {
                            case 0:
                                n = otherPixel.red;
                                break;
                            case 1:
                                n = otherPixel.green;
                                break;
                            case 2:
                                n = otherPixel.blue;
                                break;
                            default:
                                throw std::runtime_error("Error in applyKernel(),"
                                    " control should never default on switch statement. Channel number is "
                                    + std::to_string(channel));
                        }
                        sum += n * kernel[kernelRow][kernelCol];
                    }
                }
                c = Pixel::clamp(sum);
                channel++;
            });
        }
    }

    return *this;
}

TgaContainer& TgaContainer::save(const std::string& filename)
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


bool TgaContainer::isKernel(const KernelVec& vec)
{
    if (vec.empty() || vec.size() % 2 == 0 || vec[0].size() % 2 == 0)
    {
        return false;
    }
    // Ensure that all nested vectors are the same size
    size_t numColumns = vec[0].size();
    for (const std::vector<double>& row : vec)
    {
        if (row.size() != numColumns)
        {
            return false;
        }
    }
    return true;
}

KernelVec TgaContainer::createGaussianKernel(size_t xSize, size_t ySize, double standardDeviation)
{
    KernelVec kernel(ySize, std::vector<double>(xSize, 0));
    if (!isKernel(kernel))
    {
        throw std::runtime_error("Invalid size passed to createGaussianKernel()");
    }
    for (size_t row = 0; row < kernel.size(); row++)
    {
        for (size_t col = 0; col < kernel[0].size(); row++)
        {
            const int x = row - (kernel.size() / 2);
            const int y = col - (kernel[0].size() / 2);
            const double exponentDenominator = 2 * std::pow(standardDeviation, 2);

            kernel[row][col] = (1/(std::numbers::pi * exponentDenominator))
            * -std::pow(std::numbers::e, (x*x + y*y)/exponentDenominator);
        }
    }

    return kernel;
}

KernelVec TgaContainer::invertKernel(const KernelVec& kernel)
{
    if (!isKernel(kernel))
    {
        throw std::runtime_error("Invalid size passed to createGaussianKernel()");
    }
    KernelVec newKernel(kernel);
    for (std::vector<double>& vec : newKernel)
    {
        for (double& val : vec)
        {
            val = -val;
        }
    }
    return newKernel;
}

// Should only be called in the constructor, allocates imageData_
void TgaContainer::load(std::ifstream& in)
{
    in.read(reinterpret_cast<char*>(&header_), sizeof(header_));
    allocateImageData();

    // Initialize imageData_ array
    forEachPixel([&in](Pixel& pixel)
    {
        in.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));
    });
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

