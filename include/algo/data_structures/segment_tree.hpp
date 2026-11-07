#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()

using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
using f128 = long double;
using i128 = __int128_t;

/// &TRD_BEGIN
/// @author unknown
struct SegmentTree {
    int size = 1;
    vector<i64> tree, buf;

    SegmentTree(int n) {
        while (size < n)
            size *= 2;
        tree = vector<i64>(2 * size);
        buf = vector<i64>(tree.size());
    }

    void Push(int i) {
        if (i * 2 < tree.size()) {
            buf[i * 2] += buf[i];
            buf[i * 2 + 1] += buf[i];
        }

        tree[i] += buf[i];
        buf[i] = 0;
    }

    void Add(int l, int r, int v, int i, int lx, int rx) {
        Push(i);
        if (r <= lx || rx <= l) {
            return;
        } else if (l <= lx && rx <= r) {
            buf[i] += v;
        } else {
            int m = (lx + rx) / 2;
            Add(l, r, v, i * 2, lx, m);
            Add(l, r, v, i * 2 + 1, m, rx);
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
        Push(i);
    }

    void Add(int l, int r, int v) {
        Add(l, r, v, 1, 0, size);
    }

    i64 Min(int l, int r, int i, int lx, int rx) {
        Push(i);
        if (r <= lx || rx <= l){
            return 1e18;
        } else if (l <= lx && rx <= r) {
            return tree[i];
        } else {
            int m = (lx + rx) / 2;
            return min(Min(l, r, i * 2, lx, m),
                       Min(l, r, i * 2 + 1, m, rx));
        }
    }

    i64 Min(int l, int r) {
        return Min(l, r, 1, 0, size);
    }
};

/// &TRD_END
