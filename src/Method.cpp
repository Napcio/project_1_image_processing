//
// Created by bigna on 9/27/2025.
//

#include "Method.hpp"
#include "InputValidationExceptions.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <concepts>

Method::Method(const std::string& n, const std::function<void(std::vector<TgaContainer>&, const std::vector<std::string>&, size_t&)>& o)
    : name(n), operation(o) {}

bool Method::run(std::vector<TgaContainer>& targets, const std::vector<std::string>& args, size_t& currentArg) const
{
    try
    {
        operation(targets, args, currentArg);
    }
    catch (const InputValidationExceptions::InvalidArgument& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

std::string Method::consumeInputFilename(const std::vector<std::string>& args, size_t& currentArg)
{
    if (currentArg >= args.size())
        throw InputValidationExceptions::MissingArgument();

    if (std::filesystem::path(args[currentArg]).extension() != ".tga")
        throw InputValidationExceptions::InvalidFilename();
    if (!std::ifstream(args[currentArg]))
        throw InputValidationExceptions::FileDNE();


    return args[currentArg++];
}

std::string Method::consumeOutputFilename(const std::vector<std::string>& args, size_t& currentArg)
{
    if (currentArg >= args.size())
        throw InputValidationExceptions::MissingArgument();

    if (std::filesystem::path(args[currentArg]).extension() != ".tga")
        throw InputValidationExceptions::InvalidFilename();

    return args[currentArg++];
}

std::string Method::consumeString(const std::vector<std::string>& args, size_t& currentArg)
{
    if (currentArg >= args.size())
        throw InputValidationExceptions::MissingArgument();

    return args[currentArg++];
}

int Method::consumeInt(const std::vector<std::string>& args, size_t& currentArg)
{
    if (currentArg >= args.size())
        throw InputValidationExceptions::MissingArgument();

    std::istringstream in(args[currentArg]);
    int x;
    in >> x;
    if (in.fail() || !in.eof())
        throw InputValidationExceptions::InvalidInteger();

    currentArg++;
    return x;
}
