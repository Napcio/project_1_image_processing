//
// Created by bigna on 9/27/2025.
//

#ifndef PROJECT_1_IMAGE_PROCESSING_METHOD_HPP
#define PROJECT_1_IMAGE_PROCESSING_METHOD_HPP

#include <functional>
#include <sstream>
#include <string>
#include <vector>

#include "TgaContainer.hpp"
#include "InputValidationExceptions.hpp"

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

    static std::string consumeInputFilename(const std::vector<std::string>& args, size_t& currentArg);
    static std::string consumeOutputFilename(const std::vector<std::string>& args, size_t& currentArg);

    static std::string consumeString(const std::vector<std::string>& args, size_t& currentArg);
    static int consumeInt(const std::vector<std::string>& args, size_t& currentArg);
    template <class T>
    static T consumeNum(const std::vector<std::string>& args, size_t& currentArg)
    {
        static_assert(std::is_arithmetic_v<T>, "consumeNum<T>() type must be arithmetic");

        if (currentArg >= args.size())
            throw InputValidationExceptions::MissingArgument();

        std::istringstream in(args[currentArg]);
        T x;
        in >> x;
        if (in.fail() || !in.eof())
        {
            if (std::is_integral_v<T>)
            {
                throw InputValidationExceptions::InvalidInteger();
            }
            if (std::is_floating_point_v<T>)
            {
                throw InputValidationExceptions::InvalidFloatingPoint();
            }
        }

        currentArg++;
        return x;
    }
};
#endif //PROJECT_1_IMAGE_PROCESSING_METHOD_HPP
