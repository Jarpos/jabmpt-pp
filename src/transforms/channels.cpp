#include "../types.hpp"

#include <algorithm>

namespace transforms {

void DisableRedChannel(Image& image) {
    image.ForEachPixel([&](RgbValue& r) {
        r.Red = 0;
    });
}

void DisableGreenChannel(Image& image) {
    image.ForEachPixel([&](RgbValue& r) {
        r.Green = 0;
    });
}

void DisableBlueChannel(Image& image) {
    image.ForEachPixel([&](RgbValue& r) {
        r.Blue = 0;
    });
}

} // namespace transforms
