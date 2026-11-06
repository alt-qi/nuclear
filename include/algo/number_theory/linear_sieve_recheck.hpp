/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Линейное решето Эратосфена O(n) RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

struct linear_sieve {
    int n = 0;
    vector<int> lp, primes;

    void init(int n_) {
        n = n_;
        lp.assign(n + 1, 0);
        primes.clear();
        for (llt d = 2; d <= n; ++d) {
            if (lp[d] == 0) {
                lp[d] = d;
                primes.push_back(d);
            }
            for (ll i = 0; i < (int)primes.size() && primes[i] <= lp[d] && 1LL * primes[i] * d <= n; ++i) {
                lp[d * primes[i]] = primes[i];
            }
        }
    }

    bool is_prime(int x) const {
        return x >= 2 && x <= n && lp[x] == x;
    }

    vector<pair<int,int>> factorize(int x) const {
        vector<pair<int,int>> res;
        while (x > 1) {
            int p = lp[x], c = 0;
            while (x % p == 0) { x /= p; ++c; }
            res.push_back({p, c});
        }
        return res;
    }
};
/// &TRD_END
