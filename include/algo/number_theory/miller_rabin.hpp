/// &TRD_BEGIN
/// @author unknown
/// @brief Проверка на простоту Миллера — Рабина RECHECK.
// Быстрое возведение в степень по модулю с защитой от переполнения
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp /= 2;
    }
    return res;
}

// Тест Миллера-Рабина
bool is_prime(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    long long d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    // Свидетели, достаточные для детерминированной проверки всех long long
    for (long long a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;

        long long x = power(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        long long temp_d = d;
        while (temp_d * 2 < n - 1) {
            temp_d *= 2;
            x = (__int128)x * x % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}
/// &TRD_END
