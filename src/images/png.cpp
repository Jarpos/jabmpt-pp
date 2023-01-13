#include "image.hpp"

#include <cstdint>

// See:
// https://en.wikipedia.org/wiki/Portable_Network_Graphics

// Must be equal to:
// 89        Has the high bit set to detect transmission systems that do not support 8-bit data and to reduce
//           the chance that a text file is mistakenly interpreted as a PNG, or vice versa.
// 50 4E 47  In ASCII, the letters PNG, allowing a person to identify the format easily if it is viewed in a
//           text editor.
// 0D 0A     A DOS-style line ending (CRLF) to detect DOS-Unix line ending conversion of the data.
// 1A        A byte that stops display of the file under DOS when the command type has been used—the
//           end-of-file character.
// 0A        A Unix-style line ending (LF) to detect Unix-DOS line ending conversion.
#pragma pack(1)
struct FileHeader {
    uint8_t TransMissionSystems = 0x89;
    uint8_t MagicNumbers[3] = {
        'P',
        'N',
        'G',
    };
    uint8_t DosLineEnd[2] = {
        '\r',
        '\n',
    };
    uint8_t EndOfFile = 0x1A;
    uint8_t LineFeed = 0x0A;
};
#pragma pack()

namespace chunks
{

#pragma pack(1)
struct ChunkName {
    uint8_t Name[4];
};
#pragma pack()

#pragma pack(1)
struct IHDR {
    uint32_t Width;
    uint32_t Height;
    uint8_t BitDepth;
    uint8_t ColorType;
    uint8_t CompressionMethod;
    uint8_t FilterMethod;
    uint8_t InterlaceMethod;
};
#pragma pack()

#pragma pack(1)
struct PLTE {};
#pragma pack()

#pragma pack(1)
struct IDAT {};
#pragma pack()

#pragma pack(1)
struct IEND {};
#pragma pack()

} // namespace chunks
