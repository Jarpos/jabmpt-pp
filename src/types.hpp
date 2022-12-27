#pragma once

#include <cstdint>
#include <vector>

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

struct BitmapFileHeader_t;
struct BitmapInfoHeader_t;
struct RGBTriple;
struct Image;

#pragma pack(1)
struct RGBTriple {
    RGBTriple() : RGBTriple(0, 0, 0) {}
    RGBTriple(BYTE red, BYTE green, BYTE blue) : Red(red), Green(green), Blue(blue) {}

    // Members have to be sorted like this, because of Endianess
    BYTE Blue;  // Blue channel
    BYTE Green; // Green channel
    BYTE Red;   // Red channel

    void Set(BYTE red, BYTE green, BYTE blue) {
        Red = red;
        Green = green;
        Blue = blue;
    }
};
#pragma pack()

struct Image {
    Image(LONG width, LONG height) : Pixels(height, std::vector<RGBTriple>(width, RGBTriple())) {}

    std::vector<std::vector<RGBTriple>> Pixels;

    constexpr LONG Width() const {
        return Pixels.at(0).size();
    }

    constexpr LONG Height() const {
        return Pixels.size();
    }

    constexpr BYTE Padding() const {
        return 4 - (Width() * sizeof(RGBTriple) % 4) % 4;
    }
};
