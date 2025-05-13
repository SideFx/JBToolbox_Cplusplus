cmake_minimum_required(VERSION 3.31)
project(JBToolbox)

set(CMAKE_CXX_STANDARD 20)

add_executable(JBToolbox main.cpp
        JBCommon/TextStuff.h
        JBCrypto/JBTwofish.hpp
        JBSelftest/JBTwofishSelftest.hpp
        JBCrypto/JBBlowfish.hpp
        JBSelftest/JBBlowfishSelftest.hpp
        JBCommon/JBCommon.hpp
        JBCrypto/JBShaxxx.hpp
        JBSelftest/JBShaSelftest.hpp
        JBCodec/JBAscii85.hpp
        JBSelftest/JBAscii85Selftest.hpp
        JBCrypto/JBAdler32.hpp
        JBSelftest/JBAdler32Selftest.hpp
        JBCrypto/JBMd5.hpp
        JBSelftest/JBMd5Selftest.hpp
        JBCodec/JBBase64.hpp
        JBSelftest/JBBase64Selftest.hpp
        JBCrypto/JBCrc64.hpp
        JBSelftest/JBCrc64Selftest.hpp
        JBSelftest/JBBlowfishSpeedtest.hpp
)
