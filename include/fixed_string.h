#ifndef FIXED_STRING_H_
#define FIXED_STRING_H_

#include <cstddef>

#include <array>
#include <iostream>
#include <string_view>

template <std::size_t size>
struct FixedString {
    constexpr FixedString(const char* str)
    {
        std::copy(str, str + size + 1, std::begin(data));
    }

    constexpr operator std::string_view() const
    {
        return { std::data(data), size };
    }

    friend std::ostream& operator<<(std::ostream& os, FixedString fstr)
    {
        os << std::string_view { fstr };

        return os;
    }

    std::array<char, size + 1> data {};
};

template <std::size_t size>
FixedString(const char (&)[size]) -> FixedString<size - 1>;

template <FixedString fstr>
consteval auto operator""_fstr()
{
    return fstr;
}

#endif // FIXED_STRING_H_