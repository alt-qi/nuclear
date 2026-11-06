/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Префикс-функция RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

vector<int> preffunc(const string& s) {
    int n = s.size();
    vector<int> p(n);

    for (int i = 1; i < n; ++i) {
        int j = p[i - 1];
        while (j != 0 && s[j] != s[i]) {
            j = p[j - 1];
        }
        if (s[j] == s[i]) {
            j++;
        }
        p[i] = j;
    }
    return p;
}
/// &TRD_END
