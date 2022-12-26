#pragma once

#include <cstdint>
#include <vector>

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

// See: https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
#pragma pack(1)
struct BitmapFileHeader_t {
    WORD Type;      // FileType - must be "BM" (or 0x42 0x4D or 19778 or 0x4D42)
    DWORD Size;     // Size, in bytes, of the bitmap file
    WORD Reserved1; // Reserved - must be zero
    WORD Reserved2; // Reserved - must be zero
    DWORD OffBits;  // The offset, in bytes, from the beginning of this to the bitmap bits
};

// See: https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader
#pragma pack(1)
struct BitmapInfoHeader_t {
    DWORD Size;         // Number of bytes required by the structure
    LONG Width;         // Width of the bitmap in pixels
    LONG Height;        // Height of the bitmap in pixel
    WORD Planes;        // Number of planes for the target device - must be one
    WORD BitCount;      // Number of bits per pixel (See above link for more infos)
    DWORD Compression;  // The type of compression (See above link for more infos)
    DWORD SizeImage;    // The size in bytes of the image (zero for uncompressed bmps)
    LONG XPelsPerMeter; // Horizontal resolution in pixels-per-meter
    LONG YPelsPerMeter; // Vertical resolution in pixels-per-meter
    DWORD ClrUsed;      // The number of color indexes in the color table (See above link for more infos)
    DWORD ClrImportant; // The number of color indexes that are required for displaying the bitmap
};

#pragma pack(1)
struct RGBTriple {
    RGBTriple() : RGBTriple(0, 0, 0) {}
    RGBTriple(BYTE red, BYTE green, BYTE blue) : Red(red), Green(green), Blue(blue) {}

    // Members have to be sorted like this, because of Endianess
    BYTE Blue;  // Blue channel
    BYTE Green; // Green channel
    BYTE Red;   // Red channel

    void Set(BYTE red, BYTE green, BYTE blue)
    {
        Red = red;
        Green = green;
        Blue = blue;
    }
};

#pragma pack()

struct Image {
    Image(LONG width, LONG height) :
        Width(width), Height(height), Pixels(height, std::vector<RGBTriple>(width, RGBTriple()))
    {
    }

    LONG Width;
    LONG Height;
    std::vector<std::vector<RGBTriple>> Pixels;

    constexpr BYTE Padding() const
    {
        return 4 - (Width * sizeof(RGBTriple) % 4) % 4;
    }
};
