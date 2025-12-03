#include <vector>

using namespace std;

template <typename T>
struct FenwickTree2D {
    int n, m;
    vector<vector<T>> t;

    /// @note n ~ x, m ~ y
    FenwickTree2D(int n, int m) : n(n), m(m), t(n + 1, vector<T>(m + 1)) {}

    void Add(int x, int y, int v) {
        x++, y++;
        for (int i = x; i <= n; i |= (i + 1)) {
            for (int j = y; j <= m; j |= (j + 1)) {
                t[i][j] += v;
            }
        }
    }

    T Sum(int x, int y) {
        T s = 0;
        for (int i = x; i > 0; i = (i & (i + 1)) - 1) {
            for (int j = y; j > 0; j = (j & (j + 1)) - 1) {
                s += t[i][j];
            }
        }
        return s;
    }

    T Sum(int x0, int y0, int x1, int y1) {
        x1++, y1++;
        return Sum(x1, y1) - Sum(x0, y1) - Sum(x1, y0) + Sum(x0, y0);
    }
};
