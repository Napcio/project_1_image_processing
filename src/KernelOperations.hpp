//
// Created by bigna on 10/5/2025.
//

#ifndef PROJECT_1_IMAGE_PROCESSING_KERNELOPERATIONS_HPP
#define PROJECT_1_IMAGE_PROCESSING_KERNELOPERATIONS_HPP

#include <functional>
#include <vector>

using KernelVecValueType = double;
using KernelVecRow = std::vector<KernelVecValueType>;
using KernelVec = std::vector<KernelVecRow>;

namespace KernelOperations
{
    bool isKernel(const KernelVec& vec);

    KernelVec createGaussianKernel(size_t xSize, size_t ySize, double standardDeviation);
    KernelVec invertKernel(KernelVec kernel);
    KernelVec normalize(KernelVec kernel);

    KernelVec forEachElement(KernelVec kernel, const std::function<void(KernelVecValueType&)>& func);
}


#endif //PROJECT_1_IMAGE_PROCESSING_KERNELOPERATIONS_HPP