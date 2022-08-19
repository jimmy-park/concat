#ifndef CONCAT_H_
#define CONCAT_H_

#include <algorithm>
#include <array>
#include <concepts>
#include <string>
#include <string_view>

#include "fixed_string.h"

namespace detail {

struct OversizedString {
    std::array<char, 10'000> data {};
    std::size_t size { 0 };
};

constexpr std::string Concatenate(const auto&... strings)
{
    std::string ret;

    (ret.append(strings), ...);

    return ret;
}

constexpr auto ToOversizedString(const std::string& str)
{
    OversizedString buffer;

    std::copy(std::cbegin(str), std::cend(str), std::begin(buffer.data));
    buffer.size = std::size(str);

    return buffer;
}

consteval auto ShrinkOversizedString(std::invocable auto callable)
{
    constexpr auto buffer = ToOversizedString(callable());
    std::array<char, buffer.size> shrunk;

    std::copy(std::cbegin(buffer.data), std::next(std::cbegin(buffer.data), buffer.size), std::begin(shrunk));

    return shrunk;
}

template <auto Data>
consteval const auto& MakeStatic()
{
    return Data;
}

} // namespace detail

template <FixedString... strings>
consteval std::string_view Concat()
{
    constexpr auto concat = []() { return detail::Concatenate(strings...); };
    constexpr auto& static_data = detail::MakeStatic<detail::ShrinkOversizedString(concat)>();

    return { std::cbegin(static_data), std::cend(static_data) };
}

#endif // CONCAT_H_