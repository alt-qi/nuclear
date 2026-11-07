#pragma once

#include "extended_gcd.hpp"

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

// Нужна заготовка extended_gcd. Объединяет x = a (mod m), x = b (mod n).
// Поля residue и modulus действительны при status == CrtStatus::ok.
inline CrtResult crt_merge(long long a, long long m, long long b, long long n) {
    assert(m > 0 && n > 0);
    const auto bezout = extended_gcd(m, n);
    const __int128 delta = static_cast<__int128>(b) - a;
    if (delta % bezout.g != 0) return {CrtStatus::inconsistent, 0, 0};

    const __int128 reduced_n = n / bezout.g;
    const __int128 modulus = m * reduced_n;
    if (modulus > std::numeric_limits<long long>::max()) {
        return {CrtStatus::overflow, 0, 0};
    }

    __int128 t = (delta / bezout.g % reduced_n) * bezout.x % reduced_n;
    if (t < 0) t += reduced_n;
    __int128 residue = (a + m * t) % modulus;
    if (residue < 0) residue += modulus;
    return {CrtStatus::ok, static_cast<long long>(residue), static_cast<long long>(modulus)};
}
/// &TRD_END
