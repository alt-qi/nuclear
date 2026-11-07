#pragma once

/// &TRD_BEGIN
/// @author OpenAI Codex
/// @brief Объединение сравнений с произвольными положительными модулями.
/// @date 2026-11-07

#include <cassert>
#include <limits>

enum class CrtStatus { ok, inconsistent, overflow };

struct CrtResult {
    CrtStatus status;
    long long residue, modulus;
};

// Объединяет x = a (mod m), x = b (mod n). Модули положительны.
// Поля residue и modulus действительны при status == CrtStatus::ok.
inline CrtResult crt_merge(long long a, long long m, long long b, long long n) {
    assert(m > 0 && n > 0);

    // Евклид с коэффициентом при m для каждого из двух остатков.
    long long g = m, remainder = n;
    __int128 x = 1, remainder_x = 0;
    while (remainder != 0) {
        const long long quotient = g / remainder;
        const long long next_remainder = g % remainder;
        const __int128 next_x = x - quotient * remainder_x;
        g = remainder;
        remainder = next_remainder;
        x = remainder_x;
        remainder_x = next_x;
    }

    const __int128 delta = static_cast<__int128>(b) - a;
    if (delta % g != 0) return {CrtStatus::inconsistent, 0, 0};

    const __int128 reduced_n = n / g;
    const __int128 modulus = m * reduced_n;
    if (modulus > std::numeric_limits<long long>::max()) {
        return {CrtStatus::overflow, 0, 0};
    }

    __int128 t = (delta / g % reduced_n) * x % reduced_n;
    if (t < 0) t += reduced_n;
    __int128 residue = (a + m * t) % modulus;
    if (residue < 0) residue += modulus;
    return {CrtStatus::ok, static_cast<long long>(residue), static_cast<long long>(modulus)};
}
/// &TRD_END
