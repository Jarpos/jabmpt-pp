#pragma once

#include <array>
#include <cstdint>
#include <functional>
#include <list>
#include <vector>

struct RgbValue;
struct Image;

#pragma pack(1)
struct RgbValue {
    RgbValue() : RgbValue(0, 0, 0) {}
    RgbValue(uint8_t red, uint8_t green, uint8_t blue) : Red(red), Green(green), Blue(blue) {}

    // Members have to be sorted like this, because of Endianess
    uint8_t Blue;  // Blue channel
    uint8_t Green; // Green channel
    uint8_t Red;   // Red channel

    constexpr void Set(uint8_t red, uint8_t green, uint8_t blue) {
        Red = red;
        Green = green;
        Blue = blue;
    }

    void Set(RgbValue r) {
        Set(r.Red, r.Green, r.Blue);
    }

    constexpr void SetAll(uint8_t value) {
        Set(value, value, value);
    }

    constexpr uint8_t Average() const {
        // TODO: Fix possible overflow problem
        return (Red + Green + Blue) / 3;
    }
};
#pragma pack()

struct Image {
    Image(const Image& image) = default;
    Image(size_t width, size_t height) : Pixels(height, std::vector<RgbValue>(width, RgbValue())) {}

    std::vector<std::vector<RgbValue>> Pixels;

    size_t Width() const;
    size_t Height() const;

    RgbValue& At(size_t y, size_t x);
    const RgbValue& At(size_t y, size_t x) const;

    std::list<RgbValue> GetSurrounding(size_t y, size_t x);
    int GetSurroundingQuick(size_t y, size_t x, std::array<RgbValue, 9>& result);

    void ForEachPixel(std::function<void(RgbValue&)> fnc);
};
