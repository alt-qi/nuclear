#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
using ld = long double;
constexpr ld EPS = 1e-12L;
#include "graham_recheck.hpp"

/// &TRD_BEGIN
inline bool example_graham() {
    auto hull = graham({{0, 0}, {4, 0}, {0, 4}, {1, 1}});
    return hull.size() == 3;  // (1, 1) внутри
}
/// &TRD_END
