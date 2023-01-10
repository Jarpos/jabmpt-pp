#include "image.hpp"

#include <array>
#include <cstdint>
#include <functional>
#include <list>
#include <vector>

size_t Image::Width() const {
    return Pixels.at(0).size();
}

size_t Image::Height() const {
    return Pixels.size();
}

RgbValue& Image::At(size_t y, size_t x) {
    return Pixels.at(y).at(x);
}

const RgbValue& Image::At(size_t y, size_t x) const {
    return At(y, x);
}

std::list<RgbValue> Image::GetSurrounding(size_t y, size_t x) {
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

int Image::GetSurroundingQuick(size_t y, size_t x, std::array<RgbValue, 9>& result) {
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

void Image::ForEachPixel(std::function<void(RgbValue&)> fnc) {
    for (auto& line : Pixels) {
        for (auto& pixel : line) {
            fnc(pixel);
        }
    }
}
