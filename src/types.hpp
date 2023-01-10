#pragma once

#include <array>
#include <cstdint>
#include <functional>
#include <list>
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

    void Set(RgbValue r) {
        Set(r.Red, r.Green, r.Blue);
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

    Image(const Image& image) = default;

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

    std::list<RgbValue> GetSurrounding(size_t y, size_t x) {
        constexpr std::array<std::pair<int, int>, 9> Indices = {
            std::pair { -1, -1 }, { -1, +0 }, { -1, +1 },
            /*******/ { +0, -1 }, { +0, +0 }, { +0, +1 },
            /*******/ { +1, -1 }, { +1, +0 }, { +1, +1 },
        };

        std::list<RgbValue> surrounding {};
        for (const auto& i : Indices) {
            if (y + i.first >= 0 && y + i.first < Height()) {
                if (x + i.second >= 0 && x + i.second < Width()) {
                    surrounding.emplace_back(At(y + i.first, x + i.second));
                }
            }
        }

        return surrounding;
    }

    int GetSurroundingQuick(size_t y, size_t x, std::array<RgbValue, 9>& result) {
        int count = 0;
        for (int yc = -1; yc < 2; yc++) {
            for (int xc = -1; xc < 2; xc++) {
                if (y + yc >= 0 && y + yc < Height()) {
                    if (x + xc >= 0 && x + xc < Width()) {
                        result[count++] = At(y + yc, x + xc);
                    }
                }
            }
        }

        return count;
    }

    void ForEachPixel(std::function<void(RgbValue&)> fnc) {
        for (auto& line : Pixels) {
            for (auto& pixel : line) {
                fnc(pixel);
            }
        }
    }
};
