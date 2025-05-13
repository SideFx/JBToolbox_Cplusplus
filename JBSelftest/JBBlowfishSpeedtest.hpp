//------------------------------------------------------------------------------------------------------
// Blowfish speed test, (w) 2025 Jan Buchholz
//------------------------------------------------------------------------------------------------------

#pragma once

#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>
#include "../JBCommon/TextStuff.h"
#include "../JBCommon/JBCommon.hpp"
#include "../JBCrypto/JBBlowfish.hpp"

inline void JBBlowfishECBSpeedtest() {
    constexpr int rounds = 1000;
    const std::string key = "Batteries not included";
    const int words = wordsInString(text2);
    std::cout << "\n" << rounds << "x Blowfish ECB encryption/decryption of a plain text containing "
        << words << " words:" << std::endl;
    const std::vector<uint8_t> tx(text2.begin(), text2.end());
    const auto start0 = std::chrono::steady_clock::now();
    BlowfishInitialize(key);
    for (int i = 0; i < rounds; i++) {
        std::vector<uint8_t> tmp0 = BlowfishEncryptECB(tx);
        std::vector<uint8_t> tmp1 = BlowfishDecryptECB(tmp0);
    }
    const auto end0 = std::chrono::steady_clock::now();
    const auto dur0 = std::chrono::duration_cast<std::chrono::microseconds>(end0 - start0);
    std::cout << "Runtime measured: " << dur0.count() << " microseconds" << std::endl;
}

inline void JBBlowfishCBCSpeedtest() {
    constexpr int rounds = 1000;
    const std::string key = "Batteries not included";
    const std::vector<uint8_t> ivec = { 0x01, 0xaa, 0xff, 0x55, 0x23, 0x91, 0x45, 0xee, 0xfe, 0x66 };
    const int words = wordsInString(text2);
    std::cout << "\n" << rounds << "x Blowfish CBC encryption/decryption of a plain text containing "
        << words << " words:" << std::endl;
    const std::vector<uint8_t> tx(text2.begin(), text2.end());
    const auto start0 = std::chrono::steady_clock::now();
    BlowfishInitialize(key);
    for (int i = 0; i < rounds; i++) {
        std::vector<uint8_t> tmp0 = BlowfishEncryptCBC(tx, ivec);
        std::vector<uint8_t> tmp1 = BlowfishDecryptCBC(tmp0, ivec);
    }
    const auto end0 = std::chrono::steady_clock::now();
    const auto dur0 = std::chrono::duration_cast<std::chrono::microseconds>(end0 - start0);
    std::cout << "Runtime measured: " << dur0.count() << " microseconds" << std::endl;
}
