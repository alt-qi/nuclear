#ifdef NUCLEAR_TRD_EXAMPLE
#include <bits/stdc++.h>
using namespace std;
#endif

/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Максимальное паросочетание (Кун с очисткой used) RECHECK.
/// @date 2026-11-06
/// @note Порядок вызовов показан в example_kuhn.

int n, k;
vector < vector<int> > g;
vector<int> mt;
vector<char> used;
 
bool try_kuhn (int v) {
	if (used[v])  return false;
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (mt[to] == -1 || try_kuhn (mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}
/// &TRD_END

/// &TRD_EXAMPLE_BEGIN
// Пример использования
inline bool example_kuhn() {
    n = k = 2; g = {{0, 1}, {0}};  // вершины обеих долей с нуля
    mt.assign(k, -1);
    for (int v = 0; v < n; ++v) { used.assign(n, false); try_kuhn(v); }
    return mt[0] == 1 && mt[1] == 0;  // mt[правая] = левая
}
/// &TRD_EXAMPLE_END
