#include "../types.hpp"

#include <algorithm>

namespace transforms {

void DisableRedChannel(Image& image) {
    for (auto& line : image.Pixels) {
        std::for_each(line.begin(), line.end(), [&](RgbValue& pixel) {
            pixel.Red = 0;
        });
    }
}

void DisableGreenChannel(Image& image) {
    for (auto& line : image.Pixels) {
        std::for_each(line.begin(), line.end(), [&](RgbValue& pixel) {
            pixel.Green = 0;
        });
    }
}

void DisableBlueChannel(Image& image) {
    for (auto& line : image.Pixels) {
        std::for_each(line.begin(), line.end(), [&](RgbValue& pixel) {
            pixel.Blue = 0;
        });
    }
}

} // namespace transforms
