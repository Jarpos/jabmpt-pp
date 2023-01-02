#include "../types.hpp"

#include <numeric>

namespace transforms {

void Blur(Image& image) {
    for (int y = 0; y < image.Height(); y++) {
        for (int x = 0; x < image.Width(); x++) {
            image.At(y, x).SetAll(0);
            std::list<RgbValue> cells = image.GetSurrounding(y, x);

            // TODO: Maybe change this, to account for integer rounding?
            for (const auto& cell : cells) {
                image.At(y, x).Red += cell.Red / cells.size();
                image.At(y, x).Green += cell.Green / cells.size();
                image.At(y, x).Blue += cell.Blue / cells.size();
            }
        }
    }
}

} // namespace transforms
