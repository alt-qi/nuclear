#pragma once

/// &TRD_BEGIN
/// @author Не указан в справочнике
/// @brief Расширенный Евклид для знаковых long long.
/// @date 2026-11-07

struct ExtendedGcdResult {
    __int128 g, x, y;
};

// Возвращает g >= 0 и a*x + b*y = g. GCC/Clang с __int128.
inline ExtendedGcdResult extended_gcd(long long a, long long b) {
    if (b == 0) {
        if (a < 0) return {-static_cast<__int128>(a), -1, 0};
        return {a, 1, 0};
    }

    const __int128 wide_a = a;
    const auto [g, x, y] = extended_gcd(b, static_cast<long long>(wide_a % b));
    return {g, y, x - (wide_a / b) * y};
}
/// &TRD_END
