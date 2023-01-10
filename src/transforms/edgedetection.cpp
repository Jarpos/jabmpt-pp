#include "../images/image.hpp"

#include <algorithm>
#include <array>

namespace transforms {

// See:
// https://cs50.harvard.edu/x/2021/psets/4/filter/more/#edges
// https://en.wikipedia.org/wiki/Sobel_operator
void EdgeDetection(Image& image) {
    Image copy(image);

    std::array<short, 9> kernelY = {
        -1, +0, +1, //
        -2, +0, +2, //
        -1, +0, +1, //
    };
    std::array<short, 9> kernelY = {
        -1, -2, -1, //
        +0, +0, +0, //
        +1, +2, +1, //
    };

    std::array<RgbValue, 9> surrounding {};
    for (int y = 0; y < image.Height(); y++) {
        for (int x = 0; x < image.Width(); x++) {
        }
    }
}

} // namespace transforms
