#pragma once

#include "../types.hpp"

#include <functional>
#include <unordered_map>

namespace transforms {

void Blur(Image& image);
void BlackAndWhite(Image& image);
void FlipX(Image& image);
void FlipY(Image& image);
void DisableRedChannel(Image& image);
void DisableGreenChannel(Image& image);
void DisableBlueChannel(Image& image);

typedef std::function<void(Image&)> transformation_t;

struct Transformation {
    std::function<void(Image&)> Function;
    const char* const HelpDescription;
    const char* const ActionDescription;
};

const std::unordered_map<char, Transformation> Transformations = {
    { 'l', { Blur, "Blurs the image", /*********************************/ "Blured" } },
    { 'w', { BlackAndWhite, "Makes image black and white", /************/ "Made black and white" } },
    { 'x', { FlipX, "Flips the image on the X axis (right to left)", /**/ "Flipped on X-Axis" } },
    { 'y', { FlipY, "Flips the image on the Y axis (upside down)", /****/ "Flipped on Y-Axis" } },

    { 'r', { DisableRedChannel, "Disables the red channel", /***********/ "Disabled Red channel" } },
    { 'g', { DisableGreenChannel, "Disables the Green channel", /*******/ "Disabled Green channel" } },
    { 'b', { DisableBlueChannel, "Disables the Blue channel", /*********/ "Disabled Blue channel" } },
};

} // namespace transforms
