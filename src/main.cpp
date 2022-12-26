#include "types.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::string inpath = "../Hallway.bmp";
    std::string outpath = "../Out.bmp";

    std::ifstream infile(inpath, std::ios::in | std::ios::binary);
    if (!infile.is_open()) {
        std::cout << "Couldn't open " << inpath;
        return EXIT_FAILURE;
    }

    BitmapFileHeader_t fileHeader {};
    BitmapInfoHeader_t infoHeader {};
    infile.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    infile.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    infile.seekg(fileHeader.OffBits / 8, std::ios::beg);
    Image image(infoHeader.Width, infoHeader.Height);
    for (int i = 0; i < infoHeader.Height; i++) {
        infile.read(reinterpret_cast<char*>(&(image.Pixels[i])), infoHeader.Width * sizeof(RGBTriple));
        infile.seekg(image.Padding, std::ios::cur);
    }

    return EXIT_SUCCESS;
}
