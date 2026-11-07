#pragma once

#include <bits/stdc++.h>
using namespace std;
constexpr int N = 16;
int n = 0, m = 0;
#include "kuhn_recheck.hpp"

/// &TRD_BEGIN
inline bool example_kuhn_timer() {
    n = m = 2; g[1] = {1, 2}; g[2] = {1};  // вершины долей с единицы
    std::fill(mt, mt + N, -1);
    for (int v = 1; v <= n; ++v) { ++timer; try_Kuhn(v); }
    return mt[1] == 2 && mt[2] == 1;  // mt[правая] = левая
}
/// &TRD_END
