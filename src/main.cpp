#include "transforms/transformations.hpp"
#include "types.hpp"

#include <fstream>
#include <iostream>
#include <string>

Image ReadImageFromBmp(const std::string& inpath);
void WriteImageToBmp(const std::string& path, const Image& image);

void PrintHelp();

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Given amount of args was not correct" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inpath = argv[1], outpath = argv[2];
    Image image = ReadImageFromBmp(inpath);

    PrintHelp();
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);
    while (input != "") {
        const auto& t = transforms::Transformations.find(input[0]);

        if (t == transforms::Transformations.end()) {
            std::cout << "Couldn't find function " << input[0] << "\n";
        } else {
            t->second.Function(image);
            std::cout << t->second.ActionDescription << "\n";
        }

        std::cout << "> ";
        std::getline(std::cin, input);
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

// transforms::Transformations.at('b').Function(image);
// transforms::Transformations.at('w').Function(image);
// transforms::Transformations.at('y').Function(image);
// transforms::Transformations.at('x').Function(image);
// transforms::Transformations.at('r').Function(image);
// transforms::Transformations.at('g').Function(image);
// transforms::Transformations.at('b').Function(image);
