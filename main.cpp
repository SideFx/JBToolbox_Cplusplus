//------------------------------------------------------------------------------------------------------
// JBToolbox C++ edition, (w) 2025 Jan Buchholz
//------------------------------------------------------------------------------------------------------

#include "JBSelftest/JBBlowfishSelftest.hpp"
#include "JBSelftest/JBShaSelftest.hpp"
#include "JBSelftest/JBTwofishSelftest.hpp"
#include "JBSelftest/JBAscii85Selftest.hpp"
#include "JBSelftest/JBAdler32Selftest.hpp"
#include "JBSelftest/JBBase64Selftest.hpp"
#include "JBSelftest/JBBlowfishSpeedtest.hpp"
#include "JBSelftest/JBTwofishSpeedtest.hpp"
#include "JBSelftest/JBCrc64Selftest.hpp"
#include "JBSelftest/JBMd5Selftest.hpp"

int main() {
    std::string key;
    std::cout << "\n-------------------------\nJB Toolbox Demo:\n-------------------------" << std::endl;
    std::cout << "(a) Adler32 selftest" << std::endl;
    std::cout << "(b) Crc64 selftest" << std::endl;
    std::cout << "(c) Md5 selftest" << std::endl;
    std::cout << "(d) Sha256 selftest" << std::endl;
    std::cout << "(e) Sha512 selftest" << std::endl;
    std::cout << "(f) Ascii85 selftest" << std::endl;
    std::cout << "(g) Base64 selftest" << std::endl;
    std::cout << "(h) Blowfish selftest" << std::endl;
    std::cout << "(i) Twofish selftest" << std::endl;
    std::cout << "(k) Blowfish ECB speed test" << std::endl;
    std::cout << "(l) Blowfish CBC speed test" << std::endl;
    std::cout << "(m) Twofish ECB speed test" << std::endl;
    std::cout << "(n) Twofish CBC speed test" << std::endl;
    std::cout << "(x) Exit" << std::endl;
    while (key !=  "x") {
        std::cout << "\nPlease enter an option: ";
        getline(std::cin, key);
        std::system("cls");
        if (key == "a") JBAdler32Selftest();
        else if (key == "b") JBCrc64Selftest();
        else if (key == "c") JBMd5Selftest();
        else if (key == "d") JBSha256SelfTest();
        else if (key == "e") JBSha512SelfTest();
        else if (key == "f") JBAscii85Selftest();
        else if (key == "g") JBBase64Selftest();
        else if (key == "h") JBBlowfishSelftest();
        else if (key == "i") JBTwofishSelftest();
        else if (key == "k") JBBlowfishECBSpeedtest();
        else if (key == "l") JBBlowfishCBCSpeedtest();
        else if (key == "m") JBTwofishECBSpeedtest();
        else if (key == "n") JBTwofishCBCSpeedtest();
        else if (key == "x") std::cout << "Bye." << std::endl;
        else std::cout << "Invalid input (press 'x' to exit)" << std::endl;
    }
    return 0;
}
