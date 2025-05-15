//----------------------------------------------------------------------------------------------------------------------
// Adler32 C++ implementation based on Wikipedia's C code
// https://en.wikipedia.org/wiki/Adler-32
// (w) 2025 Jan Buchholz
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <vector>
#include <string>

inline uint32_t Adler32(const std::vector<uint8_t> &payload) {
    uint32_t a = 1;
    uint32_t b = 0;
    for (auto &c: payload) {
        constexpr uint32_t modAdler32 = 65521;
        a += c;
        if (a >= modAdler32) a -= modAdler32;
        b += a;
        if (b >= modAdler32) b -= modAdler32;
    }
    return (b << 16) | a;
}

inline uint32_t Adler32(const std::string &payload) {
    return Adler32(std::vector<uint8_t>(payload.begin(), payload.end()));
}
