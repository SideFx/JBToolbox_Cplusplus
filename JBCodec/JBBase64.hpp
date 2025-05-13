//----------------------------------------------------------------------------------------------------------------------
// (w) 2025 by Jan Buchholz
// Base64 C++ implementation based on Wikipedia's web site
// https://en.wikipedia.org/wiki/Base64
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "../JBCommon/JBCommon.hpp"

constexpr uint8_t base64Array[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
constexpr uint8_t padding = '=';

inline std::string Base64Encode(const std::vector<uint8_t> &payload) {
    std::string result;
    uint64_t const l = payload.size();
    int i = 0;
    int j;
    while (i < l) {
        uint32_t buf = 0;
        int k = 0;
        for (j = 0; j < 3; j++) {
            buf <<= 8;
            if (i+j < l) {
                buf |= payload[i + j];
                k++;
            }
        }
        i += 3;
        int n = 3;
        for (j = 0; j <= k; j++) {
            const uint32_t idx = (buf >> (6 * n)) & 0x3f;
            result += static_cast<char>(base64Array[idx]);
            n--;
        }
        for (j = 0; j <= n; j++) result += padding;
    }
    return result;
}

inline std::vector<uint8_t> Base64Decode(const std::string &payload) {
    std::vector<uint8_t> result = {};
    const uint64_t l = payload.size();
    uint64_t i = 0;
    int j;
    uint8_t b;
    while (i < l) {
        uint32_t buf = 0;
        int k = -1;
        for (j = 0; j < 4; j++) {
            if (i+j < l) {
                buf <<= 6;
                b = payload[i+j];
                if (b != padding) {
                    const size_t idx = findByte(base64Array, 64, b);
                    if (idx == -1) {
                        i = l;
                        break;
                    }
                    buf |= idx;
                    k++;
                }
            }
        }
        i += 4;
        int n = 16;
        for (j = 0; j < k; j++) {
            b = buf >> n;
            result.push_back(b);
            n -= 8;
        }
    }
    return result;
}
