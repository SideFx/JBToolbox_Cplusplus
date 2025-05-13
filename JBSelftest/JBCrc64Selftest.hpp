//------------------------------------------------------------------------------------------------------
// Crc64 ECMA-182 & Crc64 ISO selftest, (w) 2025 Jan Buchholz
//------------------------------------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <iostream>
#include "../JBCrypto/JBCrc64.hpp"
#include "../JBCommon/TextStuff.h"

inline void Crc64EcmaSelftest(const std::string &inp, const uint64_t crc) {
    std::cout << "INPUT text    : " << inp << std::endl;
    std::cout << "Expected Crc64: " << uint64ToHexString(crc) << std::endl;
    const uint64_t res = Crc64Ecma(inp);
    std::cout << "Computed Crc64: " << uint64ToHexString(res) << std::endl;
}

inline void Crc64IsoSelftest(const std::string &inp, const uint64_t crc) {
    std::cout << "INPUT text    : " << inp << std::endl;
    std::cout << "Expected Crc64: " << uint64ToHexString(crc) << std::endl;
    const uint64_t res = Crc64Iso(inp);
    std::cout << "Computed Crc64: " << uint64ToHexString(res) << std::endl;
}

inline void JBCrc64Selftest() {
    std::cout << "\n------------ Crc64 ECMA-182 Selftest ------------" << std::endl;
    Crc64EcmaSelftest(text1, 0x55fbc0cb189f41a9);
    Crc64EcmaSelftest("123456789", 0x995dc9bbdf1939fa);
    Crc64EcmaSelftest(text3, 0x230E6ABE5DA53740);
    std::cout << "\n--------------- Crc64 ISO Selftest --------------" << std::endl;
    Crc64IsoSelftest(text1, 0x25ef5aea3cba058b);
    Crc64IsoSelftest("123456789", 0xb90956c775a41001);
    Crc64IsoSelftest(text3, 0x675BAF1A4B03CCF9);
}
