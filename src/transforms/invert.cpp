#include "../images/image.hpp"

namespace transforms {

void Invert(Image& image) {
    image.ForEachPixel([&](RgbValue& r) {
        r.Set(~r.Red, ~r.Green, ~r.Blue);
    });
}

} // namespace transforms
