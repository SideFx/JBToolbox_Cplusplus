//----------------------------------------------------------------------------------------------------------------------
// CRC64 (reversed ECMA-182 & reversed ISO) C++ implementation based on Wikipedia's web site
// (w) 2025 by Jan Buchholz
// https://en.wikipedia.org/wiki/Cyclic_redundancy_check
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <string>
#include <vector>

constexpr uint64_t ecmaPoly = 0xc96c5795d7870f42;
constexpr uint64_t isoPoly = 0xd800000000000000;

inline std::vector<uint64_t> crc64Ecma{};
inline std::vector<uint64_t> crc64Iso{};

inline std::vector<uint64_t> makeTable(const uint64_t poly) {
    std::vector<uint64_t> table{};
    for (int i = 0; i < 256; i++) {
        auto r = static_cast<uint64_t>(i);
        for (int j = 0; j < 8; j++) {
            if ((r&1) == 1) r = (r >> 1) ^ poly; else r >>= 1;
        }
        table.push_back(r);
    }
    return table;
}

inline uint64_t Crc64Ecma(const std::vector<uint8_t>& payload) {
    uint64_t result = UINT64_MAX;
    if (crc64Ecma.empty()) crc64Ecma = makeTable(ecmaPoly);
    for (const auto &c : payload) {
        result = (result >> 8) ^ crc64Ecma[static_cast<uint8_t>(result ^ c)];
    }
    return ~result;
}

inline uint64_t Crc64Ecma(const std::string& payload) {
    return Crc64Ecma(std::vector<uint8_t>(payload.begin(), payload.end()));
}

inline uint64_t Crc64Iso(const std::vector<uint8_t>& payload) {
    uint64_t result = UINT64_MAX;
    if (crc64Iso.empty()) crc64Iso = makeTable(isoPoly);
    for (const auto &c : payload) {
        result = (result >> 8) ^ crc64Iso[static_cast<uint8_t>(result ^ c)];
    }
    return ~result;
}

inline uint64_t Crc64Iso(const std::string& payload) {
    return Crc64Iso(std::vector<uint8_t>(payload.begin(), payload.end()));
}



