#pragma once

#include "../types.hpp"

#include <functional>
#include <unordered_map>

namespace transforms {

void BlackAndWhite(Image& image);
void FlipX(Image& image);
void FlipY(Image& image);

typedef std::function<void(Image&)> transformation_t;

struct Transformation {
    std::function<void(Image&)> Function;
    const char* const Description;
};

const std::unordered_map<char, Transformation> Transformations = {
    { 'w', { BlackAndWhite, "Makes image black and white" } },
    { 'x', { FlipX, "Flips the image on the X axis (right to left)" } },
    { 'y', { FlipY, "Flips the image on the Y axis (upside down)" } },
};

} // namespace transform
