#include "../types.hpp"

#include <cmath>
#include <numeric>

namespace transforms {

void Blur(Image& image) {
    Image copy(image);

    std::array<RgbValue, 9> surrounding {};
    for (int y = 0; y < image.Height(); y++) {
        for (int x = 0; x < image.Width(); x++) {
            double r(0), g(0), b(0);
            int count = copy.GetSurroundingQuick(y, x, surrounding);
            for (int i = 0; i < count; i++) {
                r += (double)surrounding[i].Red / count;
                g += (double)surrounding[i].Green / count;
                b += (double)surrounding[i].Blue / count;
            }
            image.At(y, x).Set(std::round(r), std::round(g), std::round(b));
        }
    }
}

} // namespace transforms
