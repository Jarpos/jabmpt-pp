#include "../types.hpp"

namespace transforms {

void BlackAndWhite(Image& image) {
    for (int y = 0; y < image.Height(); y++) {
        for (int x = 0; x < image.Width(); x++) {
            image.At(y, x).SetAll(image.At(y, x).Average());
        }
    }
}

} // namespace transform
