//----------------------------------------------------------------------------------------------------------------------
// (w) 2025 by Jan Buchholz
// Base64 selftest
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include <iostream>

#include "../JBCodec/JBBase64.hpp"
#include "../JBCommon/TextStuff.h"

inline void JBBase64Selftest() {
    const std::vector<uint8_t> tx(text3.begin(), text3.end());
    std::cout << "\n-------------- Base64 Selftest --------------" << std::endl;
    std::cout << "INPUT text  : " << text3 << std::endl;
    const std::string base64enc = Base64Encode(tx);
    std::cout << "Encoded text: " << base64enc << std::endl;
    const std::vector<uint8_t> base64dec = Base64Decode(base64enc);
    std::cout << "Decoded text: " << std::string(base64dec.begin(), base64dec.end()) << std::endl;
}
