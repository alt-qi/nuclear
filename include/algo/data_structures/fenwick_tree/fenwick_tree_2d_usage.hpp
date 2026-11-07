#pragma once

#include "fenwick_tree_2d.hpp"

/// &TRD_BEGIN
inline bool example_fenwick_2d() {
    FenwickTree2D<long long> f(2, 3);
    f.Add(0, 1, 4); f.Add(1, 2, 7);  // индексы с нуля
    return f.Sum(0, 1, 1, 1) == 4 && f.Sum(2, 3) == 11;
}
/// &TRD_END
