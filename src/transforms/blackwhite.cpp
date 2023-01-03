#include "../types.hpp"

namespace transforms {

void BlackAndWhite(Image& image) {
    for (auto& line : image.Pixels) {
        for (auto& pixel : line) {
            pixel.SetAll(pixel.Average());
        }
    }
}

} // namespace transforms
