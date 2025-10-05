//
// Created by bigna on 10/5/2025.
//

#include "KernelOperations.hpp"

#include <cmath>
#include <functional>
#include <stdexcept>

namespace KernelOperations
{
    bool isKernel(const KernelVec& vec)
    {
        if (vec.empty() || vec.size() % 2 == 0 || vec[0].size() % 2 == 0)
        {
            return false;
        }
        // Ensure that all nested vectors are the same size
        size_t numColumns = vec[0].size();
        for (const KernelVecRow& row : vec)
        {
            if (row.size() != numColumns)
            {
                return false;
            }
        }
        return true;
    }

    // TODO: Fix artifacting on top and right edge when applying large gaussian kernels, may be an issue w/ applyKernel()
    KernelVec createGaussianKernel(size_t xSize, size_t ySize, double standardDeviation)
    {
        KernelVec kernel(ySize, KernelVecRow(xSize, 0));
        if (!isKernel(kernel))
        {
            throw std::runtime_error("Invalid size passed to createGaussianKernel()");
        }

        const double twoSigmaSquared = 2 * std::pow(standardDeviation, 2);
        const double multiplier = 1 / (std::numbers::pi * twoSigmaSquared);
        for (size_t row = 0; row < kernel.size(); row++)
        {
            for (size_t col = 0; col < kernel[0].size(); col++)
            {
                const int y = row - (kernel.size() / 2);
                const int x = col - (kernel[0].size() / 2);

                kernel[row][col] = multiplier * std::exp(-(x*x + y*y)/twoSigmaSquared);
            }
        }
        kernel = normalize(std::move(kernel));
        return kernel;
    }

    KernelVec invertKernel(KernelVec kernel)
    {
        if (!isKernel(kernel))
        {
            throw std::runtime_error("Invalid size passed to createGaussianKernel()");
        }
        for (KernelVecRow& vec : kernel)
        {
            for (double& val : vec)
            {
                val = -val;
            }
        }
        return kernel;
    }

    KernelVec normalize(KernelVec kernel)
    {
        double sum = 0;
        forEachElement(kernel, [&sum](const KernelVecValueType& val)
        {
            sum += val;
        });

        kernel = forEachElement(kernel, [&sum](KernelVecValueType& val)
        {
            val /= sum;
        });
        return kernel;
    }

    KernelVec forEachElement(KernelVec kernel, const std::function<void(KernelVecValueType&)>& func)
    {
        for (KernelVecRow& vec : kernel)
        {
            for (KernelVecValueType& element : vec)
            {
                func(element);
            }
        }
        return kernel;
    }
}