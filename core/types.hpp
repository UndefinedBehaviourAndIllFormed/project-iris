//Copyright 2022 Project Aura, All Rights Reserved
#pragma once
#include <atomic>
#include <core/enumeration.hpp>
#define alpha '_': case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z': case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z'
#define numeric '0':  case '1':  case '2':  case '3':  case '4':  case '5':  case '6':  case '7':  case '8':  case '9'
#define alphanumeric alpha: case numeric

namespace aena
{
    /** atomic enumeration 't' */
    template<enumeration t> using aenum = std::atomic<t>;

    /** atomic 1-byte boolean type */
    using abool = std::atomic<bool>;

    /** atomic 1-byte ASCII character type */
    using aascii = std::atomic<char>;

    /** atomic 1-byte UTF-8 character type */
    using autf8 = std::atomic<char8_t>;

    /** atomic 2-bytes UTF-16 character type */
    using autf16 = std::atomic<char16_t>;

    /** atomic 4-bytes UTF-32 character type */
    using autf32 = std::atomic<char32_t>;

    /** atomic 1-byte unsigned integer type */
    using au8 = std::atomic<std::uint8_t>;

    /** atomic 1-byte signed integer type */
    using as8 = std::atomic<std::int8_t>;

    /** atomic 2-bytes unsigned integer type */
    using au16 = std::atomic<std::uint16_t>;

    /** atomic 2-bytes signed integer type */
    using as16 = std::atomic<std::int16_t>;

    /** atomic 4-bytes unsigned integer type */
    using au32 = std::atomic<std::uint32_t>;

    /** atomic 4-bytes signed integer type */
    using as32 = std::atomic<std::int32_t>;

    /** atomic 4-bytes scalar single-precision floating-point type */
    using af32 = std::atomic<float>;

    /** atomic 8-bytes unsigned integer type */
    using au64 = std::atomic<std::uint64_t>;

    /** atomic 8-bytes signed integer type */
    using as64 = std::atomic<std::int64_t>;

    /** atomic 8-bytes scalar double-precision floating-point type */
    using af64 = std::atomic<double>;

    /** 1-byte ASCII character type */
    using ascii = char;

    /** 1-byte UTF-8 character type */
    using utf8 = char8_t;

    /** 2-bytes UTF-16 character type */
    using utf16 = char16_t;

    /** 4-bytes UTF-32 character type */
    using utf32 = char32_t;

    /** 1-byte unsigned interger type */
    using u8 = std::uint8_t;

    /** 1-byte signed integer type */
    using s8 = std::int8_t;

    /** 2-bytes unsigned integer type */
    using u16 = std::uint16_t;

    /** 2-bytes signed integer type */
    using s16 = std::int16_t;

    /** 4-bytes unsigned integer type */
    using u32 = std::uint32_t;

    /** 4-bytes signed integer type */
    using s32 = std::int32_t;

    /** 4-bytes scalar single-precision floating-point type */
    using f32 = float;

    /** 8-bytes unsigned integer type */
    using u64 = std::uint64_t;

    /** 8-bytes signed integer type */
    using s64 = std::int64_t;

    /** 8-bytes scalar double-precision floating-point type */
    using f64 = double;
}