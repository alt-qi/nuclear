/// &TRD_BEGIN
/// @author unknown
/// @brief Z-функция RECHECK.
vector<int> zfunc(const string& s) {
    int n = s.size();
    vector<int> z(n);
    int j = 0;
    for (int i = 1; i < n; ++i) {
        z[i] = max(min(z[i - j], z[j] + j - i), 0);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
            int c1 = z[i], c2 = i + z[i];
            z[i]++;
        }
        if (i + z[i] > j + z[j]) {
            j = i;
        }
    }
    z[0] = n;
    return v;
}
/// &TRD_END
