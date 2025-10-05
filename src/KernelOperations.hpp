//
// Created by bigna on 10/5/2025.
//

#ifndef PROJECT_1_IMAGE_PROCESSING_KERNELOPERATIONS_HPP
#define PROJECT_1_IMAGE_PROCESSING_KERNELOPERATIONS_HPP

#include <vector>

using KernelVec = std::vector<std::vector<double>>;

namespace KernelOperations
{
    bool isKernel(const KernelVec& vec);

    KernelVec createGaussianKernel(size_t xSize, size_t ySize, double standardDeviation);
    KernelVec invertKernel(KernelVec kernel);
}


#endif //PROJECT_1_IMAGE_PROCESSING_KERNELOPERATIONS_HPP