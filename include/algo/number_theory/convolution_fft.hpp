#pragma once

#include <cmath>
#include <complex>
#include <cstddef>
#include <numbers>
#include <stdexcept>
#include <utility>
#include <vector>

/// &TRD_BEGIN
/// @author igor
/// @brief Свёртка целых чисел через комплексную FFT с округлением.
namespace fft_detail {
using Complex = std::complex<long double>;

inline void transform(std::vector<Complex>& a,
                      const std::vector<Complex>& roots, bool inverse) {
    const int n = static_cast<int>(a.size());
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n / 2;
        while (j & bit) {
            j ^= bit;
            bit /= 2;
        }
        j ^= bit;
        if (i < j) std::swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len *= 2) {
        const int half = len / 2;
        const int step = n / len;
        for (int start = 0; start < n; start += len) {
            for (int j = 0; j < half; ++j) {
                const Complex root = roots[j * step];
                const Complex u = a[start + j];
                const Complex v = a[start + j + half] * (inverse ? std::conj(root) : root);
                a[start + j] = u + v;
                a[start + j + half] = u - v;
            }
        }
    }
    if (inverse) {
        for (auto& x : a) x /= n;
    }
}
}  // namespace fft_detail

// c[k] = sum a[i]*b[j] по i+j=k. Сложность O(N log N), память O(N).
// N <= 2^20, произведение евклидовых норм a и b <= 10^12.
inline std::vector<long long> convolution_fft(const std::vector<long long>& a,
                                              const std::vector<long long>& b) {
    if (a.empty() || b.empty()) return {};
    constexpr std::size_t max_length = 1 << 20;
    if (a.size() > max_length || b.size() > max_length ||
        a.size() + b.size() - 1 > max_length) {
        throw std::length_error("convolution_fft: length exceeds 2^20");
    }
    const auto squared_norm = [](const std::vector<long long>& values) {
        long double sum = 0;
        for (long double x : values) sum += x * x;
        return sum;
    };
    if (squared_norm(a) * squared_norm(b) > 1e24L) {
        throw std::overflow_error("convolution_fft: input exceeds rounding range");
    }

    const int length = static_cast<int>(a.size() + b.size() - 1);
    int n = 1;
    while (n < length) n *= 2;
    std::vector<fft_detail::Complex> fa(n), fb(n), roots(n / 2);
    for (std::size_t i = 0; i < a.size(); ++i) fa[i] = a[i];
    for (std::size_t i = 0; i < b.size(); ++i) fb[i] = b[i];
    for (int j = 0; j < n / 2; ++j) {
        roots[j] = std::polar(1.0L, 2 * std::numbers::pi_v<long double> * j / n);
    }
    fft_detail::transform(fa, roots, false);
    fft_detail::transform(fb, roots, false);
    for (int i = 0; i < n; ++i) fa[i] *= fb[i];
    fft_detail::transform(fa, roots, true);

    std::vector<long long> result(length);
    for (int i = 0; i < length; ++i) result[i] = std::llround(fa[i].real());
    return result;
}
/// &TRD_END
