/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Максимальное паросочетание (Кун, пример с main) RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

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
 
int main() {
	... чтение графа ...
 
	mt.assign (k, -1);
	for (int v=0; v<n; ++v) {
		used.assign (n, false);
		try_kuhn (v);
	}
 
	for (int i=0; i<k; ++i)
		if (mt[i] != -1)
			printf ("%d %d\n", mt[i]+1, i+1);
}
/// &TRD_END
