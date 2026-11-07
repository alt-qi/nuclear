#ifdef NUCLEAR_TRD_EXAMPLE
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 16;
int n = 0, m = 0;
#endif

/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Максимальное паросочетание (Кун с таймером) RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

vector<int> g[N]; int mt[N];
int last_version[N]; int timer = 0;
bool try_Kuhn(int v) {
    if (last_version[v] == timer) return false;
    last_version[v] = timer;
    for (int u : g[v]) {
        if (mt[u] == -1) {
            mt[u] = v;
            return true;
        }
        if (try_Kuhn(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

void solve() {
    int cnt = 0;
    fill(mt, mt + N, -1);
    for (int v = 1; v <= n; v++) {
        timer++;
        if (try_Kuhn(v)) {
            cnt++;
        }
    }
    cout << cnt << "\n";
    for (int u = 1; u <= m; u++) {
        if (mt[u] != -1) {
            // вывод -- паросочетание
            cout << mt[u] << " " << u << "\n";
        }
    }
}
/// &TRD_END

/// &TRD_EXAMPLE_BEGIN
// Пример использования
inline bool example_kuhn_timer() {
    n = m = 2; g[1] = {1, 2}; g[2] = {1};  // вершины долей с единицы
    std::fill(mt, mt + N, -1);
    for (int v = 1; v <= n; ++v) { ++timer; try_Kuhn(v); }
    return mt[1] == 2 && mt[2] == 1;  // mt[правая] = левая
}
/// &TRD_EXAMPLE_END
