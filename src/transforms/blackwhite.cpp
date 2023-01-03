#include "../types.hpp"

namespace transforms {

void BlackAndWhite(Image& image) {
    // Yes, I know that actual human color perception is
    // slightly scewed when it comes to Black & White
    // pictures, but I don't care about this atm
    image.ForEachPixel([&](RgbValue& r) {
        r.SetAll(r.Average());
    });
}

} // namespace transforms
