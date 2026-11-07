#pragma once

#include <vector>
using std::vector;
using ll = long long;
#include "fenwick_tree_recheck.hpp"

/// &TRD_BEGIN
inline bool example_fenwick() {
    Fenwick f(4);
    f.add(1, 3); f.add(3, 5);  // индексы с единицы
    return f.sumRange(2, 4) == 5;  // обе границы включены
}
/// &TRD_END
