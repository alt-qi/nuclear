/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Максимальное паросочетание (Кун с очисткой used) RECHECK.
/// @date 2026-11-06
/// @note Порядок вызовов показан в kuhn_example_recheck_usage.hpp.

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
