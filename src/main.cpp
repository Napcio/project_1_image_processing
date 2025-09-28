//
// Created by bigna on 9/21/2025.
//

#include <filesystem>
#include <fstream>
#include <iostream>

#include "TgaContainer.hpp"
#include "Pixel.hpp"
#include "Method.hpp"

void milestone1(); // Defined in Milestone1.cpp

void printHelp()
{
    std::cout
    << "Project 1: Image Processing, Fall 2025\n\n"
    << "Usage:\n"
    << "\t./project1.out [output] [firstImage] [method] [...]" << std::endl;
}

int main(int argc, char* argv[])
{
    // milestone1();
    const std::vector<Method> methods = {
        Method("multiply", [](TgaContainer& target, const std::vector<std::string>& args, size_t& currentArg)
        {
            target.multiply(TgaContainer(Method::consumeFilenameInput(args, currentArg)));
        }),
        Method("subtract", [](TgaContainer& target, const std::vector<std::string>& args, size_t& currentArg)
        {
            target.subtract(TgaContainer(Method::consumeFilenameInput(args, currentArg)));
        }),
        Method("overlay", [](TgaContainer& target, const std::vector<std::string>& args, size_t& currentArg)
        {
            target.overlay(TgaContainer(Method::consumeFilenameInput(args, currentArg)));
        }),
        Method("screen", [](TgaContainer& target, const std::vector<std::string>& args, size_t& currentArg)
        {
            target.screen(TgaContainer(Method::consumeFilenameInput(args, currentArg)));
        }),
        Method("combine", [](TgaContainer& target, const std::vector<std::string>& args, size_t& currentArg)
        {
            target.combine(
                TgaContainer(Method::consumeFilenameInput(args, currentArg)),
                TgaContainer(Method::consumeFilenameInput(args, currentArg))
                );
        }),
        Method("flip", [](TgaContainer& target, [[maybe_unused]] const std::vector<std::string>& args, [[maybe_unused]] size_t& currentArg)
        {
            target.flip();
        }),
        Method("onlyred", [](TgaContainer& target, [[maybe_unused]] const std::vector<std::string>& args, [[maybe_unused]] size_t& currentArg)
        {
            target.onlyRed();
        }),
        Method("onlygreen", [](TgaContainer& target, [[maybe_unused]] const std::vector<std::string>& args, [[maybe_unused]] size_t& currentArg)
        {
            target.onlyGreen();
        }),
        Method("onlyblue", [](TgaContainer& target, [[maybe_unused]] const std::vector<std::string>& args, [[maybe_unused]] size_t& currentArg)
        {
            target.onlyBlue();
        }),
        Method("addred", [](TgaContainer& target, const std::vector<std::string>& args, size_t& currentArg)
        {
            target.addRed(Method::consumeInt(args, currentArg));
        }),
        Method("addgreen", [](TgaContainer& target, const std::vector<std::string>& args, size_t& currentArg)
        {
            target.addGreen(Method::consumeInt(args, currentArg));
        }),
        Method("addblue", [](TgaContainer& target, const std::vector<std::string>& args, size_t& currentArg)
        {
            target.addBlue(Method::consumeInt(args, currentArg));
        }),
        Method("scalered", [](TgaContainer& target, const std::vector<std::string>& args, size_t& currentArg)
        {
            target.scaleRed(Method::consumeInt(args, currentArg));
        }),
        Method("scalegreen", [](TgaContainer& target, const std::vector<std::string>& args, size_t& currentArg)
        {
            target.scaleGreen(Method::consumeInt(args, currentArg));
        }),
        Method("scaleblue", [](TgaContainer& target, const std::vector<std::string>& args, size_t& currentArg)
        {
            target.scaleBlue(Method::consumeInt(args, currentArg));
        })
    };


    const std::vector<std::string> args(argv, argv + argc);
    size_t currentArg = 1;

    if (argc == 1 || args[1] == "--help")
    {
        printHelp();
        return 0;
    }

    const std::string INV_FILENAME = "Invalid file name.";
    const std::string FILE_DNE = "File does not exist.";
    // Input validation for first 2 args
    if (std::filesystem::path(args[currentArg]).extension() != ".tga" || !std::ifstream(args[currentArg]))
    {
        std::cout << INV_FILENAME << std::endl;
        return -1;
    }
    if (!std::ifstream(args[currentArg]))
    {
        std::cout << FILE_DNE << std::endl;
        return -1;
    }
    const std::string& outputPath = args[currentArg++];
    // if (currentArg >= args.size())
    //     handleError(ErrorMessages::MISSING_ARG);

    if (std::filesystem::path(args[currentArg]).extension() != ".tga")
    {
        std::cout << INV_FILENAME << std::endl;
        return -1;
    }
    const std::string& inputPath = args[currentArg++];

    TgaContainer target(inputPath);

    while (currentArg < args.size())
    {
        bool isMethodSuccessful = false;
        for (const Method& m : methods)
        {
            if (args[currentArg] == m.name)
            {
                currentArg++;
                isMethodSuccessful = m.run(target, args, currentArg);
                if (!isMethodSuccessful)
                {
                    // Method class should handle user-facing error messages
                    return -1;
                }
            }
        }
        if (!isMethodSuccessful) // If the program got here and this evaluates to true, no matching method was found
        {
            std::cout << ErrorMessages::INV_METHOD << std::endl;
            return -1;
        }
    }
    target.save(outputPath);
    return 0;
}

