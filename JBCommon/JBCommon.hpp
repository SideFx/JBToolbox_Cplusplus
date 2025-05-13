//------------------------------------------------------------------------------------------------------
// Commonly used functions, (w) 2025 Jan Buchholz
//------------------------------------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <sstream>

#define BITS(x) sizeof(x) * 8
#define LOQU(x) ((x) & 0x0F)
#define HIQU(x) ((x >> 4) & 0x0F)
const std::vector HEX{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

inline uint32_t rol32(const uint32_t a, const uint8_t n) {
    return (a << n) | (a >> (BITS(a) - n));
}

inline uint32_t ror32(const uint32_t a, const uint8_t n) {
    return (a >> n) | (a << (BITS(a) - n));
}

inline uint64_t ror64(const uint64_t x, const uint8_t n) {
    return (x >> n) | (x << (BITS(x) - n));
}

inline size_t findByte(const uint8_t* array, const int size, const uint8_t byte) {
    for (size_t i = 0; i < size; i++) {
        if (array[i] == byte) {
            return i;
        }
    }
    return -1;
}

inline std::string vectorToHexString(const std::vector<uint8_t> &vec) {
    std::string result;
    for (const auto &byte : vec) {
        result += HEX[HIQU(byte)];
        result += HEX[LOQU(byte)];
    }
    return result;
}

inline std::string stringToHexString(const std::string &str) {
    const std::vector<uint8_t> bytes{str.begin(), str.end()};
    return vectorToHexString(bytes);
}

inline std::string uint32ToHexString(const uint32_t value) {
    std::string result;
    for (int i = 0, j = 24; i < 4; i++, j -= 8) {
        result += HEX[HIQU(value >> j)];
        result += HEX[LOQU(value >> j)];
    }
    return result;
}

inline std::string uint64ToHexString(const uint64_t value) {
    std::string result;
    for (int i = 0, j = 56; i < 8; i++, j -= 8) {
        result += HEX[HIQU(value >> j)];
        result += HEX[LOQU(value >> j)];
    }
    return result;
}

inline int wordsInString(const std::string &payload) {
    int count = 0;
    std::string word;
    std::stringstream strm(payload);
    while(strm >> word) count++;
    return count;
}
