#include "types.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Given amount of args was not correct" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inpath = argv[1];
    std::string outpath = argv[2];

    std::ifstream ifile(inpath, std::ios::in | std::ios::binary);
    if (!ifile.is_open()) {
        std::cout << "Couldn't open input file " << inpath << std::endl;
        return EXIT_FAILURE;
    }

    BitmapFileHeader_t fileHeader {};
    BitmapInfoHeader_t infoHeader {};
    ifile.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    ifile.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    ifile.seekg(fileHeader.OffBits, std::ios::beg);
    Image image(infoHeader.Width, infoHeader.Height);
    for (int i = 0; i < infoHeader.Height; i++) {
        ifile.read(reinterpret_cast<char*>(&(image.Pixels[i][0])), infoHeader.Width * sizeof(RGBTriple));
        ifile.seekg(image.Padding(), std::ios::cur);
    }

    std::ofstream ofile(outpath, std::ios::out | std::ios::binary);
    if (!ofile.is_open()) {
        std::cout << "Couldn't open output file " << outpath << std::endl;
        return EXIT_FAILURE;
    }

    ofile.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    ofile.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    for (int i = 0; i < infoHeader.Height; i++) {
        ofile.write(reinterpret_cast<char*>(&(image.Pixels[i][0])), infoHeader.Width * sizeof(RGBTriple));
        for (int j = 0; j < image.Padding(); j++) {
            ofile.write("\0", sizeof(BYTE));
        }
    }

    return EXIT_SUCCESS;
}
