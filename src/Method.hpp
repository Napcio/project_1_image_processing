//
// Created by bigna on 9/27/2025.
//

#ifndef PROJECT_1_IMAGE_PROCESSING_METHOD_HPP
#define PROJECT_1_IMAGE_PROCESSING_METHOD_HPP
#include <functional>
#include <string>
#include <vector>

#include "TgaContainer.hpp"

// namespace ErrorMessages
// {
//     const std::string INV_FILENAME = "Invalid argument, invalid file name.";
//     const std::string FILE_DNE = "Invalid argument, file does not exist.";
//     const std::string INV_INT = "Invalid argument, expected number.";
//
//     const std::string MISSING_ARG = "Missing argument.";
//
//     const std::string INV_METHOD = "Invalid method name.";
//
//     const std::string ARG_EXCEPTION_MESSAGE = "Argument error";
// }

struct Method
{
    std::string name;

    /**
     * Vector is the complete list of args, size_t& is the currentArg index, to be updated as arguments are consumed.
     * Arguments should be consumed in the order that they are to be inputted using the static member functions in
     * Method which will automatically update the currentArg index. Input validity is handled by the static member
     * functions.
     */
    std::function<void(std::vector<TgaContainer>&, const std::vector<std::string>&, size_t&)> operation;

    Method(const std::string& n, const std::function<void(std::vector<TgaContainer>&, const std::vector<std::string>&, size_t&)>& o);

    // Returns true if the operation was successful, false otherwise
    bool run(std::vector<TgaContainer>& targets, const std::vector<std::string>& args, size_t& currentArg) const;

    static std::string consumeFilenameInput(const std::vector<std::string>& args, size_t& currentArg);
    static std::string consumeFilenameOutput(const std::vector<std::string>& args, size_t& currentArg);

    static std::string consumeString(const std::vector<std::string>& args, size_t& currentArg);
    static int consumeInt(const std::vector<std::string>& args, size_t& currentArg);


private:
    static void handleError(const std::string& errorMessage);
};
#endif //PROJECT_1_IMAGE_PROCESSING_METHOD_HPP
