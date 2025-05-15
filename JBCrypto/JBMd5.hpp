//----------------------------------------------------------------------------------------------------------------------
// MD5 C++ port based on Wikipedia's pseudo code
// https://en.wikipedia.org/wiki/MD5
// (w) 2025 Jan Buchholz
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include "../JBCommon/JBCommon.hpp"

constexpr uint32_t MD5_DIGEST_SIZE = 16;

inline std::vector<uint8_t> ComputeMd5(const std::vector<uint8_t> &payload) {
    constexpr uint32_t chunk_size = 64;
    constexpr uint64_t bits_size = sizeof(uint64_t);
    std::vector<uint8_t> result(MD5_DIGEST_SIZE);
    uint32_t chunks[16];
    uint32_t rArray[] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
    uint32_t i, g, f;
    const uint64_t l = payload.size();
    uint64_t sd = l / chunk_size + 1;
    if ((l % chunk_size) >= (chunk_size - bits_size)) sd++;
    const uint64_t bits = l << 3;
    auto *mc = new uint8_t[chunk_size * sd];
    memcpy(mc, payload.data(), l);
    mc[l] = 0x80;
    for (i = l + 1; i < sd * chunk_size - bits_size; i++) mc[i] = 0x00;
    mc[i++] = static_cast<uint8_t>(bits);
    mc[i++] = static_cast<uint8_t>(bits >> 8);
    mc[i++] = static_cast<uint8_t>(bits >> 16);
    mc[i++] = static_cast<uint8_t>(bits >> 24);
    mc[i++] = static_cast<uint8_t>(bits >> 32);
    mc[i++] = static_cast<uint8_t>(bits >> 40);
    mc[i++] = static_cast<uint8_t>(bits >> 48);
    mc[i] = static_cast<uint8_t>(bits >> 56);
    uint32_t k = 0;
    uint32_t z = 0;
    for (z = 0; z < sd; z++) {
        constexpr uint32_t md5Rounds = 64;
        uint32_t a = rArray[0];
        uint32_t b = rArray[1];
        uint32_t c = rArray[2];
        uint32_t d = rArray[3];
        for (i = 0; i < 16; i++) {
            chunks[i] = static_cast<uint32_t>(mc[k + 3]) << 24 | static_cast<uint32_t>(mc[k + 2]) << 16 |
                        static_cast<uint32_t>(mc[k + 1]) << 8 | static_cast<uint32_t>(mc[k]);
            k += 4;
        }
        for (i = 0; i < md5Rounds; i++) {
            uint32_t constexpr kArray[] = {
                0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
            };
            int constexpr sArray[] = {
                7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
                4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
            };
            switch (i >> 4) {
                case 0:
                    f = d ^ (b & (c ^ d));
                    g = i % 16;
                    f = f + a + kArray[i] + chunks[g];
                    a = d;
                    d = c;
                    c = b;
                    b = b + rol32(f, sArray[i]);
                    break;
                case 1:
                    f = c ^ (d & (b ^ c));
                    g = (5 * i + 1) % 16;
                    f = f + a + kArray[i] + chunks[g];
                    a = d;
                    d = c;
                    c = b;
                    b = b + rol32(f, sArray[i]);
                    break;
                case 2:
                    f = b ^ c ^ d;
                    g = (3 * i + 5) % 16;
                    f = f + a + kArray[i] + chunks[g];
                    a = d;
                    d = c;
                    c = b;
                    b = b + rol32(f, sArray[i]);
                    break;
                case 3:
                    f = c ^ (b | (~d));
                    g = (7 * i) % 16;
                    f = f + a + kArray[i] + chunks[g];
                    a = d;
                    d = c;
                    c = b;
                    b = b + rol32(f, sArray[i]);
                    break;
                default:
                    break;
            }
        }
        rArray[0] += a;
        rArray[1] += b;
        rArray[2] += c;
        rArray[3] += d;
    }
    delete[] mc;
    for (i = 0, k = 0; i < 4; i++) {
        result[k++] = static_cast<uint8_t>(rArray[i]);
        result[k++] = static_cast<uint8_t>(rArray[i] >> 8);
        result[k++] = static_cast<uint8_t>(rArray[i] >> 16);
        result[k++] = static_cast<uint8_t>(rArray[i] >> 24);
    }
    return result;
}

inline std::vector<uint8_t> ComputeMd5(const std::string &payload) {
    return ComputeMd5(std::vector<uint8_t>(payload.begin(), payload.end()));
}
