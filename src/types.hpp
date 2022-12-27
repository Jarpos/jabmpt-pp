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

    constexpr void Set(BYTE red, BYTE green, BYTE blue) {
        Red = red;
        Green = green;
        Blue = blue;
    }

    constexpr void SetAll(BYTE value) {
        Set(value, value, value);
    }

    constexpr BYTE Average() const {
        return (Red + Green + Blue) / 3;
    }

    static const RGBTriple Null() {
        return RGBTriple();
    }
};
#pragma pack()

struct Image {
    Image(LONG width, LONG height) : Pixels(height, std::vector<RGBTriple>(width, RGBTriple())) {}

    std::vector<std::vector<RGBTriple>> Pixels;

    constexpr size_t Width() const {
        return Pixels.at(0).size();
    }

    constexpr size_t Height() const {
        return Pixels.size();
    }

    constexpr BYTE Padding() const {
        return 4 - (Width() * sizeof(RGBTriple) % 4) % 4;
    }

    RGBTriple& Get(size_t y, size_t x, RGBTriple def = RGBTriple {}) {
        return (y < Height() && x < Width()) ? Pixels[y][x] : def;
    }
};
