//------------------------------------------------------------------------------------------------------
// Twofish selftest, (w) 2025 Jan Buchholz
//------------------------------------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <chrono>
#include "../JBCrypto/JBTwofish.hpp"
#include "../JBCommon/TextStuff.h"

inline bool TwofishSelfTest() {
    uint8_t const ct49[] = {
        0x37, 0xfe, 0x26, 0xff, 0x1c, 0xf6, 0x61, 0x75,
        0xf5, 0xdd, 0xf4, 0xc3, 0x3b, 0x97, 0xa2, 0x05
    };
    constexpr int rounds = 49;
    std::vector<uint8_t> key(TWOFISH_KEY_SIZE, 0x00);
    std::vector<uint8_t> pt(TWOFISH_BLOCK_SIZE, 0x00);
    std::vector<uint8_t> ptx(TWOFISH_BLOCK_SIZE, 0x00);
    std::vector<uint8_t> ct(TWOFISH_BLOCK_SIZE, 0x00);
    int j;
    for (int i = 1; i <= rounds; i++) {
        TwofishInitialize(key);
        ptx = pt;
        TwofishEncryptBase(pt);
        ct = pt;
        TwofishDecryptBase(pt);
        for (j = 0; j < TWOFISH_BLOCK_SIZE; j++) if (pt.at(j) != ptx.at(j)) return false;
        for (j = 16; j < TWOFISH_KEY_SIZE; j++) key[j] = key[j - 16];
        for (j = 0; j < TWOFISH_BLOCK_SIZE; j++) key[j] = ptx.at(j);
        pt = ct;
    }
    for (j = 0; j < TWOFISH_BLOCK_SIZE; j++) if (ct.at(j) != ct49[j]) return false;
    return true;
}

inline void JBTwofishSelftest() {
    const std::string res = (TwofishSelfTest() ? "PASSED" : "FAILED");
    const std::string key = "Batteries not included";
    const std::vector<uint8_t> ivec = { 0x01, 0xaa, 0xff, 0x55, 0x23, 0x91, 0x45, 0xee, 0xaa, 0x01, 0xc4};
    std::cout << "\n---------------- Twofish Selftest ----------------" << std::endl;
    std::cout << "... using 49 rounds test function: " << res << std::endl;
    std::cout << "\n---------------- Twofish ECB Test ----------------" << std::endl;
    const std::vector<uint8_t> plain(text1.begin(), text1.end());
    TwofishInitialize(key);
    std::cout << "Encryption key: " << key << std::endl;
    std::cout << "Plain text    : " << text1 << std::endl;
    std::vector<uint8_t> enc = TwofishEncryptECB(plain);
    std::cout << "Encrypted text: " << vectorToHexString(enc) << std::endl;
    std::vector<uint8_t> dec = TwofishDecryptECB(enc);
    std::cout << "Decrypted text: " << std::string(dec.begin(), dec.end()) << std::endl;
    std::cout << "\n---------------- Twofish CBC Test ----------------" << std::endl;
    std::cout << "Encryption key  : " << key << std::endl;
    std::cout << "Init. CBC vector: " << vectorToHexString(ivec) << std::endl;
    std::cout << "Plain text      : " << text1 << std::endl;
    enc = TwofishEncryptCBC(plain, ivec);
    std::cout << "Encrypted text  : " << vectorToHexString(enc) << std::endl;
    dec = TwofishDecryptCBC(enc, ivec);
    std::cout << "Decrypted text  : " << std::string(dec.begin(), dec.end()) << std::endl;

    /*
    std::cout << "\n1.000x Twofish CBC encryption/decryption of a ≈10.000 words long text:";
    std::vector<uint8_t> longtext(text2.begin(), text2.end());
    auto start0 = std::chrono::steady_clock::now();
    TwofishInitialize("Batteries not included");
    for (int i = 0; i < 1000; i++) {
        std::vector<uint8_t> r = TwofishEncryptCBC(longtext, iv);
        std::vector<uint8_t> tmp1 = TwofishDecryptCBC(r, iv);
    }
    auto end0 = std::chrono::steady_clock::now();
    auto dur0 = std::chrono::duration_cast<std::chrono::microseconds>(end0 - start0);
    std::cout << "\nRuntime of 1.000x Twofish CBC: " << dur0.count() << " microseconds\n";
    */
}

