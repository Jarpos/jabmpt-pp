#include "types.hpp"
#include "transforms/transformations.hpp"

#include <fstream>
#include <iostream>
#include <string>

Image ReadImageFromBmp(const std::string& inpath);
void WriteImageToBmp(const std::string& path, const Image& image);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Given amount of args was not correct" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inpath = argv[1];
    std::string outpath = argv[2];

    Image image = ReadImageFromBmp(inpath);
    transform::Transformations.at('w').Function(image);
    transform::Transformations.at('y').Function(image);
    transform::Transformations.at('x').Function(image);
    WriteImageToBmp(outpath, image);

    return EXIT_SUCCESS;
}
