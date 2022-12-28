#include "../types.hpp"

namespace transform {

void BlackAndWhite(Image& image) {
    for (int y = 0; y < image.Height(); y++) {
        for (int x = 0; x < image.Width(); x++) {
            image.Get(y, x).SetAll(image.Get(y, x).Average());
        }
    }
}

} // namespace transform
