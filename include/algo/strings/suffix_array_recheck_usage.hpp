#pragma once

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "suffix_array_recheck.hpp"

/// &TRD_BEGIN
inline bool example_suffix_array() {
    std::string s = "aba";  // непустая строка без байта 0
    SuffixArray suffixes(s);
    return suffixes.sa == std::vector<ll>{2, 0, 1}
        && build_lcp(s, suffixes.sa) == std::vector<ll>{1, 0};
}
/// &TRD_END
