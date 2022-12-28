#include "../types.hpp"

#include <algorithm>

namespace transforms {

void FlipX(Image& image) {
    for (int y = 0; y < image.Height(); y++) {
        std::reverse(image.Pixels[y].begin(), image.Pixels[y].end());
    }
}

void FlipY(Image& image) {
    std::reverse(image.Pixels.begin(), image.Pixels.end());
}

} // namespace transform
