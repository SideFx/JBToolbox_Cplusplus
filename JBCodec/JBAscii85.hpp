//---------------------------------------------------------------------------------
// Ascii85 encoder/decoder (w) 2025 Jan Buchholz
//---------------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <vector>
#include <string>

constexpr uint8_t cZero = 'z';
constexpr uint8_t cBase = 33;

inline std::vector<uint8_t> Ascii85Encode(const std::vector<uint8_t> &payload) {
	std::vector<uint8_t> result = {};
	uint32_t number = 0;
	uint64_t i = 0;
	int j;
	int pad = 0;
	uint8_t enc[5] = {};
	const uint64_t l = payload.size();
	uint8_t c;
	while (i < l) {
		for (j = 0; j < 4; j++) {
			if (i < l) c = payload[i++]; else {
				c = 0x00;
				pad++;
			}
			(number <<= 8) |= c;
		}
		if (number > 0) {
			enc[4] = (number % 85) + cBase;
			number /= 85;
			enc[3] = (number % 85) + cBase;
			number /= 85;
			enc[2] = (number % 85) + cBase;
			number /= 85;
			enc[1] = (number % 85) + cBase;
			number /= 85;
			enc[0] = (number % 85) + cBase;
			for (j = 0; j < (4 - pad) + 1; j++) result.push_back(enc[j]);
		}
		else result.push_back(cZero);
	}
	return result;
}

inline std::vector<uint8_t> Ascii85Decode(const std::vector<uint8_t> &payload) {
	std::vector<uint8_t> result = {};
	uint32_t number = 0;
	uint64_t i = 0;
	int j;
	const uint64_t l = payload.size();
	while (i < l) {
		if (payload[i] == cZero) {
			for (j = 0; j < 4; j++) result.push_back(0x00);
			i++;
		}
		else {
			number = 0;
			int cnt = 0;
			for (j = 0; j < 5; j++) {
				if (i < l) {
					if (payload[i] < 33 || payload[i] > 117) break;
					number = number * 85 + (payload[i] - cBase);
					i++;
					cnt++;
				}
				else number = number * 85 + 84;
			}
			if (cnt >= 2) result.push_back(number >> 24);
			if (cnt >= 3) result.push_back(number >> 16);
			if (cnt >= 4)result.push_back(number >> 8);
			if (cnt == 5) result.push_back(number);
		}
	}
	return result;
}

inline std::string Ascii85Encode(const std::string &payload) {
	std::vector<uint8_t> enc = Ascii85Encode(std::vector<uint8_t>(payload.begin(), payload.end()));
	return {enc.begin(), enc.end()};
}

inline std::string Ascii85Decode(const std::string &payload) {
	std::vector<uint8_t> dec = Ascii85Decode(std::vector<uint8_t>(payload.begin(), payload.end()));
	return {dec.begin(), dec.end()};
}
