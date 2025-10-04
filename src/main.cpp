//
// Created by bigna on 9/21/2025.
//

#include <filesystem>
#include <fstream>
#include <iostream>

#include "InputValidationExceptions.hpp"
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
    if (std::filesystem::current_path().filename() == "cmake-build-debug")
    {
        std::filesystem::current_path(std::filesystem::current_path().parent_path());
    }

    const std::vector<Method> methods = {
        Method("multiply", [](std::vector<TgaContainer>& targets, const std::vector<std::string>& args, size_t& currentArg)
        {
            const TgaContainer other(Method::consumeInputFilename(args, currentArg));
            for (TgaContainer& target : targets)
            {
                target.multiply(other);
            }
        }),
        Method("subtract", [](std::vector<TgaContainer>& targets, const std::vector<std::string>& args, size_t& currentArg)
        {
            const TgaContainer other(Method::consumeInputFilename(args, currentArg));
            for (TgaContainer& target : targets)
            {
                target.subtract(other);
            }
        }),
        Method("overlay", [](std::vector<TgaContainer>& targets, const std::vector<std::string>& args, size_t& currentArg)
        {
            const TgaContainer other(Method::consumeInputFilename(args, currentArg));
            for (TgaContainer& target : targets)
            {
                target.overlay(other);
            }
        }),
        Method("screen", [](std::vector<TgaContainer>& targets, const std::vector<std::string>& args, size_t& currentArg)
        {
            const TgaContainer other(Method::consumeInputFilename(args, currentArg));
            for (TgaContainer& target : targets)
            {
                target.screen(other);
            }
        }),
        Method("combine", [](std::vector<TgaContainer>& targets, const std::vector<std::string>& args, size_t& currentArg)
        {
            const TgaContainer green = TgaContainer(Method::consumeInputFilename(args, currentArg));
            const TgaContainer blue = TgaContainer(Method::consumeInputFilename(args, currentArg));
            for (TgaContainer& target : targets)
            {
                target.combine(green, blue);
            }
        }),
        Method("flip", [](std::vector<TgaContainer>& targets, [[maybe_unused]] const std::vector<std::string>& args, [[maybe_unused]] size_t& currentArg)
        {
            for (TgaContainer& target : targets)
            {
                target.flip();
            }
        }),
        Method("onlyred", [](std::vector<TgaContainer>& targets, [[maybe_unused]] const std::vector<std::string>& args, [[maybe_unused]] size_t& currentArg)
        {
            for (TgaContainer& target : targets)
            {
                target.onlyRed();
            }
        }),
        Method("onlygreen", [](std::vector<TgaContainer>& targets, [[maybe_unused]] const std::vector<std::string>& args, [[maybe_unused]] size_t& currentArg)
        {
            for (TgaContainer& target : targets)
            {
                target.onlyGreen();
            }
        }),
        Method("onlyblue", [](std::vector<TgaContainer>& targets, [[maybe_unused]] const std::vector<std::string>& args, [[maybe_unused]] size_t& currentArg)
        {
            for (TgaContainer& target : targets)
            {
                target.onlyBlue();
            }
        }),
        Method("addred", [](std::vector<TgaContainer>& targets, const std::vector<std::string>& args, size_t& currentArg)
        {
            const int offset = Method::consumeInt(args, currentArg);
            for (TgaContainer& target : targets)
            {
                target.addRed(offset);
            }
        }),
        Method("addgreen", [](std::vector<TgaContainer>& targets, const std::vector<std::string>& args, size_t& currentArg)
        {
            const int offset = Method::consumeInt(args, currentArg);
            for (TgaContainer& target : targets)
            {
                target.addGreen(offset);
            }
        }),
        Method("addblue", [](std::vector<TgaContainer>& targets, const std::vector<std::string>& args, size_t& currentArg)
        {
            const int offset = Method::consumeInt(args, currentArg);
            for (TgaContainer& target : targets)
            {
                target.addBlue(offset);
            }
        }),
        Method("scalered", [](std::vector<TgaContainer>& targets, const std::vector<std::string>& args, size_t& currentArg)
        {
            const int factor = Method::consumeInt(args, currentArg);
            for (TgaContainer& target : targets)
            {
                target.scaleRed(factor);
            }
        }),
        Method("scalegreen", [](std::vector<TgaContainer>& targets, const std::vector<std::string>& args, size_t& currentArg)
        {
            const int factor = Method::consumeInt(args, currentArg);
            for (TgaContainer& target : targets)
            {
                target.scaleGreen(factor);
            }
        }),
        Method("scaleblue", [](std::vector<TgaContainer>& targets, const std::vector<std::string>& args, size_t& currentArg)
        {
            const int factor = Method::consumeInt(args, currentArg);
            for (TgaContainer& target : targets)
            {
                target.scaleBlue(factor);
            }
        })
    };

    // Turn arguments to vector of strings
    const std::vector<std::string> args(argv, argv + argc);
    size_t currentArg = 1;

    if (argc == 1 || args[1] == "--help")
    {
        printHelp();
        return 0;
    }

    // Input validation for first 2 args
    const std::string INV_FILENAME = "Invalid file name.";
    const std::string FILE_DNE = "File does not exist.";
    const std::string MISSING_INPUT = "No input file(s) specified.";
    const std::string NO_PROVIDED_METHODS = "No methods specified, image has been saved without performing any operations.";

    std::string outputPathTemp;
    try
    {
        outputPathTemp = Method::consumeOutputFilename(args, currentArg);
    }
    catch (InputValidationExceptions::MissingArgument&) { throw; } // This should never happen
    catch (InputValidationExceptions::InvalidFilename&)
    {
        std::cout << INV_FILENAME << std::endl;
        return -1;
    }
    const std::string outputPath = std::move(outputPathTemp);

    // Populate targets
    std::vector<TgaContainer> targets;
    bool filenameArgFound = true;
    do
    {
        try
        {
            targets.emplace_back(Method::consumeInputFilename(args, currentArg));
        }
        catch (const InputValidationExceptions::MissingArgument&)
        {
            if (targets.empty())
            {
                std::cout << MISSING_INPUT << std::endl;
                return -1;
            }
            std::cout << NO_PROVIDED_METHODS << std::endl;
            targets[0].save(outputPath);
            return 0;
        }
        catch (const InputValidationExceptions::InvalidFilename&)
        {
            if (targets.empty())
            {
                std::cout << INV_FILENAME << std::endl;
                return -1;
            } // otherwise allow the argument to fall through
            filenameArgFound = false;
        }
        catch (const InputValidationExceptions::FileDNE&)
        {
            if (targets.empty())
            {
                std::cout << FILE_DNE << std::endl;
                return -1;
            } // otherwise allow the argument to fall through
            filenameArgFound = false;
        }
    } while (filenameArgFound);

    // Parse methods
    while (currentArg < args.size())
    {
        bool isMethodSuccessful = false;
        for (const Method& m : methods)
        {
            if (args[currentArg] == m.name)
            {
                currentArg++;
                isMethodSuccessful = m.run(targets, args, currentArg);
                if (!isMethodSuccessful)
                {
                    // Method class should handle user-facing error messages
                    return -1;
                }
                break;
            }
        }
        if (!isMethodSuccessful) // If the program got here and this evaluates to true, no matching method was found
        {
            std::cout << InputValidationExceptions::ErrorMessages::INV_METHOD << std::endl;
            return -1;
        }
    }
    targets[0].save(outputPath);
    return 0;
}

