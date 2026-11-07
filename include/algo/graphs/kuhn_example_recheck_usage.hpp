#pragma once

#include <bits/stdc++.h>
using namespace std;
#include "kuhn_example_recheck.hpp"

/// &TRD_BEGIN
inline bool example_kuhn() {
    n = k = 2; g = {{0, 1}, {0}};  // вершины обеих долей с нуля
    mt.assign(k, -1);
    for (int v = 0; v < n; ++v) { used.assign(n, false); try_kuhn(v); }
    return mt[0] == 1 && mt[1] == 0;  // mt[правая] = левая
}
/// &TRD_END
