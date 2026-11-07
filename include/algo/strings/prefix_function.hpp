/// &TRD_BEGIN
/// @author unknown
/// @brief Префикс-функция RECHECK.
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
