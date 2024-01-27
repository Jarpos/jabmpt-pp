#include "../images/image.hpp"

#include <algorithm>
#include <array>

namespace transforms {

RgbValue Convolute(const std::array<uint8_t, 9>& const matrix, const Image& const image, int y, int x);

// See:
// https://cs50.harvard.edu/x/2021/psets/4/filter/more/#edges
// https://en.wikipedia.org/wiki/Sobel_operator
void EdgeDetection(Image& image) {
    Image copy(image);

    std::array<uint8_t, 9> kernelY = {
        -1, +0, +1, //
        -2, +0, +2, //
        -1, +0, +1, //
    };
    std::array<uint8_t, 9> kernelX = {
        -1, -2, -1, //
        +0, +0, +0, //
        +1, +2, +1, //
    };

    std::array<RgbValue, 9> surrounding {};
    for (int y = 0; y < image.Height(); y++) {
        for (int x = 0; x < image.Width(); x++) {
            RgbValue gy = Convolute(kernelY, copy, y, x);
            RgbValue gx = Convolute(kernelX, copy, y, x);

            // TODO: Rework to prevent overflows
            image.At(y, x).Set((gy.Square() + gx.Square()).Sqrt());
        }
    }
}

RgbValue Convolute(const std::array<uint8_t, 9>& const matrix, const Image& const image, int y, int x) {
    RgbValue outpixel(0, 0, 0);

    int i = 0;
    for (int yc = -1; yc < 2; yc++) {
        for (int xc = -1; xc < 2; xc++, i++) {
            if (y + yc >= 0 && y + yc < image.Height()) {
                if (x + xc >= 0 && x + xc < image.Width()) {
                    // TODO: maybe add += operator overload
                    outpixel = outpixel + image.At(y + yc, x + xc) * matrix[i];
                }
            }
        }
    }

    return outpixel;
}

} // namespace transforms
