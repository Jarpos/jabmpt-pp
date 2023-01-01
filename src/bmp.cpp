#include "types.hpp"

#include <fstream>
#include <string>

// See: https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
#pragma pack(1)
struct BitmapFileHeader_t {
    BitmapFileHeader_t() : BitmapFileHeader_t(0) {}
    BitmapFileHeader_t(DWORD size) : Type(0x4D42), Size(size), Reserved1(0), Reserved2(0), OffBits(54) {}
    BitmapFileHeader_t(Image i) :
        BitmapFileHeader_t(i.Width() * i.Height() * sizeof(RgbValue) + i.Height() * i.Padding() + 54) {}

    WORD Type;      // FileType - must be "BM" (or 0x42 0x4D or 19778 or 0x4D42)
    DWORD Size;     // Size, in bytes, of the bitmap file
    WORD Reserved1; // Reserved - must be zero
    WORD Reserved2; // Reserved - must be zero
    DWORD OffBits;  // The offset, in bytes, from the beginning of this to the bitmap bits
};
#pragma pack()

// See: https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader
#pragma pack(1)
struct BitmapInfoHeader_t {
    BitmapInfoHeader_t() : BitmapInfoHeader_t(0, 0) {}
    BitmapInfoHeader_t(Image image) : BitmapInfoHeader_t(image.Width(), image.Height()) {}
    BitmapInfoHeader_t(LONG width, LONG height) :
        Size(40), Width(width), Height(height), Planes(1), BitCount(24), Compression(0), SizeImage(0),
        XPelsPerMeter(0), YPelsPerMeter(0), ClrUsed(0), ClrImportant(0) {}

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
#pragma pack()

Image ReadImageFromBmp(const std::string& path) {
    std::ifstream ifile(path, std::ios::in | std::ios::binary);
    if (!ifile.is_open()) {
        // Handle Error
    }

    // Read File Header & Info Header
    BitmapFileHeader_t fileHeader {};
    BitmapInfoHeader_t infoHeader {};
    ifile.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    ifile.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    // Read Bitmap
    Image image(infoHeader.Width, infoHeader.Height);
    ifile.seekg(fileHeader.OffBits, std::ios::beg);
    for (int i = 0; i < infoHeader.Height; i++) {
        ifile.read(reinterpret_cast<char*>(&(image.Pixels[i][0])), infoHeader.Width * sizeof(RgbValue));
        ifile.seekg(image.Padding(), std::ios::cur);
    }

    return image;
}

void WriteImageToBmp(const std::string& path, const Image& image) {
    std::ofstream ofile(path, std::ios::out | std::ios::binary);
    if (!ofile.is_open()) {
        // Handle Error
    }

    // Write File Header & Info Header
    BitmapFileHeader_t fileHeader(image);
    BitmapInfoHeader_t infoHeader(image);
    ofile.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    ofile.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    // Write Bitmap
    for (int i = 0; i < infoHeader.Height; i++) {
        ofile.write(reinterpret_cast<const char*>(&(image.Pixels[i][0])), image.Width() * sizeof(RgbValue));
        for (int k = 0; k < image.Padding(); k++) {
            ofile.write("\0", sizeof(BYTE));
        }
    }
}
