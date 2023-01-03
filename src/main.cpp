#include "transforms/transformations.hpp"
#include "types.hpp"

#include <fstream>
#include <iostream>
#include <string>

Image ReadImageFromBmp(const std::string& inpath);
void WriteImageToBmp(const std::string& path, const Image& image);

void PrintHelp();
std::string GetInput();

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Given amount of args was not correct" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inpath = argv[1], outpath = argv[2];
    Image image = ReadImageFromBmp(inpath);

    PrintHelp();
    std::string input;
    while ((input = GetInput()) != "") {
        const auto& t = transforms::Transformations.find(input[0]);
        if (t != transforms::Transformations.end()) {
            t->second.Function(image);
            std::cout << t->second.ActionDescription << "\n";
        } else {
            std::cout << "Couldn't find transformation " << input[0] << "\n";
        }
    }

    WriteImageToBmp(outpath, image);

    return EXIT_SUCCESS;
}

void PrintHelp() {
    for (const auto& k : transforms::Transformations) {
        std::cout << k.first << ": " << k.second.HelpDescription << "\n";
    }
    std::cout << "\n";
}

std::string GetInput() {
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);
    return input;
}
