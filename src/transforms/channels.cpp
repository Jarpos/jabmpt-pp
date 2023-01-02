#include "../types.hpp"

#include <algorithm>

namespace transforms {

void DisableRedChannel(Image& image) {
    for (int y = 0; y < image.Height(); y++) {
        std::for_each(image.Pixels[y].begin(), image.Pixels[y].end(), [&](RgbValue& r) {
            r.Red = 0;
        });
    }
}

void DisableGreenChannel(Image& image) {
    for (int y = 0; y < image.Height(); y++) {
        std::for_each(image.Pixels[y].begin(), image.Pixels[y].end(), [&](RgbValue& r) {
            r.Green = 0;
        });
    }
}

void DisableBlueChannel(Image& image) {
    for (int y = 0; y < image.Height(); y++) {
        std::for_each(image.Pixels[y].begin(), image.Pixels[y].end(), [&](RgbValue& r) {
            r.Blue = 0;
        });
    }
}

} // namespace transforms
