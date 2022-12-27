#include "types.hpp"

#include <fstream>
#include <iostream>
#include <string>

Image ReadImageFromBmp(const std::string& inpath);
void WriteImageToBmp(const std::string& path, const Image& image);

namespace transform {
void BlackAndWhite(Image& image);
void FlipX(Image& image);
void FlipY(Image& image);
} // namespace transform

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Given amount of args was not correct" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inpath = argv[1];
    std::string outpath = argv[2];

    Image image = ReadImageFromBmp(inpath);
    transform::BlackAndWhite(image);
    transform::FlipY(image);
    transform::FlipX(image);
    WriteImageToBmp(outpath, image);

    return EXIT_SUCCESS;
}
