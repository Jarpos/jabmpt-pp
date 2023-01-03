#include "../types.hpp"

namespace transforms {

void BlackAndWhite(Image& image) {
    image.ForEachPixel([&](RgbValue& r) {
        r.SetAll(r.Average());
    });
}

} // namespace transforms
