#include "../types.hpp"

#include <cmath>
#include <numeric>

namespace transforms {

void Blur(Image& image) {
    Image copy(image);

    for (int y = 0; y < image.Height(); y++) {
        for (int x = 0; x < image.Width(); x++) {
            double r(0), g(0), b(0);
            const auto& cells = copy.GetSurrounding(y, x);
            for (const auto& cell : cells) {
                r += (double)cell.Red / cells.size();
                g += (double)cell.Green / cells.size();
                b += (double)cell.Blue / cells.size();
            }
            image.At(y, x).Set(std::round(r), std::round(g), std::round(b));
        }
    }
}

} // namespace transforms
