/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Дерево отрезков с массовыми операциями RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegTree {
    int n = 0;
    vector<ll> t, c;
    static constexpr ll NEG_INF = (ll)-4e18;

    SegTree() = default;
    explicit SegTree(int n_) : n(n_), t(4 * n_, 0), c(4 * n_, 0) {}
    explicit SegTree(const vector<ll>& a) { init(a); }

    void init(int n_) {
        n = n_;
        t.assign(4 * n, 0);
        c.assign(4 * n, 0);
    }

    void init(const vector<ll>& a) {
        n = (int)a.size();
        t.assign(4 * n, 0);
        c.assign(4 * n, 0);
        build(0, 0, n, a);
    }

    void build(const vector<ll>& a) { init(a); }

    void push(int v) {
        if (c[v] != 0) {
            c[v * 2 + 1] += c[v];
            c[v * 2 + 2] += c[v];
            c[v] = 0;
        }
    }

    void pull(int v) {
        t[v] = max(t[v * 2 + 1] + c[v * 2 + 1],
                   t[v * 2 + 2] + c[v * 2 + 2]);
    }

    void build(int v, int l, int r, const vector<ll>& a) {
        if (r - l == 1) {
            t[v] = a[l];
            c[v] = 0;
            return;
        }
        int m = (l + r) / 2;
        build(v * 2 + 1, l, m, a);
        build(v * 2 + 2, m, r, a);
        t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
        c[v] = 0;
    }

    void add(int ql, int qr, ll val) { add(0, 0, n, ql, qr, val); }

    void add(int v, int l, int r, int ql, int qr, ll val) {
        if (ql <= l && r <= qr) {
            c[v] += val;
            return;
        }
        if (r <= ql || qr <= l) return;
        int m = (l + r) / 2;
        push(v);
        add(v * 2 + 1, l, m, ql, qr, val);
        add(v * 2 + 2, m, r, ql, qr, val);
        pull(v);
    }

    ll getmax(int ql, int qr) { return getmax(0, 0, n, ql, qr); }

    ll getmax(int v, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return t[v] + c[v];
        if (r <= ql || qr <= l) return NEG_INF;
        int m = (l + r) / 2;
        push(v);
        ll left = getmax(v * 2 + 1, l, m, ql, qr);
        ll right = getmax(v * 2 + 2, m, r, ql, qr);
        pull(v);
        return max(left, right);
    }
};
/// &TRD_END
