//------------------------------------------------------------------------------------------------------
// Ascii85 selftest, (w) 2025 Jan Buchholz
//------------------------------------------------------------------------------------------------------

#pragma once

#include <iostream>
#include "../JBCodec/JBAscii85.hpp"
#include "../JBCommon/TextStuff.h"

inline void JBAscii85Selftest() {
    std::cout << "\n-------------- Ascii85 Selftest --------------" << std::endl;
    std::cout << "INPUT text  : " << text3 << std::endl;
    const std::string enc = Ascii85Encode(text3);
    std::cout << "Encoded text: " << enc << std::endl;;
    const std::string dec = Ascii85Decode(enc);
    std::cout << "Decoded text: " << dec << std::endl;;
}
