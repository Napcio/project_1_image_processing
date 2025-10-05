//
// Created by bigna on 10/4/2025.
//

#ifndef PROJECT_1_IMAGE_PROCESSING_INPUTVALIDATIONEXCEPTIONS_HPP
#define PROJECT_1_IMAGE_PROCESSING_INPUTVALIDATIONEXCEPTIONS_HPP

#include <stdexcept>

namespace InputValidationExceptions
{
    class InvalidArgument : public std::runtime_error
    {
    public:
        InvalidArgument(const std::string& msg) : std::runtime_error(msg) {}
    };

    class InvalidFilename : public InvalidArgument
    {
    public:
        InvalidFilename() : InvalidArgument("Invalid argument, invalid file name.") {}
    };

    class FileDNE : public InvalidArgument
    {
    public:
        FileDNE() : InvalidArgument("Invalid argument, file does not exist.") {}
    };

    class InvalidInteger : public InvalidArgument
    {
    public:
        InvalidInteger() : InvalidArgument("Invalid argument, expected number.") {}
    };

    class InvalidFloatingPoint : public InvalidArgument
    {
    public:
        InvalidFloatingPoint() : InvalidArgument("Invalid argument, expected floating point number.") {}
    };

    class MissingArgument : public InvalidArgument
    {
    public:
        MissingArgument() : InvalidArgument("Missing argument.") {}
    };

    namespace ErrorMessages
    {
        const std::string INV_METHOD = "Invalid method name.";
    }
}



#endif //PROJECT_1_IMAGE_PROCESSING_INPUTVALIDATIONEXCEPTIONS_HPP