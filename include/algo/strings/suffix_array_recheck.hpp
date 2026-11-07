#ifdef NUCLEAR_TRD_EXAMPLE
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#endif

/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Суффиксный массив и LCP RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

struct SuffixArray {
    int n;
    string s;
    vector<ll> sa;
    SuffixArray(const string& _s) {
        n = _s.size();
        s = _s;
        sa = suffix_array(s);
    }
    vector<ll> sort_cyclic_shifts(const string& s) {
        int n = s.size();
        const int alphabet = 256;
        vector<ll> p(n), c(n), cnt(max(alphabet, n));
        for (unsigned char el: s) cnt[el]++;
        for (int i = 1; i < alphabet; ++i) cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; ++i) p[--cnt[(unsigned char)s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; ++i) {
            if (s[p[i]] != s[p[i - 1]]) ++classes;
            c[p[i]] = classes - 1;
        }
        vector<ll> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0) pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (auto el: pn) cnt[c[el]]++;
            for (int i = 1; i < classes; ++i) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i) p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++) {
                pair<int,int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<int,int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
                if (cur != prev) ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
        return p;
    }
    vector<ll> suffix_array(string s) {
        s += char(0);
        vector<ll> sorted_shifts = sort_cyclic_shifts(s);
        sorted_shifts.erase(sorted_shifts.begin());
        return sorted_shifts;
    }
};

vector<ll> build_lcp(const string& s, const vector<ll>& sa) {
    int n = s.size();
    vector<ll> rank(n), lcp(n - 1);
    for (int i = 0; i < n; ++i) rank[sa[i]] = i;
    int k = 0;
    for (int i = 0; i < n; ++i) {
        int r = rank[i];
        if (r == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[r + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
        lcp[r] = k;
        if (k) --k;
    }
    return lcp;
}

// Пример использования
inline bool example_suffix_array() {
    std::string s = "aba";  // непустая строка без байта 0
    SuffixArray suffixes(s);
    return suffixes.sa == std::vector<ll>{2, 0, 1}
        && build_lcp(s, suffixes.sa) == std::vector<ll>{1, 0};
}
/// &TRD_END
