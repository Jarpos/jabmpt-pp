#pragma once

#include <cstdint>
#include <vector>

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

struct BitmapFileHeader_t;
struct BitmapInfoHeader_t;
struct RgbValue;
struct Image;

#pragma pack(1)
struct RgbValue {
    RgbValue() : RgbValue(0, 0, 0) {}
    RgbValue(BYTE red, BYTE green, BYTE blue) : Red(red), Green(green), Blue(blue) {}

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
};
#pragma pack()

struct Image {
    Image(LONG width, LONG height) : Pixels(height, std::vector<RgbValue>(width, RgbValue())) {}

    std::vector<std::vector<RgbValue>> Pixels;

    size_t Width() const {
        return Pixels.at(0).size();
    }

    size_t Height() const {
        return Pixels.size();
    }

    BYTE Padding() const {
        return 4 - (Width() * sizeof(RgbValue) % 4) % 4;
    }

    const RgbValue& At(size_t y, size_t x) const {
        return Pixels.at(y).at(x);
    }

    RgbValue& At(size_t y, size_t x) {
        return Pixels.at(y).at(x);
    }
};
