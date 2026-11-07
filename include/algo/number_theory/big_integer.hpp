
#include <bits/stdc++.h>
using namespace std;

/// &TRD_BEGIN
/// @author unknown
/// @brief Длинная арифметика RECHECK.
class Big {
    static constexpr int BASE = 1'000'000'000;
    vector<int> d;  // Младший блок первым. Пустой вектор означает 0.

    void trim() {
        while (!d.empty() && d.back() == 0) d.pop_back();
    }

public:
    explicit Big(unsigned long long x = 0) {
        for (; x; x /= BASE) d.push_back(x % BASE);
    }

    // s состоит из десятичных цифр. Ведущие нули допустимы.
    explicit Big(const string& s) {
        for (int r = int(s.size()); r > 0; r -= 9) {
            int l = max(0, r - 9);
            d.push_back(stoi(s.substr(l, r - l)));
        }
        trim();
    }

    friend istream& operator>>(istream& in, Big& a) {
        string s;
        if (in >> s) a = Big(s);
        return in;
    }

    friend ostream& operator<<(ostream& out, const Big& a) {
        if (a.d.empty()) return out << '0';
        out << a.d.back();
        char old_fill = out.fill('0');
        for (int i = int(a.d.size()) - 2; i >= 0; --i)
            out << setw(9) << a.d[i];
        out.fill(old_fill);
        return out;
    }

    // -1, 0 или 1 для a < b, a == b или a > b.
    friend int cmp(const Big& a, const Big& b) {
        if (a.d.size() != b.d.size())
            return a.d.size() < b.d.size() ? -1 : 1;
        for (int i = int(a.d.size()) - 1; i >= 0; --i) {
            if (a.d[i] != b.d[i]) return a.d[i] < b.d[i] ? -1 : 1;
        }
        return 0;
    }

    friend Big operator+(const Big& a, const Big& b) {
        Big c;
        int n = int(max(a.d.size(), b.d.size()));
        int carry = 0;
        for (int i = 0; i < n || carry; ++i) {
            int cur = carry;
            if (i < int(a.d.size())) cur += a.d[i];
            if (i < int(b.d.size())) cur += b.d[i];
            c.d.push_back(cur % BASE);
            carry = cur / BASE;
        }
        return c;
    }

    // Требуется a >= b.
    friend Big operator-(Big a, const Big& b) {
        assert(cmp(a, b) >= 0);
        int borrow = 0;
        for (int i = 0; i < int(a.d.size()); ++i) {
            int cur = a.d[i] - borrow;
            if (i < int(b.d.size())) cur -= b.d[i];
            borrow = cur < 0;
            a.d[i] = cur + borrow * BASE;
        }
        a.trim();
        return a;
    }

    friend Big operator*(const Big& a, const Big& b) {
        if (a.d.empty() || b.d.empty()) return Big();
        int n = int(a.d.size()), m = int(b.d.size());
        Big c;
        c.d.assign(n + m, 0);
        for (int i = 0; i < n; ++i) {
            long long carry = 0;
            for (int j = 0; j < m; ++j) {
                long long cur = c.d[i + j] + 1LL * a.d[i] * b.d[j] + carry;
                c.d[i + j] = int(cur % BASE);
                carry = cur / BASE;
            }
            c.d[i + m] = int(carry);
        }
        c.trim();
        return c;
    }

    // b > 0. Возвращает {частное, остаток}.
    pair<Big, uint32_t> divmod(uint32_t b) const {
        assert(b > 0);
        Big q;
        q.d.resize(d.size());
        uint64_t rem = 0;
        for (int i = int(d.size()) - 1; i >= 0; --i) {
            uint64_t cur = rem * BASE + d[i];
            q.d[i] = int(cur / b);
            rem = cur % b;
        }
        q.trim();
        return {move(q), uint32_t(rem)};
    }

    // b > 0. Деление столбиком с бинпоиском очередного блока частного.
    pair<Big, Big> divmod(const Big& b) const {
        assert(!b.d.empty());
        if (b.d.size() == 1) {
            auto [q, r] = divmod(uint32_t(b.d[0]));
            return {move(q), Big(r)};
        }

        Big q, r;
        q.d.resize(d.size());
        for (int i = int(d.size()) - 1; i >= 0; --i) {
            // r = r * BASE + d[i].
            if (!r.d.empty() || d[i] != 0) r.d.insert(r.d.begin(), d[i]);
            if (cmp(r, b) < 0) continue;

            int lo = 1, hi = BASE;
            while (hi - lo > 1) {
                int mid = (lo + hi) / 2;
                if (cmp(b * Big(mid), r) <= 0) lo = mid;
                else hi = mid;
            }
            q.d[i] = lo;
            r = r - b * Big(lo);
        }
        q.trim();
        return {move(q), move(r)};
    }
};

// Пример использования
inline bool example_big_integer() {
    Big a("1000000000000000000000000");  // неотрицательные числа
    auto [q, r] = a.divmod(3u);  // частное Big, остаток uint32_t
    return r == 1 && cmp(q * Big(3) + Big(r), a) == 0;
}
/// &TRD_END
