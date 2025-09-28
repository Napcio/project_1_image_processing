//
// Created by bigna on 9/27/2025.
//

#include "Method.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Method::Method(const std::string& n, const std::function<void(TgaContainer&, const std::vector<std::string>&, size_t&)>& o)
    : name(n), operation(o) {}

bool Method::run(TgaContainer& target, const std::vector<std::string>& args, size_t& currentArg) const
{
    try
    {
        operation(target, args, currentArg);
    }
    catch (const std::runtime_error& e)
    {
        if (std::string(e.what()) == ErrorMessages::ARG_EXCEPTION_MESSAGE)
            return false;
        throw;
    }
    return true;
}

std::string Method::consumeFilenameInput(const std::vector<std::string>& args, size_t& currentArg)
{
    if (currentArg >= args.size())
        handleError(ErrorMessages::MISSING_ARG);

    if (!std::ifstream(args[currentArg]))
        handleError(ErrorMessages::FILE_DNE);
    if (std::filesystem::path(args[currentArg]).extension() != ".tga")
        handleError(ErrorMessages::INV_FILENAME);

    return args[currentArg++];
}

std::string Method::consumeFilenameOutput(const std::vector<std::string>& args, size_t& currentArg)
{
    if (currentArg >= args.size())
        handleError(ErrorMessages::MISSING_ARG);

    if (std::filesystem::path(args[currentArg]).extension() != ".tga")
        handleError(ErrorMessages::INV_FILENAME);

    return args[currentArg++];
}

std::string Method::consumeString(const std::vector<std::string>& args, size_t& currentArg)
{
    if (currentArg >= args.size())
        handleError(ErrorMessages::MISSING_ARG);

    return args[currentArg++];
}

int Method::consumeInt(const std::vector<std::string>& args, size_t& currentArg)
{
    if (currentArg >= args.size())
        handleError(ErrorMessages::MISSING_ARG);

    std::istringstream in(args[currentArg]);
    int x;
    in >> x;
    if (in.fail() || !in.eof())
        handleError(ErrorMessages::INV_INT);

    currentArg++;
    return x;
}

void Method::handleError(const std::string& errorMessage)
{
    std::cout << errorMessage << std::endl;
    throw std::runtime_error(ErrorMessages::ARG_EXCEPTION_MESSAGE);
}
