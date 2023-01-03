#include "../types.hpp"

#include <algorithm>

namespace transforms {

void FlipX(Image& image) {
    for (auto& line : image.Pixels) {
        std::reverse(line.begin(), line.end());
    }
}

void FlipY(Image& image) {
    std::reverse(image.Pixels.begin(), image.Pixels.end());
}

} // namespace transforms
