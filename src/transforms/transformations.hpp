#pragma once

#include "../types.hpp"

#include <functional>
#include <unordered_map>

namespace transforms {

void Blur(Image& image);
void BlackAndWhite(Image& image);
void FlipX(Image& image);
void FlipY(Image& image);

typedef std::function<void(Image&)> transformation_t;

struct Transformation {
    std::function<void(Image&)> Function;
    const char* const HelpDescription;
    const char* const ActionDescription;
};

const std::unordered_map<char, Transformation> Transformations = {
    { 'b', { Blur, "Blurs the image", /****/ "Blured" } },
    { 'w', { BlackAndWhite, "Makes image black and white", /************/ "Made black and white" } },
    { 'x', { FlipX, "Flips the image on the X axis (right to left)", /**/ "Flipped on X-Axis" } },
    { 'y', { FlipY, "Flips the image on the Y axis (upside down)", /****/ "Flipped on Y-Axis" } },
};

} // namespace transform
