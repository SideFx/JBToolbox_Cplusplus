//------------------------------------------------------------------------------------------------------
// Adler32 selftest, (w) 2025 Jan Buchholz
//------------------------------------------------------------------------------------------------------

#pragma once

#include "../JBCrypto/JBAdler32.hpp"
#include "../JBCommon/TextStuff.h"
#include "../JBCommon/JBCommon.hpp"

inline void Adler32Selftest(const std::string &inp, const uint32_t adler) {
    std::cout << "INPUT hex       : " << stringToHexString(inp) << std::endl;
    std::cout << "Expected Adler32: " << uint32ToHexString(adler) << std::endl;
    const uint32_t res = Adler32(inp);
    std::cout << "Computed Adler32: " << uint32ToHexString(res) << std::endl;
}

inline void JBAdler32Selftest() {
    std::cout << "\n-------------- Adler32 Selftest --------------" << std::endl;
    Adler32Selftest(std::string{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}, 0x005c001d);
    Adler32Selftest(std::string{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f}, 0x02b80079);
    Adler32Selftest(std::string{0x41, 0x41, 0x41, 0x41}, 0x028e0105);
    Adler32Selftest(std::string{0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42}, 0x09500211);
    Adler32Selftest(std::string{0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43}, 0x23a80431);
    Adler32Selftest("Hello", 0x058c01f5);
    Adler32Selftest("Neon", 0x03b70191);
    Adler32Selftest(text1, 0x88c0622d);
}

