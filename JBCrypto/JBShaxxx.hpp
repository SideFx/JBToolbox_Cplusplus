//------------------------------------------------------------------------------------------------
// Sha256/Sha512 C++ implementation based on Wikipedia's pseudo code
// https://en.wikipedia.org/wiki/SHA-2
// (w) 2025 Jan Buchholz
//------------------------------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include "../JBCommon/JBCommon.hpp"

constexpr uint64_t SHA512_DIGEST_SIZE = 64;
constexpr uint64_t SHA256_DIGEST_SIZE = 32;

inline std::vector<uint8_t> ComputeSha512(std::vector<uint8_t> payload) {
    constexpr uint64_t chunk_size = 128;
    constexpr uint64_t bits_size = sizeof(uint64_t) + sizeof(uint64_t);
    constexpr uint64_t rounds = 80;
    uint64_t h[] = {
        0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
        0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
    };
    std::vector<uint8_t> result(SHA512_DIGEST_SIZE);
    uint64_t const l = payload.size();
    uint64_t ha, hb, hc, hd, he, hf, hg, hh, t0, t1, bitsl, bitsh, sc, sm;
    uint64_t i, j, n, z;
    uint64_t D[rounds] = {};
    uint64_t sd = l / chunk_size + 1;
    if ((l % chunk_size) >= (chunk_size - bits_size)) sd++;
    bitsl = l << 3;
    bitsh = l >> 61;
    auto *mc = new uint8_t[chunk_size * sd];
    memcpy(mc, payload.data(), l);
    mc[l] = 0x80;
    for (i = l + 1; i < sd * chunk_size - bits_size; i++) mc[i] = 0x00;
    mc[i++] = static_cast<uint8_t>(bitsh >> 56);
    mc[i++] = static_cast<uint8_t>(bitsh >> 48);
    mc[i++] = static_cast<uint8_t>(bitsh >> 40);
    mc[i++] = static_cast<uint8_t>(bitsh >> 32);
    mc[i++] = static_cast<uint8_t>(bitsh >> 24);
    mc[i++] = static_cast<uint8_t>(bitsh >> 16);
    mc[i++] = static_cast<uint8_t>(bitsh >> 8);
    mc[i++] = static_cast<uint8_t>(bitsh);
    mc[i++] = static_cast<uint8_t>(bitsl >> 56);
    mc[i++] = static_cast<uint8_t>(bitsl >> 48);
    mc[i++] = static_cast<uint8_t>(bitsl >> 40);
    mc[i++] = static_cast<uint8_t>(bitsl >> 32);
    mc[i++] = static_cast<uint8_t>(bitsl >> 24);
    mc[i++] = static_cast<uint8_t>(bitsl >> 16);
    mc[i++] = static_cast<uint8_t>(bitsl >> 8);
    mc[i] = static_cast<uint8_t>(bitsl);
    z = 0;
    for (n = 0; n < sd; n++) {
        ha = h[0];
        hb = h[1];
        hc = h[2];
        hd = h[3];
        he = h[4];
        hf = h[5];
        hg = h[6];
        hh = h[7];
        for (i = 0; i < 16; i++) {
            D[i] = (static_cast<uint64_t>(mc[z]) << 56) | (static_cast<uint64_t>(mc[z + 1]) << 48) |
                   (static_cast<uint64_t>(mc[z + 2]) << 40) | (static_cast<uint64_t>(mc[z + 3]) << 32) |
                   (static_cast<uint64_t>(mc[z + 4]) << 24) | (static_cast<uint64_t>(mc[z + 5]) << 16) |
                   (static_cast<uint64_t>(mc[z + 6]) << 8) | static_cast<uint64_t>(mc[z + 7]);
            z += 8;
        }
        for (i = 16; i < rounds; i++) {
            bitsl = ror64(D[i - 15], 1) ^ ror64(D[i - 15], 8) ^ (D[i - 15] >> 7);
            bitsh = ror64(D[i - 2], 19) ^ ror64(D[i - 2], 61) ^ (D[i - 2] >> 6);
            D[i] = D[i - 16] + bitsl + D[i - 7] + bitsh;
        }
        for (i = 0; i < rounds; i++) {
            constexpr uint64_t kArray512[] = {
                0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
                0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
                0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
                0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
                0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
                0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
                0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
                0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
                0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
                0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
                0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
                0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
                0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
                0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
                0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
                0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
                0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
                0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
                0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
                0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
            };
            bitsh = ror64(he, 14) ^ ror64(he, 18) ^ ror64(he, 41);
            sc = (he & hf) ^ ((~he) & hg);
            t0 = hh + bitsh + sc + kArray512[i] + D[i];
            bitsl = ror64(ha, 28) ^ ror64(ha, 34) ^ ror64(ha, 39);
            sm = (ha & hb) ^ (ha & hc) ^ (hb & hc);
            t1 = bitsl + sm;
            hh = hg;
            hg = hf;
            hf = he;
            he = hd + t0;
            hd = hc;
            hc = hb;
            hb = ha;
            ha = t0 + t1;
        }
        h[0] += ha;
        h[1] += hb;
        h[2] += hc;
        h[3] += hd;
        h[4] += he;
        h[5] += hf;
        h[6] += hg;
        h[7] += hh;
    }
    delete[] mc;
    i = 0;
    for (j = 0; j < std::size(h); j++) {
        result[i++] = static_cast<uint8_t>(h[j] >> 56);
        result[i++] = static_cast<uint8_t>(h[j] >> 48);
        result[i++] = static_cast<uint8_t>(h[j] >> 40);
        result[i++] = static_cast<uint8_t>(h[j] >> 32);
        result[i++] = static_cast<uint8_t>(h[j] >> 24);
        result[i++] = static_cast<uint8_t>(h[j] >> 16);
        result[i++] = static_cast<uint8_t>(h[j] >> 8);
        result[i++] = static_cast<uint8_t>(h[j]);
    }
    return result;
}

inline std::vector<uint8_t> ComputeSha512(std::string payload) {
    return ComputeSha512(std::vector<uint8_t>(payload.begin(), payload.end()));
}

inline std::vector<uint8_t> ComputeSha256(const std::vector<uint8_t> &payload) {
    constexpr uint64_t chunk_size = 64;
    constexpr uint64_t bits_size = sizeof(uint64_t);
    constexpr uint64_t rounds = 64;
    uint32_t h[] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    std::vector<uint8_t> result(SHA256_DIGEST_SIZE);
    uint64_t i, j;
    const uint64_t l = payload.size();
    uint64_t sd = l / chunk_size + 1;
    if ((l % chunk_size) >= (chunk_size - bits_size)) sd++;
    const uint64_t bits = l << 3;
    uint32_t D[rounds] = {};
    auto *mc = new uint8_t[chunk_size * sd];
    memcpy(mc, payload.data(), l);
    mc[l] = 0x80;
    for (i = l + 1; i < sd * chunk_size - bits_size; i++) mc[i] = 0x00;
    mc[i++] = static_cast<uint8_t>(bits >> 56);
    mc[i++] = static_cast<uint8_t>(bits >> 48);
    mc[i++] = static_cast<uint8_t>(bits >> 40);
    mc[i++] = static_cast<uint8_t>(bits >> 32);
    mc[i++] = static_cast<uint8_t>(bits >> 24);
    mc[i++] = static_cast<uint8_t>(bits >> 16);
    mc[i++] = static_cast<uint8_t>(bits >> 8);
    mc[i] = static_cast<uint8_t>(bits);
    uint64_t z = 0;
    for (uint64_t n = 0; n < sd; n++) {
        uint32_t ha = h[0];
        uint32_t hb = h[1];
        uint32_t hc = h[2];
        uint32_t hd = h[3];
        uint32_t he = h[4];
        uint32_t hf = h[5];
        uint32_t hg = h[6];
        uint32_t hh = h[7];
        for (j = 0; j < 16; j++) {
            D[j] = (mc[z] << 24) | (mc[z + 1] << 16) | (mc[z + 2] << 8) | mc[z + 3];
            z += 4;
        }
        for (j = 16; j < rounds; j++) {
            D[j] = D[j - 16] + (ror32(D[j - 15], 7) ^ ror32(D[j - 15], 18) ^ (D[j - 15] >> 3)) +
                   D[j - 7] + (ror32(D[j - 2], 17) ^ ror32(D[j - 2], 19) ^ (D[j - 2] >> 10));
        }
        for (j = 0; j < rounds; j++) {
            constexpr uint32_t kArray256[] = {
                0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
            };
            const uint32_t t0 = hh + kArray256[j] + D[j] + ((he & hf) ^ ((~he) & hg)) +
                                (ror32(he, 6) ^ ror32(he, 11) ^ ror32(he, 25));
            const uint32_t t1 = (ror32(ha, 2) ^ ror32(ha, 13) ^ ror32(ha, 22)) +
                                ((ha & hb) ^ (ha & hc) ^ (hb & hc));
            hh = hg;
            hg = hf;
            hf = he;
            he = hd + t0;
            hd = hc;
            hc = hb;
            hb = ha;
            ha = t0 + t1;
        }
        h[0] += ha;
        h[1] += hb;
        h[2] += hc;
        h[3] += hd;
        h[4] += he;
        h[5] += hf;
        h[6] += hg;
        h[7] += hh;
    }
    delete[] mc;
    i = 0;
    for (j = 0; j < std::size(h); j++) {
        result[i++] = static_cast<uint8_t>(h[j] >> 24);
        result[i++] = static_cast<uint8_t>(h[j] >> 16);
        result[i++] = static_cast<uint8_t>(h[j] >> 8);
        result[i++] = static_cast<uint8_t>(h[j]);
    }
    return result;
}

inline std::vector<uint8_t> ComputeSha256(std::string payload) {
    return ComputeSha256(std::vector<uint8_t>(payload.begin(), payload.end()));
}
