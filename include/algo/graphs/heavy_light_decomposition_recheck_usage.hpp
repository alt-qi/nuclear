#pragma once

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 16;
#include "heavy_light_decomposition_recheck.hpp"

/// &TRD_BEGIN
inline bool example_hld() {
    n = 2; g[1] = {2}; g[2] = {1};  // вершины с единицы
    vertex_value[1] = 3; vertex_value[2] = 5;
    build_hld();  // корень 1
    bool ok = get_way_value(1, 2) == 8;  // сумма на пути
    update(1, 1, n + 1, tin[2], Node(9));  // заменить вес вершины 2
    return ok && get_way_value(1, 2) == 12;
}
/// &TRD_END
