//
// Created by bigna on 10/5/2025.
//

#include "KernelOperations.hpp"

#include <cmath>
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
        for (const std::vector<double>& row : vec)
        {
            if (row.size() != numColumns)
            {
                return false;
            }
        }
        return true;
    }

    KernelVec createGaussianKernel(size_t xSize, size_t ySize, double standardDeviation)
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

    KernelVec invertKernel(KernelVec kernel)
    {
        if (!isKernel(kernel))
        {
            throw std::runtime_error("Invalid size passed to createGaussianKernel()");
        }
        for (std::vector<double>& vec : kernel)
        {
            for (double& val : vec)
            {
                val = -val;
            }
        }
        return kernel;
    }
}